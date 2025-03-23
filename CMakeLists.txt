cmake_minimum_required(VERSION 3.20)

project(WaterSort)

enable_testing()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

# Add source to this project's executable.
add_executable (WaterSort "WaterSort.cpp")
target_include_directories(WaterSort PRIVATE tube)

add_subdirectory(test)