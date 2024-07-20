#include "header/colorizer.hh"
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <cstdlib>

Colorizer::Colorizer() {}

Colorizer::~Colorizer() {}

bool Colorizer::colorize()
{
  if ( !in_image_ || !tag_image_ )
    return false;

  auto tagged = detectTaggedPixels();
  auto sparse = analyzeImage( 1, tagged );

  return solveEquations( sparse );
}

std::vector<bool> Colorizer::detectTaggedPixels()
{
  if ( tag_image_.size() != in_image_.size() )
    throw std::runtime_error( "image dimensions do not match" );

  auto [w, h] = in_image_.size();
  std::vector<bool> tagged( w * h, false );
  auto isTagged = []( const Pixel& a, const Pixel& b ) {
    return 2 > abs( a.L - b.L );
  };

  std::transform( in_image_.begin(), in_image_.end(), tag_image_.begin(),
                  tagged.begin(), isTagged );

  return tagged;
}

SparseMatrix
Colorizer::analyzeImage( uint8_t pixel_window_radius,
                         const std::vector<bool>& tagged_pixels ) const
{
  auto [w, h]               = in_image_.size();
  uint64_t pixels_in_window = std::pow( 2 * pixel_window_radius + 1, 2 );
  uint64_t matrix_size      = w * h * pixels_in_window;

  SparseAxis rows( matrix_size ), cols( matrix_size );
  SparseData data( matrix_size );
  SparseMatrix mat{ cols, rows, data };

  std::vector<int32_t> a_channel( w * h, 0 ), b_channel( w * h, 0 );
  uint64_t img_index;
  uint64_t x{ 0 }, y{ 0 };

  uint8_t L;
  int32_t a, b;
  while ( x < w ) {
    while ( y < h ) {

      img_index = Image::toIndex( { x, y }, w );

      if ( tagged_pixels[img_index] ) {
        // tagged
        a_channel[img_index] = tag_image_[img_index].a;
        b_channel[img_index] = tag_image_[img_index].b;
      } else {
        // not tagged, calculate weights
        pixelWeights( { x, y }, pixel_window_radius, mat );
      }
    }
  }
}

void Colorizer::pixelWeights( const Coordinates& pixel, uint8_t radius,
                              SparseMatrix& mat ) const
{
  uint16_t one_side = 2 * radius + 1;
  const auto [x, y] = pixel;
  uint64_t w        = in_image_.width();

  uint64_t min_x{ 0 }, max_x{ in_image_.width() }, min_y{ 0 },
      max_y{ in_image_.height() };

  if ( x > radius )
    min_x = x - radius;
  if ( x + radius < in_image_.width() )
    max_x = x + radius;
  if ( y > radius )
    min_y = y - radius;
  if ( y + radius < in_image_.height() )
    max_y = y + radius;

  uint32_t num_pixels = ( max_x - min_x + 1 ) * ( max_y - min_y + 1 );

  // calculate mean & variance first
  uint64_t sum{ 0 };
  uint64_t luminance;
  double variance{ 0.0 };
  for ( uint64_t i = min_x; i < max_x; i++ ) {
    for ( uint64_t j = min_y; j < max_y; j++ ) {
      luminance = in_image_[Image::toIndex( { i, j }, w )].L;
      sum += luminance;
      variance += std::pow( luminance, 2.0 );
    }
  }

  double mean = sum / static_cast<double>( num_pixels );
  if ( mean < DBL_EPSILON )
    mean = 1e-6;

  variance =
      ( variance / static_cast<double>( num_pixels ) ) - std::pow( mean, 2. );

  uint64_t idx = Image::toIndex( { x, y }, w );
}

bool Colorizer::solveEquations( const SparseMatrix& sparse ) {}
