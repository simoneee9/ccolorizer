#include <print>

void print_help() {}

int main(int argc, char* argv[])
{ 
  if (argc == 1) {
    print_help();
    return 0;
  }

  for (int i = 0; i < argc; i++) {
    std::println("{}", argv[i]);
  }
}
