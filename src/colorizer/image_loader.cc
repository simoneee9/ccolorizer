#include "header/image_loader.hh"
#include <cstdint>
#include <sail-c++/image.h>
#include <sail-c++/image_input.h>
#include <sail-common/common.h>
#include <sail-common/status.h>
#include <stdexcept>
#include <sys/types.h>
#include <print>
#include <iostream>

LoadedImage ImageLoader::load(const std::filesystem::path &p) {
  // todo
  return sail_load(p);
}

bool ImageLoader::save(const LoadedImage &li, const std::filesystem::path &p) {
  // todo
  return sail_save(li, p);
}

LoadedImage ImageLoader::sail_load(const std::filesystem::path &p) {
  LoadedImage loaded{};
  sail::image_input in{p};
  sail::image img{};

  bool continue_loading = true;
  while (true) {
    auto sail_status = in.next_frame(&img);
    if (sail_status == SAIL_OK)
      continue;

    if (sail_status == SAIL_ERROR_NO_MORE_FRAMES)
      break;

    auto placeholder = "An unexpected SAIL error happened with code";
    throw std::runtime_error(placeholder + sail_status);
  }
  in.finish();

  if (!img.is_valid())
    throw std::runtime_error("Failed to load image");

  if (!img.can_convert(SAIL_PIXEL_FORMAT_BPP24_RGB))
    throw std::runtime_error("Image cannot be converted to a supported format");

  if (SAIL_OK != img.convert(SAIL_PIXEL_FORMAT_BPP24_RGB))
    throw std::runtime_error("Failed to convert image to RGB");

  loaded.width = img.width();
  loaded.height = img.height();
  loaded.data.reserve(loaded.width * loaded.height);

  for (uint64_t y = 0; y < loaded.height; ++y) {
    // Ownership is not mine, don't delete this
    const uint8_t *row = reinterpret_cast<uint8_t *>(img.scan_line(y));

    for (uint64_t x = 0; x < loaded.width; ++x) {
      loaded.data.push_back(Pixel(row[3 * x], row[3 * x + 1], row[3 * x + 2], x, y));
    }
  }

  return loaded;
}

bool ImageLoader::sail_save(const LoadedImage &li,
                            const std::filesystem::path &p) {

  sail::image img(SailPixelFormat::SAIL_PIXEL_FORMAT_BPP24_RGB, li.width,
                  li.height);

  for (uint64_t y = 0; y < li.height; ++y) {
    // Ownership is not mine, don't delete this
    uint8_t *row = reinterpret_cast<uint8_t *>(img.scan_line(y));

    for (uint64_t x = 0; x < li.width; ++x) {
      uint64_t i = x * li.height + y;
      
      std::array<uint8_t, 3> rgb = li.data[i].to_rgb();

      row[3 * x + 0] = rgb[0];
      row[3 * x + 1] = rgb[1];
      row[3 * x + 2] = rgb[2];
    }
  }
  
  return SAIL_OK == img.save(p);
}
