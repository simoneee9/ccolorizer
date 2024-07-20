include_directories(header/)

find_package(SailC++ REQUIRED)


file(GLOB colorizer_SRC "*.cc")
add_library(colorizer ${colorizer_SRC})

target_include_directories(colorizer PRIVATE "${CMAKE_INSTALL_INCLUDEDIR}/sail")

target_link_libraries(colorizer SAIL::sail-c++)
