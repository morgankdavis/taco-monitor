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

# Include any dependencies generated for this target.
include external/serial/tests/CMakeFiles/serial-test-timer.dir/depend.make

# Include the progress variables for this target.
include external/serial/tests/CMakeFiles/serial-test-timer.dir/progress.make

# Include the compile flags for this target's objects.
include external/serial/tests/CMakeFiles/serial-test-timer.dir/flags.make

external/serial/tests/CMakeFiles/serial-test-timer.dir/unit/unix_timer_tests.cc.o: external/serial/tests/CMakeFiles/serial-test-timer.dir/flags.make
external/serial/tests/CMakeFiles/serial-test-timer.dir/unit/unix_timer_tests.cc.o: ../external/serial/tests/unit/unix_timer_tests.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/taco-monitor/build-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object external/serial/tests/CMakeFiles/serial-test-timer.dir/unit/unix_timer_tests.cc.o"
	cd /home/pi/taco-monitor/build-pi/external/serial/tests && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/serial-test-timer.dir/unit/unix_timer_tests.cc.o -c /home/pi/taco-monitor/external/serial/tests/unit/unix_timer_tests.cc

external/serial/tests/CMakeFiles/serial-test-timer.dir/unit/unix_timer_tests.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serial-test-timer.dir/unit/unix_timer_tests.cc.i"
	cd /home/pi/taco-monitor/build-pi/external/serial/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/taco-monitor/external/serial/tests/unit/unix_timer_tests.cc > CMakeFiles/serial-test-timer.dir/unit/unix_timer_tests.cc.i

external/serial/tests/CMakeFiles/serial-test-timer.dir/unit/unix_timer_tests.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serial-test-timer.dir/unit/unix_timer_tests.cc.s"
	cd /home/pi/taco-monitor/build-pi/external/serial/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/taco-monitor/external/serial/tests/unit/unix_timer_tests.cc -o CMakeFiles/serial-test-timer.dir/unit/unix_timer_tests.cc.s

external/serial/tests/CMakeFiles/serial-test-timer.dir/unit/unix_timer_tests.cc.o.requires:

.PHONY : external/serial/tests/CMakeFiles/serial-test-timer.dir/unit/unix_timer_tests.cc.o.requires

external/serial/tests/CMakeFiles/serial-test-timer.dir/unit/unix_timer_tests.cc.o.provides: external/serial/tests/CMakeFiles/serial-test-timer.dir/unit/unix_timer_tests.cc.o.requires
	$(MAKE) -f external/serial/tests/CMakeFiles/serial-test-timer.dir/build.make external/serial/tests/CMakeFiles/serial-test-timer.dir/unit/unix_timer_tests.cc.o.provides.build
.PHONY : external/serial/tests/CMakeFiles/serial-test-timer.dir/unit/unix_timer_tests.cc.o.provides

external/serial/tests/CMakeFiles/serial-test-timer.dir/unit/unix_timer_tests.cc.o.provides.build: external/serial/tests/CMakeFiles/serial-test-timer.dir/unit/unix_timer_tests.cc.o


# Object files for target serial-test-timer
serial__test__timer_OBJECTS = \
"CMakeFiles/serial-test-timer.dir/unit/unix_timer_tests.cc.o"

# External object files for target serial-test-timer
serial__test__timer_EXTERNAL_OBJECTS =

devel/lib/serial/serial-test-timer: external/serial/tests/CMakeFiles/serial-test-timer.dir/unit/unix_timer_tests.cc.o
devel/lib/serial/serial-test-timer: external/serial/tests/CMakeFiles/serial-test-timer.dir/build.make
devel/lib/serial/serial-test-timer: external/serial/libgtest.so
devel/lib/serial/serial-test-timer: devel/lib/libserial.so
devel/lib/serial/serial-test-timer: external/serial/tests/CMakeFiles/serial-test-timer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/taco-monitor/build-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../devel/lib/serial/serial-test-timer"
	cd /home/pi/taco-monitor/build-pi/external/serial/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serial-test-timer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/serial/tests/CMakeFiles/serial-test-timer.dir/build: devel/lib/serial/serial-test-timer

.PHONY : external/serial/tests/CMakeFiles/serial-test-timer.dir/build

external/serial/tests/CMakeFiles/serial-test-timer.dir/requires: external/serial/tests/CMakeFiles/serial-test-timer.dir/unit/unix_timer_tests.cc.o.requires

.PHONY : external/serial/tests/CMakeFiles/serial-test-timer.dir/requires

external/serial/tests/CMakeFiles/serial-test-timer.dir/clean:
	cd /home/pi/taco-monitor/build-pi/external/serial/tests && $(CMAKE_COMMAND) -P CMakeFiles/serial-test-timer.dir/cmake_clean.cmake
.PHONY : external/serial/tests/CMakeFiles/serial-test-timer.dir/clean

external/serial/tests/CMakeFiles/serial-test-timer.dir/depend:
	cd /home/pi/taco-monitor/build-pi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/taco-monitor /home/pi/taco-monitor/external/serial/tests /home/pi/taco-monitor/build-pi /home/pi/taco-monitor/build-pi/external/serial/tests /home/pi/taco-monitor/build-pi/external/serial/tests/CMakeFiles/serial-test-timer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/serial/tests/CMakeFiles/serial-test-timer.dir/depend
