# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_SOURCE_DIR = /mnt/Crate/taco-monitor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/Crate/taco-monitor/build-pi

# Utility rule file for tests.

# Include the progress variables for this target.
include external/serial/CMakeFiles/tests.dir/progress.make

tests: external/serial/CMakeFiles/tests.dir/build.make

.PHONY : tests

# Rule to build all files generated by this target.
external/serial/CMakeFiles/tests.dir/build: tests

.PHONY : external/serial/CMakeFiles/tests.dir/build

external/serial/CMakeFiles/tests.dir/clean:
	cd /mnt/Crate/taco-monitor/build-pi/external/serial && $(CMAKE_COMMAND) -P CMakeFiles/tests.dir/cmake_clean.cmake
.PHONY : external/serial/CMakeFiles/tests.dir/clean

external/serial/CMakeFiles/tests.dir/depend:
	cd /mnt/Crate/taco-monitor/build-pi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/Crate/taco-monitor /mnt/Crate/taco-monitor/external/serial /mnt/Crate/taco-monitor/build-pi /mnt/Crate/taco-monitor/build-pi/external/serial /mnt/Crate/taco-monitor/build-pi/external/serial/CMakeFiles/tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/serial/CMakeFiles/tests.dir/depend

