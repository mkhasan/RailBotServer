# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_SOURCE_DIR = /home/usrc/RailBotServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/usrc/RailBotServer/build

# Include any dependencies generated for this target.
include IR_Server/CMakeFiles/IR_Server.dir/depend.make

# Include the progress variables for this target.
include IR_Server/CMakeFiles/IR_Server.dir/progress.make

# Include the compile flags for this target's objects.
include IR_Server/CMakeFiles/IR_Server.dir/flags.make

IR_Server/CMakeFiles/IR_Server.dir/src/IR_Server.cpp.o: IR_Server/CMakeFiles/IR_Server.dir/flags.make
IR_Server/CMakeFiles/IR_Server.dir/src/IR_Server.cpp.o: ../IR_Server/src/IR_Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usrc/RailBotServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object IR_Server/CMakeFiles/IR_Server.dir/src/IR_Server.cpp.o"
	cd /home/usrc/RailBotServer/build/IR_Server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IR_Server.dir/src/IR_Server.cpp.o -c /home/usrc/RailBotServer/IR_Server/src/IR_Server.cpp

IR_Server/CMakeFiles/IR_Server.dir/src/IR_Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IR_Server.dir/src/IR_Server.cpp.i"
	cd /home/usrc/RailBotServer/build/IR_Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usrc/RailBotServer/IR_Server/src/IR_Server.cpp > CMakeFiles/IR_Server.dir/src/IR_Server.cpp.i

IR_Server/CMakeFiles/IR_Server.dir/src/IR_Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IR_Server.dir/src/IR_Server.cpp.s"
	cd /home/usrc/RailBotServer/build/IR_Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usrc/RailBotServer/IR_Server/src/IR_Server.cpp -o CMakeFiles/IR_Server.dir/src/IR_Server.cpp.s

IR_Server/CMakeFiles/IR_Server.dir/src/IR_Server.cpp.o.requires:

.PHONY : IR_Server/CMakeFiles/IR_Server.dir/src/IR_Server.cpp.o.requires

IR_Server/CMakeFiles/IR_Server.dir/src/IR_Server.cpp.o.provides: IR_Server/CMakeFiles/IR_Server.dir/src/IR_Server.cpp.o.requires
	$(MAKE) -f IR_Server/CMakeFiles/IR_Server.dir/build.make IR_Server/CMakeFiles/IR_Server.dir/src/IR_Server.cpp.o.provides.build
.PHONY : IR_Server/CMakeFiles/IR_Server.dir/src/IR_Server.cpp.o.provides

IR_Server/CMakeFiles/IR_Server.dir/src/IR_Server.cpp.o.provides.build: IR_Server/CMakeFiles/IR_Server.dir/src/IR_Server.cpp.o


IR_Server/CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.o: IR_Server/CMakeFiles/IR_Server.dir/flags.make
IR_Server/CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.o: ../IR_Server/src/JPEGSamples.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usrc/RailBotServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object IR_Server/CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.o"
	cd /home/usrc/RailBotServer/build/IR_Server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.o -c /home/usrc/RailBotServer/IR_Server/src/JPEGSamples.cpp

IR_Server/CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.i"
	cd /home/usrc/RailBotServer/build/IR_Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usrc/RailBotServer/IR_Server/src/JPEGSamples.cpp > CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.i

IR_Server/CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.s"
	cd /home/usrc/RailBotServer/build/IR_Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usrc/RailBotServer/IR_Server/src/JPEGSamples.cpp -o CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.s

IR_Server/CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.o.requires:

.PHONY : IR_Server/CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.o.requires

IR_Server/CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.o.provides: IR_Server/CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.o.requires
	$(MAKE) -f IR_Server/CMakeFiles/IR_Server.dir/build.make IR_Server/CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.o.provides.build
.PHONY : IR_Server/CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.o.provides

IR_Server/CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.o.provides.build: IR_Server/CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.o


IR_Server/CMakeFiles/IR_Server.dir/src/CStreamer.cpp.o: IR_Server/CMakeFiles/IR_Server.dir/flags.make
IR_Server/CMakeFiles/IR_Server.dir/src/CStreamer.cpp.o: ../IR_Server/src/CStreamer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usrc/RailBotServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object IR_Server/CMakeFiles/IR_Server.dir/src/CStreamer.cpp.o"
	cd /home/usrc/RailBotServer/build/IR_Server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IR_Server.dir/src/CStreamer.cpp.o -c /home/usrc/RailBotServer/IR_Server/src/CStreamer.cpp

IR_Server/CMakeFiles/IR_Server.dir/src/CStreamer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IR_Server.dir/src/CStreamer.cpp.i"
	cd /home/usrc/RailBotServer/build/IR_Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usrc/RailBotServer/IR_Server/src/CStreamer.cpp > CMakeFiles/IR_Server.dir/src/CStreamer.cpp.i

IR_Server/CMakeFiles/IR_Server.dir/src/CStreamer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IR_Server.dir/src/CStreamer.cpp.s"
	cd /home/usrc/RailBotServer/build/IR_Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usrc/RailBotServer/IR_Server/src/CStreamer.cpp -o CMakeFiles/IR_Server.dir/src/CStreamer.cpp.s

IR_Server/CMakeFiles/IR_Server.dir/src/CStreamer.cpp.o.requires:

.PHONY : IR_Server/CMakeFiles/IR_Server.dir/src/CStreamer.cpp.o.requires

IR_Server/CMakeFiles/IR_Server.dir/src/CStreamer.cpp.o.provides: IR_Server/CMakeFiles/IR_Server.dir/src/CStreamer.cpp.o.requires
	$(MAKE) -f IR_Server/CMakeFiles/IR_Server.dir/build.make IR_Server/CMakeFiles/IR_Server.dir/src/CStreamer.cpp.o.provides.build
.PHONY : IR_Server/CMakeFiles/IR_Server.dir/src/CStreamer.cpp.o.provides

IR_Server/CMakeFiles/IR_Server.dir/src/CStreamer.cpp.o.provides.build: IR_Server/CMakeFiles/IR_Server.dir/src/CStreamer.cpp.o


IR_Server/CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.o: IR_Server/CMakeFiles/IR_Server.dir/flags.make
IR_Server/CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.o: ../IR_Server/src/CRtspSession.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usrc/RailBotServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object IR_Server/CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.o"
	cd /home/usrc/RailBotServer/build/IR_Server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.o -c /home/usrc/RailBotServer/IR_Server/src/CRtspSession.cpp

IR_Server/CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.i"
	cd /home/usrc/RailBotServer/build/IR_Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usrc/RailBotServer/IR_Server/src/CRtspSession.cpp > CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.i

IR_Server/CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.s"
	cd /home/usrc/RailBotServer/build/IR_Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usrc/RailBotServer/IR_Server/src/CRtspSession.cpp -o CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.s

IR_Server/CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.o.requires:

.PHONY : IR_Server/CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.o.requires

IR_Server/CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.o.provides: IR_Server/CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.o.requires
	$(MAKE) -f IR_Server/CMakeFiles/IR_Server.dir/build.make IR_Server/CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.o.provides.build
.PHONY : IR_Server/CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.o.provides

IR_Server/CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.o.provides.build: IR_Server/CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.o


IR_Server/CMakeFiles/IR_Server.dir/src/ImageProcessor.cpp.o: IR_Server/CMakeFiles/IR_Server.dir/flags.make
IR_Server/CMakeFiles/IR_Server.dir/src/ImageProcessor.cpp.o: ../IR_Server/src/ImageProcessor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usrc/RailBotServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object IR_Server/CMakeFiles/IR_Server.dir/src/ImageProcessor.cpp.o"
	cd /home/usrc/RailBotServer/build/IR_Server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IR_Server.dir/src/ImageProcessor.cpp.o -c /home/usrc/RailBotServer/IR_Server/src/ImageProcessor.cpp

IR_Server/CMakeFiles/IR_Server.dir/src/ImageProcessor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IR_Server.dir/src/ImageProcessor.cpp.i"
	cd /home/usrc/RailBotServer/build/IR_Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usrc/RailBotServer/IR_Server/src/ImageProcessor.cpp > CMakeFiles/IR_Server.dir/src/ImageProcessor.cpp.i

IR_Server/CMakeFiles/IR_Server.dir/src/ImageProcessor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IR_Server.dir/src/ImageProcessor.cpp.s"
	cd /home/usrc/RailBotServer/build/IR_Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usrc/RailBotServer/IR_Server/src/ImageProcessor.cpp -o CMakeFiles/IR_Server.dir/src/ImageProcessor.cpp.s

IR_Server/CMakeFiles/IR_Server.dir/src/ImageProcessor.cpp.o.requires:

.PHONY : IR_Server/CMakeFiles/IR_Server.dir/src/ImageProcessor.cpp.o.requires

IR_Server/CMakeFiles/IR_Server.dir/src/ImageProcessor.cpp.o.provides: IR_Server/CMakeFiles/IR_Server.dir/src/ImageProcessor.cpp.o.requires
	$(MAKE) -f IR_Server/CMakeFiles/IR_Server.dir/build.make IR_Server/CMakeFiles/IR_Server.dir/src/ImageProcessor.cpp.o.provides.build
.PHONY : IR_Server/CMakeFiles/IR_Server.dir/src/ImageProcessor.cpp.o.provides

IR_Server/CMakeFiles/IR_Server.dir/src/ImageProcessor.cpp.o.provides.build: IR_Server/CMakeFiles/IR_Server.dir/src/ImageProcessor.cpp.o


IR_Server/CMakeFiles/IR_Server.dir/__/Common/src/time.cpp.o: IR_Server/CMakeFiles/IR_Server.dir/flags.make
IR_Server/CMakeFiles/IR_Server.dir/__/Common/src/time.cpp.o: ../Common/src/time.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usrc/RailBotServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object IR_Server/CMakeFiles/IR_Server.dir/__/Common/src/time.cpp.o"
	cd /home/usrc/RailBotServer/build/IR_Server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IR_Server.dir/__/Common/src/time.cpp.o -c /home/usrc/RailBotServer/Common/src/time.cpp

IR_Server/CMakeFiles/IR_Server.dir/__/Common/src/time.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IR_Server.dir/__/Common/src/time.cpp.i"
	cd /home/usrc/RailBotServer/build/IR_Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usrc/RailBotServer/Common/src/time.cpp > CMakeFiles/IR_Server.dir/__/Common/src/time.cpp.i

IR_Server/CMakeFiles/IR_Server.dir/__/Common/src/time.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IR_Server.dir/__/Common/src/time.cpp.s"
	cd /home/usrc/RailBotServer/build/IR_Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usrc/RailBotServer/Common/src/time.cpp -o CMakeFiles/IR_Server.dir/__/Common/src/time.cpp.s

IR_Server/CMakeFiles/IR_Server.dir/__/Common/src/time.cpp.o.requires:

.PHONY : IR_Server/CMakeFiles/IR_Server.dir/__/Common/src/time.cpp.o.requires

IR_Server/CMakeFiles/IR_Server.dir/__/Common/src/time.cpp.o.provides: IR_Server/CMakeFiles/IR_Server.dir/__/Common/src/time.cpp.o.requires
	$(MAKE) -f IR_Server/CMakeFiles/IR_Server.dir/build.make IR_Server/CMakeFiles/IR_Server.dir/__/Common/src/time.cpp.o.provides.build
.PHONY : IR_Server/CMakeFiles/IR_Server.dir/__/Common/src/time.cpp.o.provides

IR_Server/CMakeFiles/IR_Server.dir/__/Common/src/time.cpp.o.provides.build: IR_Server/CMakeFiles/IR_Server.dir/__/Common/src/time.cpp.o


# Object files for target IR_Server
IR_Server_OBJECTS = \
"CMakeFiles/IR_Server.dir/src/IR_Server.cpp.o" \
"CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.o" \
"CMakeFiles/IR_Server.dir/src/CStreamer.cpp.o" \
"CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.o" \
"CMakeFiles/IR_Server.dir/src/ImageProcessor.cpp.o" \
"CMakeFiles/IR_Server.dir/__/Common/src/time.cpp.o"

# External object files for target IR_Server
IR_Server_EXTERNAL_OBJECTS =

../bin/IR_Server: IR_Server/CMakeFiles/IR_Server.dir/src/IR_Server.cpp.o
../bin/IR_Server: IR_Server/CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.o
../bin/IR_Server: IR_Server/CMakeFiles/IR_Server.dir/src/CStreamer.cpp.o
../bin/IR_Server: IR_Server/CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.o
../bin/IR_Server: IR_Server/CMakeFiles/IR_Server.dir/src/ImageProcessor.cpp.o
../bin/IR_Server: IR_Server/CMakeFiles/IR_Server.dir/__/Common/src/time.cpp.o
../bin/IR_Server: IR_Server/CMakeFiles/IR_Server.dir/build.make
../bin/IR_Server: IR_Server/CMakeFiles/IR_Server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/usrc/RailBotServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable ../../bin/IR_Server"
	cd /home/usrc/RailBotServer/build/IR_Server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/IR_Server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
IR_Server/CMakeFiles/IR_Server.dir/build: ../bin/IR_Server

.PHONY : IR_Server/CMakeFiles/IR_Server.dir/build

IR_Server/CMakeFiles/IR_Server.dir/requires: IR_Server/CMakeFiles/IR_Server.dir/src/IR_Server.cpp.o.requires
IR_Server/CMakeFiles/IR_Server.dir/requires: IR_Server/CMakeFiles/IR_Server.dir/src/JPEGSamples.cpp.o.requires
IR_Server/CMakeFiles/IR_Server.dir/requires: IR_Server/CMakeFiles/IR_Server.dir/src/CStreamer.cpp.o.requires
IR_Server/CMakeFiles/IR_Server.dir/requires: IR_Server/CMakeFiles/IR_Server.dir/src/CRtspSession.cpp.o.requires
IR_Server/CMakeFiles/IR_Server.dir/requires: IR_Server/CMakeFiles/IR_Server.dir/src/ImageProcessor.cpp.o.requires
IR_Server/CMakeFiles/IR_Server.dir/requires: IR_Server/CMakeFiles/IR_Server.dir/__/Common/src/time.cpp.o.requires

.PHONY : IR_Server/CMakeFiles/IR_Server.dir/requires

IR_Server/CMakeFiles/IR_Server.dir/clean:
	cd /home/usrc/RailBotServer/build/IR_Server && $(CMAKE_COMMAND) -P CMakeFiles/IR_Server.dir/cmake_clean.cmake
.PHONY : IR_Server/CMakeFiles/IR_Server.dir/clean

IR_Server/CMakeFiles/IR_Server.dir/depend:
	cd /home/usrc/RailBotServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/usrc/RailBotServer /home/usrc/RailBotServer/IR_Server /home/usrc/RailBotServer/build /home/usrc/RailBotServer/build/IR_Server /home/usrc/RailBotServer/build/IR_Server/CMakeFiles/IR_Server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : IR_Server/CMakeFiles/IR_Server.dir/depend

