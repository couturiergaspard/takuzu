# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/gaspardcouturier/Desktop/L2/takuzu-03d

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/gaspardcouturier/Desktop/L2/takuzu-03d/build

# Include any dependencies generated for this target.
include CMakeFiles/game_ext_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/game_ext_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/game_ext_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/game_ext_test.dir/flags.make

CMakeFiles/game_ext_test.dir/game_ext_test.c.o: CMakeFiles/game_ext_test.dir/flags.make
CMakeFiles/game_ext_test.dir/game_ext_test.c.o: /Users/gaspardcouturier/Desktop/L2/takuzu-03d/game_ext_test.c
CMakeFiles/game_ext_test.dir/game_ext_test.c.o: CMakeFiles/game_ext_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gaspardcouturier/Desktop/L2/takuzu-03d/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/game_ext_test.dir/game_ext_test.c.o"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/game_ext_test.dir/game_ext_test.c.o -MF CMakeFiles/game_ext_test.dir/game_ext_test.c.o.d -o CMakeFiles/game_ext_test.dir/game_ext_test.c.o -c /Users/gaspardcouturier/Desktop/L2/takuzu-03d/game_ext_test.c

CMakeFiles/game_ext_test.dir/game_ext_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/game_ext_test.dir/game_ext_test.c.i"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/gaspardcouturier/Desktop/L2/takuzu-03d/game_ext_test.c > CMakeFiles/game_ext_test.dir/game_ext_test.c.i

CMakeFiles/game_ext_test.dir/game_ext_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/game_ext_test.dir/game_ext_test.c.s"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/gaspardcouturier/Desktop/L2/takuzu-03d/game_ext_test.c -o CMakeFiles/game_ext_test.dir/game_ext_test.c.s

# Object files for target game_ext_test
game_ext_test_OBJECTS = \
"CMakeFiles/game_ext_test.dir/game_ext_test.c.o"

# External object files for target game_ext_test
game_ext_test_EXTERNAL_OBJECTS =

game_ext_test: CMakeFiles/game_ext_test.dir/game_ext_test.c.o
game_ext_test: CMakeFiles/game_ext_test.dir/build.make
game_ext_test: libgame.a
game_ext_test: CMakeFiles/game_ext_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/gaspardcouturier/Desktop/L2/takuzu-03d/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable game_ext_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/game_ext_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/game_ext_test.dir/build: game_ext_test
.PHONY : CMakeFiles/game_ext_test.dir/build

CMakeFiles/game_ext_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/game_ext_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/game_ext_test.dir/clean

CMakeFiles/game_ext_test.dir/depend:
	cd /Users/gaspardcouturier/Desktop/L2/takuzu-03d/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/gaspardcouturier/Desktop/L2/takuzu-03d /Users/gaspardcouturier/Desktop/L2/takuzu-03d /Users/gaspardcouturier/Desktop/L2/takuzu-03d/build /Users/gaspardcouturier/Desktop/L2/takuzu-03d/build /Users/gaspardcouturier/Desktop/L2/takuzu-03d/build/CMakeFiles/game_ext_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/game_ext_test.dir/depend

