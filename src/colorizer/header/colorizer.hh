#pragma once

#include <cstdint>
#include <vector>

class Colorizer {
public:
  
  Colorizer();
  ~Colorizer();


private:

  std::vector<uint32_t> in_image_;
  std::vector<uint32_t> tag_image_;
  std::vector<uint32_t> out_image_;

};
