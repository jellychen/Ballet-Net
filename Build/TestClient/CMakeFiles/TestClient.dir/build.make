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
include TestClient/CMakeFiles/TestClient.dir/depend.make

# Include the progress variables for this target.
include TestClient/CMakeFiles/TestClient.dir/progress.make

# Include the compile flags for this target's objects.
include TestClient/CMakeFiles/TestClient.dir/flags.make

TestClient/CMakeFiles/TestClient.dir/Main.o: TestClient/CMakeFiles/TestClient.dir/flags.make
TestClient/CMakeFiles/TestClient.dir/Main.o: ../TestClient/Main.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/shared/Ballet-Net-Github/Build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object TestClient/CMakeFiles/TestClient.dir/Main.o"
	cd /mnt/shared/Ballet-Net-Github/Build/TestClient && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/TestClient.dir/Main.o -c /mnt/shared/Ballet-Net-Github/TestClient/Main.cc

TestClient/CMakeFiles/TestClient.dir/Main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestClient.dir/Main.i"
	cd /mnt/shared/Ballet-Net-Github/Build/TestClient && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/shared/Ballet-Net-Github/TestClient/Main.cc > CMakeFiles/TestClient.dir/Main.i

TestClient/CMakeFiles/TestClient.dir/Main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestClient.dir/Main.s"
	cd /mnt/shared/Ballet-Net-Github/Build/TestClient && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/shared/Ballet-Net-Github/TestClient/Main.cc -o CMakeFiles/TestClient.dir/Main.s

TestClient/CMakeFiles/TestClient.dir/Main.o.requires:
.PHONY : TestClient/CMakeFiles/TestClient.dir/Main.o.requires

TestClient/CMakeFiles/TestClient.dir/Main.o.provides: TestClient/CMakeFiles/TestClient.dir/Main.o.requires
	$(MAKE) -f TestClient/CMakeFiles/TestClient.dir/build.make TestClient/CMakeFiles/TestClient.dir/Main.o.provides.build
.PHONY : TestClient/CMakeFiles/TestClient.dir/Main.o.provides

TestClient/CMakeFiles/TestClient.dir/Main.o.provides.build: TestClient/CMakeFiles/TestClient.dir/Main.o

# Object files for target TestClient
TestClient_OBJECTS = \
"CMakeFiles/TestClient.dir/Main.o"

# External object files for target TestClient
TestClient_EXTERNAL_OBJECTS =

TestClient/TestClient: TestClient/CMakeFiles/TestClient.dir/Main.o
TestClient/TestClient: Ballet/libBallet.so
TestClient/TestClient: IniLoader/libIniLoader.a
TestClient/TestClient: LoTrace/libLoTrace.a
TestClient/TestClient: TestClient/CMakeFiles/TestClient.dir/build.make
TestClient/TestClient: TestClient/CMakeFiles/TestClient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable TestClient"
	cd /mnt/shared/Ballet-Net-Github/Build/TestClient && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestClient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
TestClient/CMakeFiles/TestClient.dir/build: TestClient/TestClient
.PHONY : TestClient/CMakeFiles/TestClient.dir/build

TestClient/CMakeFiles/TestClient.dir/requires: TestClient/CMakeFiles/TestClient.dir/Main.o.requires
.PHONY : TestClient/CMakeFiles/TestClient.dir/requires

TestClient/CMakeFiles/TestClient.dir/clean:
	cd /mnt/shared/Ballet-Net-Github/Build/TestClient && $(CMAKE_COMMAND) -P CMakeFiles/TestClient.dir/cmake_clean.cmake
.PHONY : TestClient/CMakeFiles/TestClient.dir/clean

TestClient/CMakeFiles/TestClient.dir/depend:
	cd /mnt/shared/Ballet-Net-Github/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/shared/Ballet-Net-Github /mnt/shared/Ballet-Net-Github/TestClient /mnt/shared/Ballet-Net-Github/Build /mnt/shared/Ballet-Net-Github/Build/TestClient /mnt/shared/Ballet-Net-Github/Build/TestClient/CMakeFiles/TestClient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : TestClient/CMakeFiles/TestClient.dir/depend

