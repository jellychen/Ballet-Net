# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/shared/Ballet-Net-Github

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/shared/Ballet-Net-Github/Build

# Include any dependencies generated for this target.
include LoTrace/CMakeFiles/LoTrace.dir/depend.make

# Include the progress variables for this target.
include LoTrace/CMakeFiles/LoTrace.dir/progress.make

# Include the compile flags for this target's objects.
include LoTrace/CMakeFiles/LoTrace.dir/flags.make

LoTrace/CMakeFiles/LoTrace.dir/LoTrace.o: LoTrace/CMakeFiles/LoTrace.dir/flags.make
LoTrace/CMakeFiles/LoTrace.dir/LoTrace.o: ../Libs/LoTrace/LoTrace.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/shared/Ballet-Net-Github/Build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object LoTrace/CMakeFiles/LoTrace.dir/LoTrace.o"
	cd /mnt/shared/Ballet-Net-Github/Build/LoTrace && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/LoTrace.dir/LoTrace.o -c /mnt/shared/Ballet-Net-Github/Libs/LoTrace/LoTrace.cc

LoTrace/CMakeFiles/LoTrace.dir/LoTrace.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LoTrace.dir/LoTrace.i"
	cd /mnt/shared/Ballet-Net-Github/Build/LoTrace && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/shared/Ballet-Net-Github/Libs/LoTrace/LoTrace.cc > CMakeFiles/LoTrace.dir/LoTrace.i

LoTrace/CMakeFiles/LoTrace.dir/LoTrace.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LoTrace.dir/LoTrace.s"
	cd /mnt/shared/Ballet-Net-Github/Build/LoTrace && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/shared/Ballet-Net-Github/Libs/LoTrace/LoTrace.cc -o CMakeFiles/LoTrace.dir/LoTrace.s

LoTrace/CMakeFiles/LoTrace.dir/LoTrace.o.requires:
.PHONY : LoTrace/CMakeFiles/LoTrace.dir/LoTrace.o.requires

LoTrace/CMakeFiles/LoTrace.dir/LoTrace.o.provides: LoTrace/CMakeFiles/LoTrace.dir/LoTrace.o.requires
	$(MAKE) -f LoTrace/CMakeFiles/LoTrace.dir/build.make LoTrace/CMakeFiles/LoTrace.dir/LoTrace.o.provides.build
.PHONY : LoTrace/CMakeFiles/LoTrace.dir/LoTrace.o.provides

LoTrace/CMakeFiles/LoTrace.dir/LoTrace.o.provides.build: LoTrace/CMakeFiles/LoTrace.dir/LoTrace.o

# Object files for target LoTrace
LoTrace_OBJECTS = \
"CMakeFiles/LoTrace.dir/LoTrace.o"

# External object files for target LoTrace
LoTrace_EXTERNAL_OBJECTS =

LoTrace/libLoTrace.a: LoTrace/CMakeFiles/LoTrace.dir/LoTrace.o
LoTrace/libLoTrace.a: LoTrace/CMakeFiles/LoTrace.dir/build.make
LoTrace/libLoTrace.a: LoTrace/CMakeFiles/LoTrace.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libLoTrace.a"
	cd /mnt/shared/Ballet-Net-Github/Build/LoTrace && $(CMAKE_COMMAND) -P CMakeFiles/LoTrace.dir/cmake_clean_target.cmake
	cd /mnt/shared/Ballet-Net-Github/Build/LoTrace && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LoTrace.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
LoTrace/CMakeFiles/LoTrace.dir/build: LoTrace/libLoTrace.a
.PHONY : LoTrace/CMakeFiles/LoTrace.dir/build

LoTrace/CMakeFiles/LoTrace.dir/requires: LoTrace/CMakeFiles/LoTrace.dir/LoTrace.o.requires
.PHONY : LoTrace/CMakeFiles/LoTrace.dir/requires

LoTrace/CMakeFiles/LoTrace.dir/clean:
	cd /mnt/shared/Ballet-Net-Github/Build/LoTrace && $(CMAKE_COMMAND) -P CMakeFiles/LoTrace.dir/cmake_clean.cmake
.PHONY : LoTrace/CMakeFiles/LoTrace.dir/clean

LoTrace/CMakeFiles/LoTrace.dir/depend:
	cd /mnt/shared/Ballet-Net-Github/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/shared/Ballet-Net-Github /mnt/shared/Ballet-Net-Github/Libs/LoTrace /mnt/shared/Ballet-Net-Github/Build /mnt/shared/Ballet-Net-Github/Build/LoTrace /mnt/shared/Ballet-Net-Github/Build/LoTrace/CMakeFiles/LoTrace.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : LoTrace/CMakeFiles/LoTrace.dir/depend

