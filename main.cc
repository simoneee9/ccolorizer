
#include <cstdint>
#include <filesystem>
#include <optional>

struct Flags {
  bool help{ false };
  bool verbose{ false };
  std::optional<std::filesystem::path> in_file_path;
  std::optional<std::filesystem::path> tag_file_path;
  std::optional<std::filesystem::path> out_file_path;
  uint8_t pixel_window_radius{ 1 };
  char afinity_function{ 'a' };
};

void print_help() {}

int main(int argc, char* argv[])
{
  if (argc == 1) {
    print_help();
    return 0;
  }

  for (int i = 0; i < argc; i++) {
  }
}
