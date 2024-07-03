#include "header/colorizer.hh"
#include <algorithm>
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

  std::vector<bool> tagged(in_image_.size(), false);
  auto isTagged = [](const Pixel& a, const Pixel& b) {
    return 2 > abs(a.L - b.L);
  };

  std::transform(in_image_.begin(), in_image_.end(), tag_image_.begin(),
                 tagged.begin(), isTagged);

  return tagged;
}

SparseMatrix
Colorizer::analyzeImage(const std::vector<bool>& tagged_pixels) const
{
  
}

bool Colorizer::solveEquations(const SparseMatrix& sparse) {}
