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
CMAKE_SOURCE_DIR = /home/pi/taco-monitor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/taco-monitor/build-pi

# Utility rule file for run_tests_serial_gtest_serial-test.

# Include the progress variables for this target.
include external/serial/tests/CMakeFiles/run_tests_serial_gtest_serial-test.dir/progress.make

external/serial/tests/CMakeFiles/run_tests_serial_gtest_serial-test:
	cd /home/pi/taco-monitor/build-pi/external/serial/tests && ../../../catkin_generated/env_cached.sh /usr/bin/python /usr/share/catkin/cmake/test/run_tests.py /home/pi/taco-monitor/build-pi/test_results/serial/gtest-serial-test.xml /home/pi/taco-monitor/build-pi/devel/lib/serial/serial-test\ --gtest_output=xml:/home/pi/taco-monitor/build-pi/test_results/serial/gtest-serial-test.xml

run_tests_serial_gtest_serial-test: external/serial/tests/CMakeFiles/run_tests_serial_gtest_serial-test
run_tests_serial_gtest_serial-test: external/serial/tests/CMakeFiles/run_tests_serial_gtest_serial-test.dir/build.make

.PHONY : run_tests_serial_gtest_serial-test

# Rule to build all files generated by this target.
external/serial/tests/CMakeFiles/run_tests_serial_gtest_serial-test.dir/build: run_tests_serial_gtest_serial-test

.PHONY : external/serial/tests/CMakeFiles/run_tests_serial_gtest_serial-test.dir/build

external/serial/tests/CMakeFiles/run_tests_serial_gtest_serial-test.dir/clean:
	cd /home/pi/taco-monitor/build-pi/external/serial/tests && $(CMAKE_COMMAND) -P CMakeFiles/run_tests_serial_gtest_serial-test.dir/cmake_clean.cmake
.PHONY : external/serial/tests/CMakeFiles/run_tests_serial_gtest_serial-test.dir/clean

external/serial/tests/CMakeFiles/run_tests_serial_gtest_serial-test.dir/depend:
	cd /home/pi/taco-monitor/build-pi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/taco-monitor /home/pi/taco-monitor/external/serial/tests /home/pi/taco-monitor/build-pi /home/pi/taco-monitor/build-pi/external/serial/tests /home/pi/taco-monitor/build-pi/external/serial/tests/CMakeFiles/run_tests_serial_gtest_serial-test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/serial/tests/CMakeFiles/run_tests_serial_gtest_serial-test.dir/depend

