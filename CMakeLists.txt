cmake_minimum_required(VERSION 3.1)
project(stitchingfaster)
#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# find openmp

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE -DWIN32_LEAN_AND_MEAN -DVC_EXTRALEAN -DMSVC)
    # /Zo makes debug symbol in pdb in release mode in VS2015
    add_definitions(/fp:fast /GR- /Os /Zo /arch:AVX /openmp)
else()
    add_definitions(-O3 -march=native -Wall -Wextra)
endif()
add_definitions(-DDEBUG)

find_package(OpenMP)
if (NOT OPENMP_FOUND)
    message(WARNING "OpenMP is not found. Will be slow.")
else()
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()
# find jpeg
find_package(JPEG)
if(JPEG_FOUND)
    include_directories(${JPEG_INCLUDE_DIR})
endif()

# find eigen 3
find_package(Eigen3 REQUIRED)
# add third party
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third-party/)
# definitions
add_definitions(${EIGEN3_DEFINITIONS})
include_directories(${EIGEN3_INCLUDE_DIRS})
# find sources
file(GLOB SOURCES feature/*.cc stitch/*.cc lib/*.cc )



add_executable(stitchingfaster main.cc )

#add_library(stitchingfaster ${SOURCES})	# TODO shared?
target_link_libraries(stitchingfaster ${JPEG_LIBRARY} lodepng)
if (NOT JPEG_FOUND)
    target_compile_definitions(stitchingfaster PUBLIC DISABLE_JPEG)
#    target_compile_definitions(image-stitching PUBLIC DISABLE_JPEG)
endif()
find_package(PythonLibs)
#if(PYTHONLIBS_FOUND AND BUILD_SHARED_LIBS)
#    add_library(pyopenpano SHARED python/pybind.cc)
#    target_link_libraries(pyopenpano openpano pybind11)
#    target_include_directories(pyopenpano SYSTEM
#            PRIVATE ${PYTHON_INCLUDE_DIRS}
#            )
#endif()

#add_executable(stitchingfaster main.cpp)
# compiler options:

