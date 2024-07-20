#pragma once

#include <cstdint>
#include <filesystem>

#include "image.hh"

using SparseAxis = std::vector<uint64_t>;
using SparseData = std::vector<double>;

struct SparseMatrix
{
  SparseAxis rows;
  SparseAxis cols;
  SparseData data;
};

class Colorizer
{
public:
  Colorizer();
  ~Colorizer();

  bool loadInputImage( std::filesystem::path p );
  bool loadTaggedImage( std::filesystem::path p );

  bool colorize( uint8_t pixel_window_radius, char afinity = 'a' );

  bool saveOutputImage( std::filesystem::path p );

  /* prepare the object for reuse */
  void restore();

private:
  bool colorized_{ false };

  Image in_image_;
  Image tag_image_;
  Image out_image_;

  std::vector<bool> detectTaggedPixels();
  SparseMatrix analyzeImage( uint8_t pixel_window_radius,
                             const std::vector<bool>& tagged_pixels ) const;

  bool solveEquations( const SparseMatrix& sparse );

  void pixelWeights( const Coordinates& pixel, uint8_t radius,
                     SparseMatrix& mat ) const;
};
