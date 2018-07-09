cmake_minimum_required(VERSION 2.8.9)
 
set (TARGET IR_Server)


set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -Wall -std=c++0x -Wno-narrowing -w")


option(BUILD_X64 "build 64-bit" TRUE)

message("Initial BUILD_X64=${BUILD_X64}")
message("Initial CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Debug )
endif( NOT CMAKE_BUILD_TYPE )

message( ${TARGET} " build type: " ${CMAKE_BUILD_TYPE} )

if (BUILD_X64)
	message("Building 64-bit")
else()
	message("Building 32-bit")
endif(BUILD_X64)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wextra")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -O3 -fomit-frame-pointer -fexpensive-optimizations")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra")


include_directories(${PROJECT_SOURCE_DIR}/Common/include)
include_directories($ENV{ACE_ROOT})

include_directories(
	$ENV{LZHAM_DIR}/lzhamdecomp
    $ENV{LZHAM_DIR}/lzhamcomp
	$ENV{LZHAM_DIR}/include)


link_directories($ENV{ACE_ROOT}/lib)
link_directories($ENV{LZHAM_DIR}/build/lzhamdll)

add_executable(${TARGET} src/${TARGET}.cpp src/JPEGSamples.cpp src/CStreamer.cpp src/CRtspSession.cpp src/ImageProcessor.cpp ${COMMON_SRC})

target_link_libraries(${TARGET} lzhamdll ACE pthread)

 
