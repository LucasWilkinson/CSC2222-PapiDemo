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
CMAKE_SOURCE_DIR = /home/behrooz/Desktop/CSC2222-PapiDemo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/behrooz/Desktop/CSC2222-PapiDemo/build

# Include any dependencies generated for this target.
include CMakeFiles/low_level_demo_vec_flops.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/low_level_demo_vec_flops.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/low_level_demo_vec_flops.dir/flags.make

CMakeFiles/low_level_demo_vec_flops.dir/src/low_level_demo_vec_flops.cpp.o: CMakeFiles/low_level_demo_vec_flops.dir/flags.make
CMakeFiles/low_level_demo_vec_flops.dir/src/low_level_demo_vec_flops.cpp.o: src/low_level_demo_vec_flops.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/behrooz/Desktop/CSC2222-PapiDemo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/low_level_demo_vec_flops.dir/src/low_level_demo_vec_flops.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/low_level_demo_vec_flops.dir/src/low_level_demo_vec_flops.cpp.o -c /home/behrooz/Desktop/CSC2222-PapiDemo/build/src/low_level_demo_vec_flops.cpp

CMakeFiles/low_level_demo_vec_flops.dir/src/low_level_demo_vec_flops.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/low_level_demo_vec_flops.dir/src/low_level_demo_vec_flops.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/behrooz/Desktop/CSC2222-PapiDemo/build/src/low_level_demo_vec_flops.cpp > CMakeFiles/low_level_demo_vec_flops.dir/src/low_level_demo_vec_flops.cpp.i

CMakeFiles/low_level_demo_vec_flops.dir/src/low_level_demo_vec_flops.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/low_level_demo_vec_flops.dir/src/low_level_demo_vec_flops.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/behrooz/Desktop/CSC2222-PapiDemo/build/src/low_level_demo_vec_flops.cpp -o CMakeFiles/low_level_demo_vec_flops.dir/src/low_level_demo_vec_flops.cpp.s

CMakeFiles/low_level_demo_vec_flops.dir/src/low_level_demo_vec_flops.cpp.o.requires:

.PHONY : CMakeFiles/low_level_demo_vec_flops.dir/src/low_level_demo_vec_flops.cpp.o.requires

CMakeFiles/low_level_demo_vec_flops.dir/src/low_level_demo_vec_flops.cpp.o.provides: CMakeFiles/low_level_demo_vec_flops.dir/src/low_level_demo_vec_flops.cpp.o.requires
	$(MAKE) -f CMakeFiles/low_level_demo_vec_flops.dir/build.make CMakeFiles/low_level_demo_vec_flops.dir/src/low_level_demo_vec_flops.cpp.o.provides.build
.PHONY : CMakeFiles/low_level_demo_vec_flops.dir/src/low_level_demo_vec_flops.cpp.o.provides

CMakeFiles/low_level_demo_vec_flops.dir/src/low_level_demo_vec_flops.cpp.o.provides.build: CMakeFiles/low_level_demo_vec_flops.dir/src/low_level_demo_vec_flops.cpp.o


# Object files for target low_level_demo_vec_flops
low_level_demo_vec_flops_OBJECTS = \
"CMakeFiles/low_level_demo_vec_flops.dir/src/low_level_demo_vec_flops.cpp.o"

# External object files for target low_level_demo_vec_flops
low_level_demo_vec_flops_EXTERNAL_OBJECTS =

low_level_demo_vec_flops: CMakeFiles/low_level_demo_vec_flops.dir/src/low_level_demo_vec_flops.cpp.o
low_level_demo_vec_flops: CMakeFiles/low_level_demo_vec_flops.dir/build.make
low_level_demo_vec_flops: /home/behrooz/Software/PAPI/lib/libpapi.so
low_level_demo_vec_flops: CMakeFiles/low_level_demo_vec_flops.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/behrooz/Desktop/CSC2222-PapiDemo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable low_level_demo_vec_flops"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/low_level_demo_vec_flops.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/low_level_demo_vec_flops.dir/build: low_level_demo_vec_flops

.PHONY : CMakeFiles/low_level_demo_vec_flops.dir/build

CMakeFiles/low_level_demo_vec_flops.dir/requires: CMakeFiles/low_level_demo_vec_flops.dir/src/low_level_demo_vec_flops.cpp.o.requires

.PHONY : CMakeFiles/low_level_demo_vec_flops.dir/requires

CMakeFiles/low_level_demo_vec_flops.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/low_level_demo_vec_flops.dir/cmake_clean.cmake
.PHONY : CMakeFiles/low_level_demo_vec_flops.dir/clean

CMakeFiles/low_level_demo_vec_flops.dir/depend:
	cd /home/behrooz/Desktop/CSC2222-PapiDemo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/behrooz/Desktop/CSC2222-PapiDemo /home/behrooz/Desktop/CSC2222-PapiDemo /home/behrooz/Desktop/CSC2222-PapiDemo/build /home/behrooz/Desktop/CSC2222-PapiDemo/build /home/behrooz/Desktop/CSC2222-PapiDemo/build/CMakeFiles/low_level_demo_vec_flops.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/low_level_demo_vec_flops.dir/depend

