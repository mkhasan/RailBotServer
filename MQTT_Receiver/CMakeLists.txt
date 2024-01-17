cmake_minimum_required(VERSION 2.8.9)
 
set(TARGET mqtt_receiver)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_definitions(-DV_LEVEL=${VERBOSE_LEVEL})

execute_process(COMMAND pkg-config --cflags sdl OUTPUT_VARIABLE SDL_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
#execute_process(COMMAND find $ENV{IR_VIEWER_C} -name "*.cpp" OUTPUT_VARIABLE IR_CPP OUTPUT_STRIP_TRAILING_WHITESPACE)

message("${PROJECT_SOURCE_DIR}")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SDL_CFLAGS} -ggdb -Wall -std=c++0x -Wno-narrowing -std=c++14")



include_directories(${PROJECT_SOURCE_DIR}/Common/include)

include_directories($ENV{ACE_ROOT})

link_directories($ENV{ACE_ROOT}/lib)

add_executable(${TARGET} src/main.cpp src/mqtt_receiver.cpp )

target_link_libraries(${TARGET} ACE pthread mosquitto mosquittopp)

 
