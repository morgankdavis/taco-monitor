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
include external/serial/CMakeFiles/serial.dir/depend.make

# Include the progress variables for this target.
include external/serial/CMakeFiles/serial.dir/progress.make

# Include the compile flags for this target's objects.
include external/serial/CMakeFiles/serial.dir/flags.make

external/serial/CMakeFiles/serial.dir/src/serial.cc.o: external/serial/CMakeFiles/serial.dir/flags.make
external/serial/CMakeFiles/serial.dir/src/serial.cc.o: ../external/serial/src/serial.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/taco-monitor/build-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object external/serial/CMakeFiles/serial.dir/src/serial.cc.o"
	cd /home/pi/taco-monitor/build-pi/external/serial && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/serial.dir/src/serial.cc.o -c /home/pi/taco-monitor/external/serial/src/serial.cc

external/serial/CMakeFiles/serial.dir/src/serial.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serial.dir/src/serial.cc.i"
	cd /home/pi/taco-monitor/build-pi/external/serial && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/taco-monitor/external/serial/src/serial.cc > CMakeFiles/serial.dir/src/serial.cc.i

external/serial/CMakeFiles/serial.dir/src/serial.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serial.dir/src/serial.cc.s"
	cd /home/pi/taco-monitor/build-pi/external/serial && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/taco-monitor/external/serial/src/serial.cc -o CMakeFiles/serial.dir/src/serial.cc.s

external/serial/CMakeFiles/serial.dir/src/serial.cc.o.requires:

.PHONY : external/serial/CMakeFiles/serial.dir/src/serial.cc.o.requires

external/serial/CMakeFiles/serial.dir/src/serial.cc.o.provides: external/serial/CMakeFiles/serial.dir/src/serial.cc.o.requires
	$(MAKE) -f external/serial/CMakeFiles/serial.dir/build.make external/serial/CMakeFiles/serial.dir/src/serial.cc.o.provides.build
.PHONY : external/serial/CMakeFiles/serial.dir/src/serial.cc.o.provides

external/serial/CMakeFiles/serial.dir/src/serial.cc.o.provides.build: external/serial/CMakeFiles/serial.dir/src/serial.cc.o


external/serial/CMakeFiles/serial.dir/src/impl/unix.cc.o: external/serial/CMakeFiles/serial.dir/flags.make
external/serial/CMakeFiles/serial.dir/src/impl/unix.cc.o: ../external/serial/src/impl/unix.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/taco-monitor/build-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object external/serial/CMakeFiles/serial.dir/src/impl/unix.cc.o"
	cd /home/pi/taco-monitor/build-pi/external/serial && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/serial.dir/src/impl/unix.cc.o -c /home/pi/taco-monitor/external/serial/src/impl/unix.cc

external/serial/CMakeFiles/serial.dir/src/impl/unix.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serial.dir/src/impl/unix.cc.i"
	cd /home/pi/taco-monitor/build-pi/external/serial && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/taco-monitor/external/serial/src/impl/unix.cc > CMakeFiles/serial.dir/src/impl/unix.cc.i

external/serial/CMakeFiles/serial.dir/src/impl/unix.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serial.dir/src/impl/unix.cc.s"
	cd /home/pi/taco-monitor/build-pi/external/serial && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/taco-monitor/external/serial/src/impl/unix.cc -o CMakeFiles/serial.dir/src/impl/unix.cc.s

external/serial/CMakeFiles/serial.dir/src/impl/unix.cc.o.requires:

.PHONY : external/serial/CMakeFiles/serial.dir/src/impl/unix.cc.o.requires

external/serial/CMakeFiles/serial.dir/src/impl/unix.cc.o.provides: external/serial/CMakeFiles/serial.dir/src/impl/unix.cc.o.requires
	$(MAKE) -f external/serial/CMakeFiles/serial.dir/build.make external/serial/CMakeFiles/serial.dir/src/impl/unix.cc.o.provides.build
.PHONY : external/serial/CMakeFiles/serial.dir/src/impl/unix.cc.o.provides

external/serial/CMakeFiles/serial.dir/src/impl/unix.cc.o.provides.build: external/serial/CMakeFiles/serial.dir/src/impl/unix.cc.o


external/serial/CMakeFiles/serial.dir/src/impl/list_ports/list_ports_linux.cc.o: external/serial/CMakeFiles/serial.dir/flags.make
external/serial/CMakeFiles/serial.dir/src/impl/list_ports/list_ports_linux.cc.o: ../external/serial/src/impl/list_ports/list_ports_linux.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/taco-monitor/build-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object external/serial/CMakeFiles/serial.dir/src/impl/list_ports/list_ports_linux.cc.o"
	cd /home/pi/taco-monitor/build-pi/external/serial && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/serial.dir/src/impl/list_ports/list_ports_linux.cc.o -c /home/pi/taco-monitor/external/serial/src/impl/list_ports/list_ports_linux.cc

external/serial/CMakeFiles/serial.dir/src/impl/list_ports/list_ports_linux.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serial.dir/src/impl/list_ports/list_ports_linux.cc.i"
	cd /home/pi/taco-monitor/build-pi/external/serial && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/taco-monitor/external/serial/src/impl/list_ports/list_ports_linux.cc > CMakeFiles/serial.dir/src/impl/list_ports/list_ports_linux.cc.i

external/serial/CMakeFiles/serial.dir/src/impl/list_ports/list_ports_linux.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serial.dir/src/impl/list_ports/list_ports_linux.cc.s"
	cd /home/pi/taco-monitor/build-pi/external/serial && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/taco-monitor/external/serial/src/impl/list_ports/list_ports_linux.cc -o CMakeFiles/serial.dir/src/impl/list_ports/list_ports_linux.cc.s

external/serial/CMakeFiles/serial.dir/src/impl/list_ports/list_ports_linux.cc.o.requires:

.PHONY : external/serial/CMakeFiles/serial.dir/src/impl/list_ports/list_ports_linux.cc.o.requires

external/serial/CMakeFiles/serial.dir/src/impl/list_ports/list_ports_linux.cc.o.provides: external/serial/CMakeFiles/serial.dir/src/impl/list_ports/list_ports_linux.cc.o.requires
	$(MAKE) -f external/serial/CMakeFiles/serial.dir/build.make external/serial/CMakeFiles/serial.dir/src/impl/list_ports/list_ports_linux.cc.o.provides.build
.PHONY : external/serial/CMakeFiles/serial.dir/src/impl/list_ports/list_ports_linux.cc.o.provides

external/serial/CMakeFiles/serial.dir/src/impl/list_ports/list_ports_linux.cc.o.provides.build: external/serial/CMakeFiles/serial.dir/src/impl/list_ports/list_ports_linux.cc.o


# Object files for target serial
serial_OBJECTS = \
"CMakeFiles/serial.dir/src/serial.cc.o" \
"CMakeFiles/serial.dir/src/impl/unix.cc.o" \
"CMakeFiles/serial.dir/src/impl/list_ports/list_ports_linux.cc.o"

# External object files for target serial
serial_EXTERNAL_OBJECTS =

devel/lib/libserial.so: external/serial/CMakeFiles/serial.dir/src/serial.cc.o
devel/lib/libserial.so: external/serial/CMakeFiles/serial.dir/src/impl/unix.cc.o
devel/lib/libserial.so: external/serial/CMakeFiles/serial.dir/src/impl/list_ports/list_ports_linux.cc.o
devel/lib/libserial.so: external/serial/CMakeFiles/serial.dir/build.make
devel/lib/libserial.so: external/serial/CMakeFiles/serial.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/taco-monitor/build-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library ../../devel/lib/libserial.so"
	cd /home/pi/taco-monitor/build-pi/external/serial && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serial.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/serial/CMakeFiles/serial.dir/build: devel/lib/libserial.so

.PHONY : external/serial/CMakeFiles/serial.dir/build

external/serial/CMakeFiles/serial.dir/requires: external/serial/CMakeFiles/serial.dir/src/serial.cc.o.requires
external/serial/CMakeFiles/serial.dir/requires: external/serial/CMakeFiles/serial.dir/src/impl/unix.cc.o.requires
external/serial/CMakeFiles/serial.dir/requires: external/serial/CMakeFiles/serial.dir/src/impl/list_ports/list_ports_linux.cc.o.requires

.PHONY : external/serial/CMakeFiles/serial.dir/requires

external/serial/CMakeFiles/serial.dir/clean:
	cd /home/pi/taco-monitor/build-pi/external/serial && $(CMAKE_COMMAND) -P CMakeFiles/serial.dir/cmake_clean.cmake
.PHONY : external/serial/CMakeFiles/serial.dir/clean

external/serial/CMakeFiles/serial.dir/depend:
	cd /home/pi/taco-monitor/build-pi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/taco-monitor /home/pi/taco-monitor/external/serial /home/pi/taco-monitor/build-pi /home/pi/taco-monitor/build-pi/external/serial /home/pi/taco-monitor/build-pi/external/serial/CMakeFiles/serial.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/serial/CMakeFiles/serial.dir/depend

