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
#file(GLOB SOURCES feature/*.cc stitch/*.cc lib/*.cc )
#
#
#add_library(stitchingfaster SOURCES)
add_executable(stitchingfaster main.cc
        feature/brief.cc feature/brief.hh
        feature/dist.cc feature/dist.hh
        feature/dog.cc feature/dog.hh
        feature/extrema.cc feature/extrema.hh
        feature/feature.cc feature/feature.hh
        feature/gaussian.cc feature/gaussian.hh
        feature/matcher.cc feature/matcher.hh
        feature/orientation.cc feature/orientation.hh
        feature/sift.cc feature/sift.hh
        common/common.hh
        lib/color.cc lib/color.hh
        lib/config.cc lib/config.hh
        lib/debugutils.cc lib/debugutils.hh
        lib/geometry.hh
        lib/imgio.cc
        lib/imgproc.cc lib/imgproc.hh
        lib/kdtree.cc lib/kdtree.hh
        lib/mat.h
        lib/matrix.cc lib/matrix.hh
        lib/planedrawer.cc lib/planedrawer.hh
        lib/polygon.cc lib/polygon.hh
        lib/timer.cc lib/timer.hh
        lib/utils.cc lib/utils.hh
        stitch/blender.cc stitch/blender.hh stitch/blender.hh.gch
        stitch/camera.cc stitch/camera.hh
        stitch/camera_estimator.cc stitch/camera_estimator.hh
        stitch/cylstitcher.cc stitch/cylstitcher.hh
        stitch/debug.cc
        stitch/homography.cc stitch/homography.hh
        stitch/imageref.hh
        stitch/incremental_bundle_adjuster.cc stitch/incremental_bundle_adjuster.hh
        stitch/match_info.hh
        stitch/multiband.cc stitch/multiband.hh
        stitch/projection.hh
        stitch/stitcher.cc stitch/stitcher.hh
        stitch/stitcher_image.cc stitch/stitcher_image.hh
        stitch/stitcherbase.cc stitch/stitcherbase.hh
        stitch/transform_estimate.cc stitch/transform_estimate.hh
        stitch/warp.cc stitch/warp.hh)
find_package(OpenCV REQUIRED)
#add_library(stitchingfaster ${SOURCES})	# TODO shared?
target_link_libraries(stitchingfaster ${JPEG_LIBRARY}  lodepng)
if (NOT JPEG_FOUND)
    target_compile_definitions(stitchingfaster PUBLIC DISABLE_JPEG )
#    target_compile_definitions(image-stitching PUBLIC DISABLE_JPEG)
endif()
find_package(PythonLibs)

add_library(pylittlepussy SHARED python/pybind.cc)
target_link_libraries(pylittlepussy openpano pybind11)
target_include_directories(pylittlepussy SYSTEM
            PRIVATE ${PYTHON_INCLUDE_DIRS}
            )
#if(PYTHONLIBS_FOUND AND BUILD_SHARED_LIBS)
#    add_library(pyopenpano SHARED python/pybind.cc)
#    target_link_libraries(pyopenpano openpano pybind11)
#    target_include_directories(pyopenpano SYSTEM
#            PRIVATE ${PYTHON_INCLUDE_DIRS}
#            )
#endif()

#add_executable(stitchingfaster main.cpp)
# compiler options:

