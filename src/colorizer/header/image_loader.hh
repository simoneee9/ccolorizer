#pragma once

#include <filesystem>
#include <vector>

#include "pixel.hh"

class Image;

struct LoadedImage
{
  std::vector<Pixel> data;
  uint64_t width;
  uint64_t height;
};

class ImageLoader
{
public:
  ImageLoader()  = delete;
  ~ImageLoader() = delete;

  static LoadedImage load( const std::filesystem::path& p );
  static bool save( const LoadedImage& li, const std::filesystem::path& p );

  static LoadedImage sail_load( const std::filesystem::path& p );
  static bool sail_save( const LoadedImage& li,
                         const std::filesystem::path& p );

private:
  std::vector<Pixel> process_data();
};
