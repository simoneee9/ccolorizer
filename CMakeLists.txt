cmake_minimum_required(VERSION 3.29.6)

project(
  CColorizer
  VERSION 0.1
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-std=c++2b -lstdc++fs")

set(EXE_NAME "ccolorize")
add_executable(${EXE_NAME} main.cc)


add_subdirectory(src/colorizer)
include_directories(src/colorizer)

target_include_directories(${EXE_NAME}
  PUBLIC src/colorizer
)

target_link_directories(${EXE_NAME}
  PRIVATE src/colorizer
)

target_link_libraries(${EXE_NAME} colorizer)
