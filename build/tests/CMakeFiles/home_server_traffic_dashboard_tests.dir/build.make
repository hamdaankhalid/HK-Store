# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.21.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.21.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/hamdaankhalid/home-server-traffic-dashboard

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/hamdaankhalid/home-server-traffic-dashboard/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/flags.make

tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/logger-tests.cpp.o: tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/flags.make
tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/logger-tests.cpp.o: ../tests/logger-tests.cpp
tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/logger-tests.cpp.o: tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hamdaankhalid/home-server-traffic-dashboard/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/logger-tests.cpp.o"
	cd /Users/hamdaankhalid/home-server-traffic-dashboard/build/tests && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/logger-tests.cpp.o -MF CMakeFiles/home_server_traffic_dashboard_tests.dir/logger-tests.cpp.o.d -o CMakeFiles/home_server_traffic_dashboard_tests.dir/logger-tests.cpp.o -c /Users/hamdaankhalid/home-server-traffic-dashboard/tests/logger-tests.cpp

tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/logger-tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/home_server_traffic_dashboard_tests.dir/logger-tests.cpp.i"
	cd /Users/hamdaankhalid/home-server-traffic-dashboard/build/tests && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hamdaankhalid/home-server-traffic-dashboard/tests/logger-tests.cpp > CMakeFiles/home_server_traffic_dashboard_tests.dir/logger-tests.cpp.i

tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/logger-tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/home_server_traffic_dashboard_tests.dir/logger-tests.cpp.s"
	cd /Users/hamdaankhalid/home-server-traffic-dashboard/build/tests && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hamdaankhalid/home-server-traffic-dashboard/tests/logger-tests.cpp -o CMakeFiles/home_server_traffic_dashboard_tests.dir/logger-tests.cpp.s

# Object files for target home_server_traffic_dashboard_tests
home_server_traffic_dashboard_tests_OBJECTS = \
"CMakeFiles/home_server_traffic_dashboard_tests.dir/logger-tests.cpp.o"

# External object files for target home_server_traffic_dashboard_tests
home_server_traffic_dashboard_tests_EXTERNAL_OBJECTS =

tests/home_server_traffic_dashboard_tests: tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/logger-tests.cpp.o
tests/home_server_traffic_dashboard_tests: tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/build.make
tests/home_server_traffic_dashboard_tests: lib/libgtest_main.a
tests/home_server_traffic_dashboard_tests: logger/liblogger.a
tests/home_server_traffic_dashboard_tests: lib/libgtest.a
tests/home_server_traffic_dashboard_tests: tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/hamdaankhalid/home-server-traffic-dashboard/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable home_server_traffic_dashboard_tests"
	cd /Users/hamdaankhalid/home-server-traffic-dashboard/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/home_server_traffic_dashboard_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/build: tests/home_server_traffic_dashboard_tests
.PHONY : tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/build

tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/clean:
	cd /Users/hamdaankhalid/home-server-traffic-dashboard/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/home_server_traffic_dashboard_tests.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/clean

tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/depend:
	cd /Users/hamdaankhalid/home-server-traffic-dashboard/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hamdaankhalid/home-server-traffic-dashboard /Users/hamdaankhalid/home-server-traffic-dashboard/tests /Users/hamdaankhalid/home-server-traffic-dashboard/build /Users/hamdaankhalid/home-server-traffic-dashboard/build/tests /Users/hamdaankhalid/home-server-traffic-dashboard/build/tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/home_server_traffic_dashboard_tests.dir/depend

