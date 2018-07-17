cmake_minimum_required(VERSION 2.8.9)
 
set (TARGET IR_Server)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -Wall -std=c++0x -Wno-narrowing -w")


set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wextra")


add_definitions(-DV_LEVEL=${VERBOSE_LEVEL})

include_directories(${PROJECT_SOURCE_DIR}/Common/include ${PROJECT_SOURCE_DIR}/Utils/src)
include_directories($ENV{ACE_ROOT})

include_directories(
	$ENV{LZHAM_DIR}/include)


link_directories($ENV{ACE_ROOT}/lib)
link_directories($ENV{LZHAM_DIR}/build/lzhamdll)

add_executable(${TARGET} src/${TARGET}.cpp src/JPEGSamples.cpp src/CStreamer.cpp src/CRtspSession.cpp src/ImageProcessor.cpp ${COMMON_SRC})

target_link_libraries(${TARGET} RbUtils lzhamdll ACE pthread)

 
