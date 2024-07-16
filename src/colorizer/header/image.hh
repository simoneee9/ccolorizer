#pragma once

#include <filesystem>
#include <vector>

#include "pixel.hh"

struct Dimensions {
  uint64_t width;
  uint64_t height;
};

using Coordinates = Dimensions;

inline bool operator==(const Dimensions& lhs, const Dimensions& rhs)
{
  return lhs.width == rhs.width && lhs.height == rhs.height;
}

inline bool operator!=(const Dimensions& lhs, const Dimensions& rhs)
{
    return !(lhs == rhs);
}


class Image
{
public:
  Image() = default;
  Image(const std::filesystem::path& p);
  ~Image() = default;

  // copy
  Image(const Image& other);
  Image& operator=(const Image& other);

  // move
  Image(Image&& other) noexcept;
  Image& operator=(Image&& other) noexcept;

  bool load(const std::filesystem::path& p);
  bool create(const std::filesystem::path& p);
  bool save() const;

  inline operator bool() const { return initialized_; }

  inline Dimensions size() const { return { width_, height_ }; }
  inline uint64_t width() const { return width_; }
  inline uint64_t height() const { return height_; }

  inline std::vector<Pixel>::iterator begin() noexcept { return data_.begin(); }
  inline std::vector<Pixel>::const_iterator cbegin() noexcept
  {
    return data_.cbegin();
  }
  inline std::vector<Pixel>::iterator end() noexcept { return data_.end(); }
  inline std::vector<Pixel>::const_iterator cend() noexcept
  {
    return data_.cend();
  }

  Pixel& operator[](size_t index);
  const Pixel& operator[](size_t index) const;

  Pixel& operator[](Coordinates p);
  const Pixel& operator[](Coordinates p) const;

  inline static Coordinates toCoordinates(size_t index, uint32_t h)
  {
    return { (index - (index % h) / h), index % h };
  }

  inline static size_t toIndex(const Coordinates& dim, uint32_t h)
  {
    return dim.height * h + dim.width;
  }

private:
  std::filesystem::path path_;
  bool initialized_{ false };
  std::vector<Pixel> data_;

  uint32_t width_{ 0 };
  uint32_t height_{ 0 };
};
