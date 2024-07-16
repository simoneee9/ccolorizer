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
    ImageLoader() = delete;
    ~ImageLoader() = delete;

    static LoadedImage load(std::filesystem::path p);

    static LoadedImage sail_load(std::filesystem::path p);

private:
    std::vector<Pixel> process_data();
};
