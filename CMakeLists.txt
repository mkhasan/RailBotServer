cmake_minimum_required(VERSION 2.8.9)
 
set (TARGET IR_Server)


set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -Wall -std=c++0x")



add_executable(${TARGET} src/${TARGET}.cpp src/JPEGSamples.cpp src/CStreamer.cpp src/CRtspSession.cpp)

target_link_libraries(${TARGET} pthread)

 
