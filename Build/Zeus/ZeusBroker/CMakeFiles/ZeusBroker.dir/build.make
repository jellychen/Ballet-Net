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
include Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/depend.make

# Include the progress variables for this target.
include Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/progress.make

# Include the compile flags for this target's objects.
include Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/flags.make

Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsBrokerService.o: Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/flags.make
Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsBrokerService.o: ../Zeus/ZeusBroker/ZsBrokerService.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/shared/Ballet-Net-Github/Build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsBrokerService.o"
	cd /mnt/shared/Ballet-Net-Github/Build/Zeus/ZeusBroker && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ZeusBroker.dir/ZsBrokerService.o -c /mnt/shared/Ballet-Net-Github/Zeus/ZeusBroker/ZsBrokerService.cc

Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsBrokerService.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ZeusBroker.dir/ZsBrokerService.i"
	cd /mnt/shared/Ballet-Net-Github/Build/Zeus/ZeusBroker && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/shared/Ballet-Net-Github/Zeus/ZeusBroker/ZsBrokerService.cc > CMakeFiles/ZeusBroker.dir/ZsBrokerService.i

Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsBrokerService.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ZeusBroker.dir/ZsBrokerService.s"
	cd /mnt/shared/Ballet-Net-Github/Build/Zeus/ZeusBroker && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/shared/Ballet-Net-Github/Zeus/ZeusBroker/ZsBrokerService.cc -o CMakeFiles/ZeusBroker.dir/ZsBrokerService.s

Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsBrokerService.o.requires:
.PHONY : Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsBrokerService.o.requires

Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsBrokerService.o.provides: Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsBrokerService.o.requires
	$(MAKE) -f Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/build.make Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsBrokerService.o.provides.build
.PHONY : Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsBrokerService.o.provides

Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsBrokerService.o.provides.build: Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsBrokerService.o

Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsMain.o: Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/flags.make
Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsMain.o: ../Zeus/ZeusBroker/ZsMain.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/shared/Ballet-Net-Github/Build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsMain.o"
	cd /mnt/shared/Ballet-Net-Github/Build/Zeus/ZeusBroker && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ZeusBroker.dir/ZsMain.o -c /mnt/shared/Ballet-Net-Github/Zeus/ZeusBroker/ZsMain.cc

Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsMain.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ZeusBroker.dir/ZsMain.i"
	cd /mnt/shared/Ballet-Net-Github/Build/Zeus/ZeusBroker && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/shared/Ballet-Net-Github/Zeus/ZeusBroker/ZsMain.cc > CMakeFiles/ZeusBroker.dir/ZsMain.i

Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsMain.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ZeusBroker.dir/ZsMain.s"
	cd /mnt/shared/Ballet-Net-Github/Build/Zeus/ZeusBroker && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/shared/Ballet-Net-Github/Zeus/ZeusBroker/ZsMain.cc -o CMakeFiles/ZeusBroker.dir/ZsMain.s

Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsMain.o.requires:
.PHONY : Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsMain.o.requires

Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsMain.o.provides: Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsMain.o.requires
	$(MAKE) -f Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/build.make Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsMain.o.provides.build
.PHONY : Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsMain.o.provides

Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsMain.o.provides.build: Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsMain.o

Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsUdpServer.o: Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/flags.make
Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsUdpServer.o: ../Zeus/ZeusBroker/ZsUdpServer.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/shared/Ballet-Net-Github/Build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsUdpServer.o"
	cd /mnt/shared/Ballet-Net-Github/Build/Zeus/ZeusBroker && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ZeusBroker.dir/ZsUdpServer.o -c /mnt/shared/Ballet-Net-Github/Zeus/ZeusBroker/ZsUdpServer.cc

Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsUdpServer.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ZeusBroker.dir/ZsUdpServer.i"
	cd /mnt/shared/Ballet-Net-Github/Build/Zeus/ZeusBroker && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/shared/Ballet-Net-Github/Zeus/ZeusBroker/ZsUdpServer.cc > CMakeFiles/ZeusBroker.dir/ZsUdpServer.i

Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsUdpServer.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ZeusBroker.dir/ZsUdpServer.s"
	cd /mnt/shared/Ballet-Net-Github/Build/Zeus/ZeusBroker && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/shared/Ballet-Net-Github/Zeus/ZeusBroker/ZsUdpServer.cc -o CMakeFiles/ZeusBroker.dir/ZsUdpServer.s

Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsUdpServer.o.requires:
.PHONY : Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsUdpServer.o.requires

Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsUdpServer.o.provides: Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsUdpServer.o.requires
	$(MAKE) -f Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/build.make Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsUdpServer.o.provides.build
.PHONY : Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsUdpServer.o.provides

Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsUdpServer.o.provides.build: Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsUdpServer.o

# Object files for target ZeusBroker
ZeusBroker_OBJECTS = \
"CMakeFiles/ZeusBroker.dir/ZsBrokerService.o" \
"CMakeFiles/ZeusBroker.dir/ZsMain.o" \
"CMakeFiles/ZeusBroker.dir/ZsUdpServer.o"

# External object files for target ZeusBroker
ZeusBroker_EXTERNAL_OBJECTS =

Zeus/ZeusBroker/ZeusBroker: Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsBrokerService.o
Zeus/ZeusBroker/ZeusBroker: Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsMain.o
Zeus/ZeusBroker/ZeusBroker: Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsUdpServer.o
Zeus/ZeusBroker/ZeusBroker: Ballet/libBallet.so
Zeus/ZeusBroker/ZeusBroker: IniLoader/libIniLoader.a
Zeus/ZeusBroker/ZeusBroker: Zeus/ZeusBase/libZeusBase.a
Zeus/ZeusBroker/ZeusBroker: Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/build.make
Zeus/ZeusBroker/ZeusBroker: Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ZeusBroker"
	cd /mnt/shared/Ballet-Net-Github/Build/Zeus/ZeusBroker && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ZeusBroker.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/build: Zeus/ZeusBroker/ZeusBroker
.PHONY : Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/build

Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/requires: Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsBrokerService.o.requires
Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/requires: Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsMain.o.requires
Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/requires: Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/ZsUdpServer.o.requires
.PHONY : Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/requires

Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/clean:
	cd /mnt/shared/Ballet-Net-Github/Build/Zeus/ZeusBroker && $(CMAKE_COMMAND) -P CMakeFiles/ZeusBroker.dir/cmake_clean.cmake
.PHONY : Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/clean

Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/depend:
	cd /mnt/shared/Ballet-Net-Github/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/shared/Ballet-Net-Github /mnt/shared/Ballet-Net-Github/Zeus/ZeusBroker /mnt/shared/Ballet-Net-Github/Build /mnt/shared/Ballet-Net-Github/Build/Zeus/ZeusBroker /mnt/shared/Ballet-Net-Github/Build/Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Zeus/ZeusBroker/CMakeFiles/ZeusBroker.dir/depend

