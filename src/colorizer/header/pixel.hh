#pragma once

#include <array>
#include <cstdint>
struct Pixel
{
  Pixel(uint64_t x, uint64_t y): x(x), y(y) {}

  Pixel(uint64_t x, uint64_t y, uint8_t r, uint8_t g, uint8_t b)
  : x(x), y(y) {

  }

  int32_t L;
  int32_t a;
  int32_t b;

  uint64_t x;
  uint64_t y;

  std::array<uint8_t, 3> to_rgb() const
  {
    uint8_t r{0}, g{0}, b{0};
    // todo
    

    return {r, g, b};
  }
};
