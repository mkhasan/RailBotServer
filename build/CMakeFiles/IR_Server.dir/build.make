# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /opt/cmake-3.12.0-rc1-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.12.0-rc1-Linux-x86_64/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/usrc/external/RailRobot/RailBotServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/usrc/external/RailRobot/RailBotServer/build

# Include any dependencies generated for this target.
include CMakeFiles/IR_Server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/IR_Server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/IR_Server.dir/flags.make

CMakeFiles/IR_Server.dir/src/IR_Server.cpp.o: CMakeFiles/IR_Server.dir/flags.make
CMakeFiles/IR_Server.dir/src/IR_Server.cpp.o: ../src/IR_Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usrc/external/RailRobot/RailBotServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/IR_Server.dir/src/IR_Server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IR_Server.dir/src/IR_Server.cpp.o -c /home/usrc/external/RailRobot/RailBotServer/src/IR_Server.cpp

CMakeFiles/IR_Server.dir/src/IR_Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IR_Server.dir/src/IR_Server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usrc/external/RailRobot/RailBotServer/src/IR_Server.cpp > CMakeFiles/IR_Server.dir/src/IR_Server.cpp.i

CMakeFiles/IR_Server.dir/src/IR_Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IR_Server.dir/src/IR_Server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usrc/external/RailRobot/RailBotServer/src/IR_Server.cpp -o CMakeFiles/IR_Server.dir/src/IR_Server.cpp.s

CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.o: CMakeFiles/IR_Server.dir/flags.make
CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.o: ../src/JPEGSamples.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usrc/external/RailRobot/RailBotServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.o -c /home/usrc/external/RailRobot/RailBotServer/src/JPEGSamples.cpp

CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usrc/external/RailRobot/RailBotServer/src/JPEGSamples.cpp > CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.i

CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usrc/external/RailRobot/RailBotServer/src/JPEGSamples.cpp -o CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.s

CMakeFiles/IR_Server.dir/src/CStreamer.cpp.o: CMakeFiles/IR_Server.dir/flags.make
CMakeFiles/IR_Server.dir/src/CStreamer.cpp.o: ../src/CStreamer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usrc/external/RailRobot/RailBotServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/IR_Server.dir/src/CStreamer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IR_Server.dir/src/CStreamer.cpp.o -c /home/usrc/external/RailRobot/RailBotServer/src/CStreamer.cpp

CMakeFiles/IR_Server.dir/src/CStreamer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IR_Server.dir/src/CStreamer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usrc/external/RailRobot/RailBotServer/src/CStreamer.cpp > CMakeFiles/IR_Server.dir/src/CStreamer.cpp.i

CMakeFiles/IR_Server.dir/src/CStreamer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IR_Server.dir/src/CStreamer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usrc/external/RailRobot/RailBotServer/src/CStreamer.cpp -o CMakeFiles/IR_Server.dir/src/CStreamer.cpp.s

CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.o: CMakeFiles/IR_Server.dir/flags.make
CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.o: ../src/CRtspSession.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usrc/external/RailRobot/RailBotServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.o -c /home/usrc/external/RailRobot/RailBotServer/src/CRtspSession.cpp

CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usrc/external/RailRobot/RailBotServer/src/CRtspSession.cpp > CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.i

CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usrc/external/RailRobot/RailBotServer/src/CRtspSession.cpp -o CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.s

# Object files for target IR_Server
IR_Server_OBJECTS = \
"CMakeFiles/IR_Server.dir/src/IR_Server.cpp.o" \
"CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.o" \
"CMakeFiles/IR_Server.dir/src/CStreamer.cpp.o" \
"CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.o"

# External object files for target IR_Server
IR_Server_EXTERNAL_OBJECTS =

../bin/IR_Server: CMakeFiles/IR_Server.dir/src/IR_Server.cpp.o
../bin/IR_Server: CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.o
../bin/IR_Server: CMakeFiles/IR_Server.dir/src/CStreamer.cpp.o
../bin/IR_Server: CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.o
../bin/IR_Server: CMakeFiles/IR_Server.dir/build.make
../bin/IR_Server: CMakeFiles/IR_Server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/usrc/external/RailRobot/RailBotServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable ../bin/IR_Server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/IR_Server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/IR_Server.dir/build: ../bin/IR_Server

.PHONY : CMakeFiles/IR_Server.dir/build

CMakeFiles/IR_Server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/IR_Server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/IR_Server.dir/clean

CMakeFiles/IR_Server.dir/depend:
	cd /home/usrc/external/RailRobot/RailBotServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/usrc/external/RailRobot/RailBotServer /home/usrc/external/RailRobot/RailBotServer /home/usrc/external/RailRobot/RailBotServer/build /home/usrc/external/RailRobot/RailBotServer/build /home/usrc/external/RailRobot/RailBotServer/build/CMakeFiles/IR_Server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/IR_Server.dir/depend
