#pragma once

#include <filesystem>
#include <vector>

#include "pixel.hh"

class Image
{
public:
  Image() = default;
  Image(std::filesystem::path p);
  ~Image() = default;

  // copy
  Image(const Image& other);
  Image& operator=(const Image& other);

  // move
  Image(Image&& other) noexcept;
  Image& operator=(Image&& other) noexcept;

  bool load(std::filesystem::path p);
  bool create(std::filesystem::path p);
  bool save() const;

  inline operator bool() const { return initialized_; }

  inline size_t size() const { return data_.size(); }

  inline std::vector<Pixel>::iterator begin() noexcept { return data_.begin(); }
  inline std::vector<Pixel>::const_iterator cbegin() noexcept { return data_.cbegin(); }
  inline std::vector<Pixel>::iterator end() noexcept { return data_.end(); }
  inline std::vector<Pixel>::const_iterator cend() noexcept { return data_.cend(); }

  Pixel& operator[](size_t index);
  const Pixel& operator[](size_t index) const;

private:
  std::filesystem::path path_;
  bool initialized_{ false };
  std::vector<Pixel> data_;
};
