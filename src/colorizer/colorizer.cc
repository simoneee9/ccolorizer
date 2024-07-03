#include "header/colorizer.hh"
#include <algorithm>
#include <cmath>
#include <cstdlib>

Colorizer::Colorizer() {}

Colorizer::~Colorizer() {}

bool Colorizer::colorize()
{
  if (!in_image_ || !tag_image_)
    return false;

  auto tagged = detectTaggedPixels();
  auto sparse = analyzeImage(tagged);

  return solveEquations(sparse);
}

std::vector<bool> Colorizer::detectTaggedPixels()
{
  if (tag_image_.size() != in_image_.size())
    throw std::runtime_error("image dimensions do not match");

  auto [w, h] = in_image_.size();
  std::vector<bool> tagged(w * h, false);
  auto isTagged = [](const Pixel& a, const Pixel& b) {
    return 2 > abs(a.L - b.L);
  };

  std::transform(in_image_.begin(), in_image_.end(), tag_image_.begin(),
                 tagged.begin(), isTagged);

  return tagged;
}

SparseMatrix
Colorizer::analyzeImage(uint8_t pixel_window_raidus,
                        const std::vector<bool>& tagged_pixels) const
{
  auto [w, h]               = in_image_.size();
  uint64_t pixels_in_window = std::pow(2 * pixel_window_raidus + 1, 2);
  uint64_t matrix_size      = w * h * pixels_in_window;

  SparseAxis rows(matrix_size), cols(matrix_size);
  SparseData data(matrix_size);

  std::vector<int32_t> a_channel(w * h, 0), b_channel(w * h, 0);
  uint64_t img_index;
  uint64_t x{ 0 }, y{ 0 };

  uint8_t L;
  int32_t a, b;
  while (x < w) {
    while (y < h) {

      img_index = Image::toIndex({ x, y }, h);

      if (tagged_pixels[img_index]) {
        // tagged
        a_channel[img_index] = tag_image_[img_index].a;
        b_channel[img_index] = tag_image_[img_index].b;
      } else {
        // not tagged, calculate weights
      }
    }
  }
  for (size_t i = 0; i < (w * h); i++) {
  }
}

bool Colorizer::solveEquations(const SparseMatrix& sparse) {}
