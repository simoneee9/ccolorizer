#include "header/image.hh"
#include "header/image_loader.hh"
#include <utility>

Image::Image(const std::filesystem::path& p)
{
  initialized_ = load(p);
}

// copy
Image::Image(const Image& other)
{
  path_ = other.path_;
  initialized_ = other.initialized_;
  data_ = other.data_;
}

Image& Image::operator=(const Image& other)
{
  return *this = Image(other);
}

// move
Image::Image(Image&& other) noexcept
{
  path_ = other.path_;
  initialized_ = other.initialized_;
  data_ = std::move(other.data_);
}

Image& Image::operator=(Image&& other) noexcept
{
  path_ = other.path_;
  initialized_ = other.initialized_;
  data_ = std::move(other.data_);
  return *this;
}

bool Image::load(const std::filesystem::path& p)
{
  LoadedImage loaded = ImageLoader::load(p);
  width_ = loaded.width;
  height_ = loaded.height;
  data_ = std::move(loaded.data);
  initialized_ = true;
  return initialized_;
}

bool Image::create(const std::filesystem::path& p)
{
  // create file

  return save();
}

bool Image::save() const
{

  return true;
}

Pixel& Image::operator[](size_t index)
{
  return data_[index];
}

const Pixel& Image::operator[](size_t index) const
{
  return data_[index];
}

Pixel& Image::operator[](Coordinates p)
{
   return data_[toIndex(p, height_)];
}

const Pixel& Image::operator[](Coordinates p) const
{
   return data_[toIndex(p, height_)];
}
