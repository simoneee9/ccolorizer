#include "colorizer.hh"

#include <cstdint>
#include <filesystem>
#include <print>

struct Flags
{
  bool help{ false };
  bool verbose{ false };
  std::filesystem::path in_file_path;
  std::filesystem::path tag_file_path;
  std::filesystem::path out_file_path;
  uint8_t pixel_window_radius{ 1 };
  char afinity_function{ 'a' };
};

void print_help() {}

Flags process_flags( int argc, char* argv[] )
{
  Flags fl{};
  for ( int i = 0; i < argc; i++ ) {
    // todo process args
  }

  return fl;
}

int main( int argc, char* argv[] )
{
  if ( argc == 1 ) {
    print_help();
    return 0;
  }

  Flags fl = process_flags( argc, argv );
  if ( fl.help == true ) {
    print_help();
    return 0;
  }

  Colorizer colorizer{};
  if ( !colorizer.loadInputImage( fl.in_file_path ) )
    return 1;

  if ( !colorizer.loadTaggedImage( fl.tag_file_path ) )
    return 1;

  if ( !colorizer.colorize( fl.pixel_window_radius, fl.afinity_function ) )
    return 1;

  if ( !colorizer.saveOutputImage( fl.out_file_path ) )
    return 1;
}
