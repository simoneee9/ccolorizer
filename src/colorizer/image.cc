#include "header/image.hh"
#include <utility>

Image::Image(std::filesystem::path p)
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

bool Image::load(std::filesystem::path p)
{

  return initialized_;
}

bool Image::create(std::filesystem::path p)
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
