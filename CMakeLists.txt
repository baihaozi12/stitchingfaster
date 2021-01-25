cmake_minimum_required(VERSION 3.10)
project(stitchingfaster)
find_package(OpenMP)
if (NOT OPENMP_FOUND)
    message(WARNING "OpenMP is not found. Will be slow.")
else()
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

find_package(JPEG)
if(JPEG_FOUND)
    include_directories(${JPEG_INCLUDE_DIR})
endif()

find_package(Eigen3 REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(stitchingfaster main.cpp)