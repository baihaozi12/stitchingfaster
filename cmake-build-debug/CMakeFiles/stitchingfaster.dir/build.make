# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/mnt/c/Users/Hao Bai/workspace/stitchingfaster"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/Hao Bai/workspace/stitchingfaster/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/stitchingfaster.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/stitchingfaster.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/stitchingfaster.dir/flags.make

CMakeFiles/stitchingfaster.dir/main.cpp.o: CMakeFiles/stitchingfaster.dir/flags.make
CMakeFiles/stitchingfaster.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Hao Bai/workspace/stitchingfaster/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/stitchingfaster.dir/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stitchingfaster.dir/main.cpp.o -c "/mnt/c/Users/Hao Bai/workspace/stitchingfaster/main.cpp"

CMakeFiles/stitchingfaster.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stitchingfaster.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Hao Bai/workspace/stitchingfaster/main.cpp" > CMakeFiles/stitchingfaster.dir/main.cpp.i

CMakeFiles/stitchingfaster.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stitchingfaster.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Hao Bai/workspace/stitchingfaster/main.cpp" -o CMakeFiles/stitchingfaster.dir/main.cpp.s

CMakeFiles/stitchingfaster.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/stitchingfaster.dir/main.cpp.o.requires

CMakeFiles/stitchingfaster.dir/main.cpp.o.provides: CMakeFiles/stitchingfaster.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/stitchingfaster.dir/build.make CMakeFiles/stitchingfaster.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/stitchingfaster.dir/main.cpp.o.provides

CMakeFiles/stitchingfaster.dir/main.cpp.o.provides.build: CMakeFiles/stitchingfaster.dir/main.cpp.o


# Object files for target stitchingfaster
stitchingfaster_OBJECTS = \
"CMakeFiles/stitchingfaster.dir/main.cpp.o"

# External object files for target stitchingfaster
stitchingfaster_EXTERNAL_OBJECTS =

stitchingfaster: CMakeFiles/stitchingfaster.dir/main.cpp.o
stitchingfaster: CMakeFiles/stitchingfaster.dir/build.make
stitchingfaster: CMakeFiles/stitchingfaster.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/Hao Bai/workspace/stitchingfaster/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable stitchingfaster"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stitchingfaster.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/stitchingfaster.dir/build: stitchingfaster

.PHONY : CMakeFiles/stitchingfaster.dir/build

CMakeFiles/stitchingfaster.dir/requires: CMakeFiles/stitchingfaster.dir/main.cpp.o.requires

.PHONY : CMakeFiles/stitchingfaster.dir/requires

CMakeFiles/stitchingfaster.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/stitchingfaster.dir/cmake_clean.cmake
.PHONY : CMakeFiles/stitchingfaster.dir/clean

CMakeFiles/stitchingfaster.dir/depend:
	cd "/mnt/c/Users/Hao Bai/workspace/stitchingfaster/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/Hao Bai/workspace/stitchingfaster" "/mnt/c/Users/Hao Bai/workspace/stitchingfaster" "/mnt/c/Users/Hao Bai/workspace/stitchingfaster/cmake-build-debug" "/mnt/c/Users/Hao Bai/workspace/stitchingfaster/cmake-build-debug" "/mnt/c/Users/Hao Bai/workspace/stitchingfaster/cmake-build-debug/CMakeFiles/stitchingfaster.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/stitchingfaster.dir/depend

