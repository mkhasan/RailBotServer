cmake_minimum_required(VERSION 2.8.9)
 
set (TARGET IR_Handler)


set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


execute_process(COMMAND pkg-config --cflags sdl OUTPUT_VARIABLE SDL_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
#execute_process(COMMAND find $ENV{IR_VIEWER_C} -name "*.cpp" OUTPUT_VARIABLE IR_CPP OUTPUT_STRIP_TRAILING_WHITESPACE)

message("all cpp ${IR_CPP}")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SDL_CFLAGS} -ggdb -Wall -std=c++0x -Wno-narrowing -w")


set (IR_HANDLER_SRC ${IR_CPP} 
	src/${TARGET}.cpp  
	src/CircularBuffer.cpp
	src/Decoder.cpp
	src/ir_viewer.cpp
	src/Socket.cpp
	
	)


include_directories(${PROJECT_SOURCE_DIR}/Common/include)

include_directories($ENV{ACE_ROOT})

link_directories($ENV{ACE_ROOT}/lib)

add_executable(${TARGET} ${IR_HANDLER_SRC} ${COMMON_SRC})

target_link_libraries(${TARGET} SDL ACE pthread)

 
