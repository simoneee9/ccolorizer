#pragma once

#include <algorithm>
#include <array>
#include <cstdint>

struct Pixel
{
  Pixel(uint64_t x, uint64_t y): x(x), y(y) {}

  Pixel(uint64_t x, uint64_t y, uint8_t red, uint8_t gre, uint8_t blu)
  : x(x), y(y) {
    
    double r_n = static_cast<double>(red) / 255.0;
    double g_n = static_cast<double>(gre) / 255.0;
    double b_n = static_cast<double>(blu) / 255.0;
    
    // actually im too lazy to figure out what is white point normalization
    // i literally worked for 8 hours today trying to make windows containers work
    // i deserve a break
    // double x_tris = 0.4124564 * r_n + 0.3575761 * g_n + 0.1804375 * b_n;
    // double y_tris = 0.2126729 * r_n + 0.7151522 * g_n + 0.0721750 * b_n;
    // double z_tris = 0.0193339 * r_n + 0.1191920 * g_n + 0.9503041 * b_n;

    // actually converting to YUV hehehehee
    L =  0.257 * r_n + 0.504 * g_n + 0.098 * b_n + 16;
    a = -0.148 * r_n - 0.291 * g_n + 0.439 * b_n + 128;
    b =  0.439 * r_n - 0.368 * g_n - 0.071 * b_n + 128;

  }

  // int32_t L;
  // int32_t a;
  // int32_t b;
  double L;
  double a;
  double b;

  uint64_t x;
  uint64_t y;

  std::array<uint8_t, 3> to_rgb() const
  {
    
    // again, doing YUV for now
    double L_t = L - 16;
    double a_t = a - 128;
    double b_t = b - 128;

    double red = (1.164 * L_t               + 1.596 * b_t) * 255 ;
    double gre = (1.164 * L_t - 0.392 * a_t - 0.813 * b_t) * 255 ;
    double blu = (1.164 * L_t + 2.017 * a_t              ) * 255 ;

    uint8_t rr = std::clamp(red, 0.0, 255.0);
    uint8_t gg = std::clamp(gre, 0.0, 255.0);
    uint8_t bb = std::clamp(blu, 0.0, 255.0);

    return {rr, gg, bb};
  }

};
