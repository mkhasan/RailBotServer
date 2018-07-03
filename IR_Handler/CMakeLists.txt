cmake_minimum_required(VERSION 2.8.9)
 
set (TARGET IR_Handler)


set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


execute_process(COMMAND pkg-config --cflags sdl OUTPUT_VARIABLE SDL_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
#execute_process(COMMAND find $ENV{IR_VIEWER_C} -name "*.cpp" OUTPUT_VARIABLE IR_CPP OUTPUT_STRIP_TRAILING_WHITESPACE)

message("all cpp ${IR_CPP}")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SDL_CFLAGS} -ggdb -Wall -std=c++0x -Wno-narrowing")


include_directories($ENV{IR_VIEWER_C})

set (IR_HANDLER_SRC ${IR_CPP} 
	src/${TARGET}.cpp  
	$ENV{IR_VIEWER_C}/CircularBuffer.cpp
	$ENV{IR_VIEWER_C}/Decoder.cpp
	$ENV{IR_VIEWER_C}/ir_viewer.cpp
	$ENV{IR_VIEWER_C}/Socket.cpp
	
	)

add_executable(${TARGET} ${IR_HANDLER_SRC})

target_link_libraries(${TARGET} SDL pthread)

 
