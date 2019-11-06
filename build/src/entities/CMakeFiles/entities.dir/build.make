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
CMAKE_SOURCE_DIR = /home/gxiv/projects/games/origins/orgengine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gxiv/projects/games/origins/orgengine/build

# Include any dependencies generated for this target.
include src/entities/CMakeFiles/entities.dir/depend.make

# Include the progress variables for this target.
include src/entities/CMakeFiles/entities.dir/progress.make

# Include the compile flags for this target's objects.
include src/entities/CMakeFiles/entities.dir/flags.make

src/entities/CMakeFiles/entities.dir/Entity.cpp.o: src/entities/CMakeFiles/entities.dir/flags.make
src/entities/CMakeFiles/entities.dir/Entity.cpp.o: ../src/entities/Entity.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gxiv/projects/games/origins/orgengine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/entities/CMakeFiles/entities.dir/Entity.cpp.o"
	cd /home/gxiv/projects/games/origins/orgengine/build/src/entities && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/entities.dir/Entity.cpp.o -c /home/gxiv/projects/games/origins/orgengine/src/entities/Entity.cpp

src/entities/CMakeFiles/entities.dir/Entity.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/entities.dir/Entity.cpp.i"
	cd /home/gxiv/projects/games/origins/orgengine/build/src/entities && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gxiv/projects/games/origins/orgengine/src/entities/Entity.cpp > CMakeFiles/entities.dir/Entity.cpp.i

src/entities/CMakeFiles/entities.dir/Entity.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/entities.dir/Entity.cpp.s"
	cd /home/gxiv/projects/games/origins/orgengine/build/src/entities && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gxiv/projects/games/origins/orgengine/src/entities/Entity.cpp -o CMakeFiles/entities.dir/Entity.cpp.s

src/entities/CMakeFiles/entities.dir/Entity.cpp.o.requires:

.PHONY : src/entities/CMakeFiles/entities.dir/Entity.cpp.o.requires

src/entities/CMakeFiles/entities.dir/Entity.cpp.o.provides: src/entities/CMakeFiles/entities.dir/Entity.cpp.o.requires
	$(MAKE) -f src/entities/CMakeFiles/entities.dir/build.make src/entities/CMakeFiles/entities.dir/Entity.cpp.o.provides.build
.PHONY : src/entities/CMakeFiles/entities.dir/Entity.cpp.o.provides

src/entities/CMakeFiles/entities.dir/Entity.cpp.o.provides.build: src/entities/CMakeFiles/entities.dir/Entity.cpp.o


# Object files for target entities
entities_OBJECTS = \
"CMakeFiles/entities.dir/Entity.cpp.o"

# External object files for target entities
entities_EXTERNAL_OBJECTS =

src/entities/libentities.a: src/entities/CMakeFiles/entities.dir/Entity.cpp.o
src/entities/libentities.a: src/entities/CMakeFiles/entities.dir/build.make
src/entities/libentities.a: src/entities/CMakeFiles/entities.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gxiv/projects/games/origins/orgengine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libentities.a"
	cd /home/gxiv/projects/games/origins/orgengine/build/src/entities && $(CMAKE_COMMAND) -P CMakeFiles/entities.dir/cmake_clean_target.cmake
	cd /home/gxiv/projects/games/origins/orgengine/build/src/entities && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/entities.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/entities/CMakeFiles/entities.dir/build: src/entities/libentities.a

.PHONY : src/entities/CMakeFiles/entities.dir/build

src/entities/CMakeFiles/entities.dir/requires: src/entities/CMakeFiles/entities.dir/Entity.cpp.o.requires

.PHONY : src/entities/CMakeFiles/entities.dir/requires

src/entities/CMakeFiles/entities.dir/clean:
	cd /home/gxiv/projects/games/origins/orgengine/build/src/entities && $(CMAKE_COMMAND) -P CMakeFiles/entities.dir/cmake_clean.cmake
.PHONY : src/entities/CMakeFiles/entities.dir/clean

src/entities/CMakeFiles/entities.dir/depend:
	cd /home/gxiv/projects/games/origins/orgengine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gxiv/projects/games/origins/orgengine /home/gxiv/projects/games/origins/orgengine/src/entities /home/gxiv/projects/games/origins/orgengine/build /home/gxiv/projects/games/origins/orgengine/build/src/entities /home/gxiv/projects/games/origins/orgengine/build/src/entities/CMakeFiles/entities.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/entities/CMakeFiles/entities.dir/depend

