cmake_minimum_required(VERSION 3.29.6)

project(
  CColorizer
  VERSION 0.1
  LANGUAGES CXX
)

set(EXE_NAME "ccolorize")

add_executable(${EXE_NAME} main.cc)

add_subdirectory(src/colorizer)

target_link_libraries(${EXE_NAME} colorizer)

