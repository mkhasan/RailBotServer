# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build

# Include any dependencies generated for this target.
include IR_Handler/CMakeFiles/IR_Handler.dir/depend.make

# Include the progress variables for this target.
include IR_Handler/CMakeFiles/IR_Handler.dir/progress.make

# Include the compile flags for this target's objects.
include IR_Handler/CMakeFiles/IR_Handler.dir/flags.make

IR_Handler/CMakeFiles/IR_Handler.dir/src/IR_Handler.cpp.o: IR_Handler/CMakeFiles/IR_Handler.dir/flags.make
IR_Handler/CMakeFiles/IR_Handler.dir/src/IR_Handler.cpp.o: ../IR_Handler/src/IR_Handler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object IR_Handler/CMakeFiles/IR_Handler.dir/src/IR_Handler.cpp.o"
	cd /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/IR_Handler && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IR_Handler.dir/src/IR_Handler.cpp.o -c /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/IR_Handler/src/IR_Handler.cpp

IR_Handler/CMakeFiles/IR_Handler.dir/src/IR_Handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IR_Handler.dir/src/IR_Handler.cpp.i"
	cd /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/IR_Handler && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/IR_Handler/src/IR_Handler.cpp > CMakeFiles/IR_Handler.dir/src/IR_Handler.cpp.i

IR_Handler/CMakeFiles/IR_Handler.dir/src/IR_Handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IR_Handler.dir/src/IR_Handler.cpp.s"
	cd /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/IR_Handler && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/IR_Handler/src/IR_Handler.cpp -o CMakeFiles/IR_Handler.dir/src/IR_Handler.cpp.s

IR_Handler/CMakeFiles/IR_Handler.dir/src/CircularBuffer.cpp.o: IR_Handler/CMakeFiles/IR_Handler.dir/flags.make
IR_Handler/CMakeFiles/IR_Handler.dir/src/CircularBuffer.cpp.o: ../IR_Handler/src/CircularBuffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object IR_Handler/CMakeFiles/IR_Handler.dir/src/CircularBuffer.cpp.o"
	cd /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/IR_Handler && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IR_Handler.dir/src/CircularBuffer.cpp.o -c /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/IR_Handler/src/CircularBuffer.cpp

IR_Handler/CMakeFiles/IR_Handler.dir/src/CircularBuffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IR_Handler.dir/src/CircularBuffer.cpp.i"
	cd /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/IR_Handler && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/IR_Handler/src/CircularBuffer.cpp > CMakeFiles/IR_Handler.dir/src/CircularBuffer.cpp.i

IR_Handler/CMakeFiles/IR_Handler.dir/src/CircularBuffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IR_Handler.dir/src/CircularBuffer.cpp.s"
	cd /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/IR_Handler && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/IR_Handler/src/CircularBuffer.cpp -o CMakeFiles/IR_Handler.dir/src/CircularBuffer.cpp.s

IR_Handler/CMakeFiles/IR_Handler.dir/src/Decoder.cpp.o: IR_Handler/CMakeFiles/IR_Handler.dir/flags.make
IR_Handler/CMakeFiles/IR_Handler.dir/src/Decoder.cpp.o: ../IR_Handler/src/Decoder.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object IR_Handler/CMakeFiles/IR_Handler.dir/src/Decoder.cpp.o"
	cd /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/IR_Handler && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IR_Handler.dir/src/Decoder.cpp.o -c /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/IR_Handler/src/Decoder.cpp

IR_Handler/CMakeFiles/IR_Handler.dir/src/Decoder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IR_Handler.dir/src/Decoder.cpp.i"
	cd /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/IR_Handler && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/IR_Handler/src/Decoder.cpp > CMakeFiles/IR_Handler.dir/src/Decoder.cpp.i

IR_Handler/CMakeFiles/IR_Handler.dir/src/Decoder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IR_Handler.dir/src/Decoder.cpp.s"
	cd /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/IR_Handler && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/IR_Handler/src/Decoder.cpp -o CMakeFiles/IR_Handler.dir/src/Decoder.cpp.s

IR_Handler/CMakeFiles/IR_Handler.dir/src/ir_viewer.cpp.o: IR_Handler/CMakeFiles/IR_Handler.dir/flags.make
IR_Handler/CMakeFiles/IR_Handler.dir/src/ir_viewer.cpp.o: ../IR_Handler/src/ir_viewer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object IR_Handler/CMakeFiles/IR_Handler.dir/src/ir_viewer.cpp.o"
	cd /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/IR_Handler && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IR_Handler.dir/src/ir_viewer.cpp.o -c /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/IR_Handler/src/ir_viewer.cpp

IR_Handler/CMakeFiles/IR_Handler.dir/src/ir_viewer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IR_Handler.dir/src/ir_viewer.cpp.i"
	cd /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/IR_Handler && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/IR_Handler/src/ir_viewer.cpp > CMakeFiles/IR_Handler.dir/src/ir_viewer.cpp.i

IR_Handler/CMakeFiles/IR_Handler.dir/src/ir_viewer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IR_Handler.dir/src/ir_viewer.cpp.s"
	cd /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/IR_Handler && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/IR_Handler/src/ir_viewer.cpp -o CMakeFiles/IR_Handler.dir/src/ir_viewer.cpp.s

IR_Handler/CMakeFiles/IR_Handler.dir/src/Socket.cpp.o: IR_Handler/CMakeFiles/IR_Handler.dir/flags.make
IR_Handler/CMakeFiles/IR_Handler.dir/src/Socket.cpp.o: ../IR_Handler/src/Socket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object IR_Handler/CMakeFiles/IR_Handler.dir/src/Socket.cpp.o"
	cd /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/IR_Handler && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IR_Handler.dir/src/Socket.cpp.o -c /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/IR_Handler/src/Socket.cpp

IR_Handler/CMakeFiles/IR_Handler.dir/src/Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IR_Handler.dir/src/Socket.cpp.i"
	cd /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/IR_Handler && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/IR_Handler/src/Socket.cpp > CMakeFiles/IR_Handler.dir/src/Socket.cpp.i

IR_Handler/CMakeFiles/IR_Handler.dir/src/Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IR_Handler.dir/src/Socket.cpp.s"
	cd /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/IR_Handler && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/IR_Handler/src/Socket.cpp -o CMakeFiles/IR_Handler.dir/src/Socket.cpp.s

IR_Handler/CMakeFiles/IR_Handler.dir/__/Common/src/time.cpp.o: IR_Handler/CMakeFiles/IR_Handler.dir/flags.make
IR_Handler/CMakeFiles/IR_Handler.dir/__/Common/src/time.cpp.o: ../Common/src/time.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object IR_Handler/CMakeFiles/IR_Handler.dir/__/Common/src/time.cpp.o"
	cd /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/IR_Handler && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IR_Handler.dir/__/Common/src/time.cpp.o -c /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/Common/src/time.cpp

IR_Handler/CMakeFiles/IR_Handler.dir/__/Common/src/time.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IR_Handler.dir/__/Common/src/time.cpp.i"
	cd /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/IR_Handler && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/Common/src/time.cpp > CMakeFiles/IR_Handler.dir/__/Common/src/time.cpp.i

IR_Handler/CMakeFiles/IR_Handler.dir/__/Common/src/time.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IR_Handler.dir/__/Common/src/time.cpp.s"
	cd /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/IR_Handler && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/Common/src/time.cpp -o CMakeFiles/IR_Handler.dir/__/Common/src/time.cpp.s

# Object files for target IR_Handler
IR_Handler_OBJECTS = \
"CMakeFiles/IR_Handler.dir/src/IR_Handler.cpp.o" \
"CMakeFiles/IR_Handler.dir/src/CircularBuffer.cpp.o" \
"CMakeFiles/IR_Handler.dir/src/Decoder.cpp.o" \
"CMakeFiles/IR_Handler.dir/src/ir_viewer.cpp.o" \
"CMakeFiles/IR_Handler.dir/src/Socket.cpp.o" \
"CMakeFiles/IR_Handler.dir/__/Common/src/time.cpp.o"

# External object files for target IR_Handler
IR_Handler_EXTERNAL_OBJECTS =

../bin/IR_Handler: IR_Handler/CMakeFiles/IR_Handler.dir/src/IR_Handler.cpp.o
../bin/IR_Handler: IR_Handler/CMakeFiles/IR_Handler.dir/src/CircularBuffer.cpp.o
../bin/IR_Handler: IR_Handler/CMakeFiles/IR_Handler.dir/src/Decoder.cpp.o
../bin/IR_Handler: IR_Handler/CMakeFiles/IR_Handler.dir/src/ir_viewer.cpp.o
../bin/IR_Handler: IR_Handler/CMakeFiles/IR_Handler.dir/src/Socket.cpp.o
../bin/IR_Handler: IR_Handler/CMakeFiles/IR_Handler.dir/__/Common/src/time.cpp.o
../bin/IR_Handler: IR_Handler/CMakeFiles/IR_Handler.dir/build.make
../bin/IR_Handler: IR_Handler/CMakeFiles/IR_Handler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable ../../bin/IR_Handler"
	cd /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/IR_Handler && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/IR_Handler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
IR_Handler/CMakeFiles/IR_Handler.dir/build: ../bin/IR_Handler

.PHONY : IR_Handler/CMakeFiles/IR_Handler.dir/build

IR_Handler/CMakeFiles/IR_Handler.dir/clean:
	cd /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/IR_Handler && $(CMAKE_COMMAND) -P CMakeFiles/IR_Handler.dir/cmake_clean.cmake
.PHONY : IR_Handler/CMakeFiles/IR_Handler.dir/clean

IR_Handler/CMakeFiles/IR_Handler.dir/depend:
	cd /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/IR_Handler /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/IR_Handler /home/mecasys/MyProjects/RailBot_4_dot_O/RailBotServer/build/IR_Handler/CMakeFiles/IR_Handler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : IR_Handler/CMakeFiles/IR_Handler.dir/depend

