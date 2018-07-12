
cmake_minimum_required(VERSION 2.8)

set (TARGET RbUtils)
set (TARGET_TEST UtilsTest)


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

set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wextra")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -O3 -fomit-frame-pointer -fexpensive-optimizations")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra")


# -fno-strict-aliasing is *required* to compile LZHAM
set(GCC_COMPILE_FLAGS "-fno-strict-aliasing -D_LARGEFILE64_SOURCE=1 -D_FILE_OFFSET_BITS=64")

if (NOT BUILD_X64)
	set(GCC_COMPILE_FLAGS "${GCC_COMPILE_FLAGS} -m32")
endif()

set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COMPILE_FLAGS}")
set(CMAKE_C_FLAGS_RELEASE  "${CMAKE_C_FLAGS_RELEASE} ${GCC_COMPILE_FLAGS} -DNDEBUG")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${GCC_COMPILE_FLAGS} -D_DEBUG")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} ${GCC_COMPILE_FLAGS} -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${GCC_COMPILE_FLAGS} -D_DEBUG")

include_directories(
	$ENV{LZHAM_DIR}/lzhamdecomp
    $ENV{LZHAM_DIR}/lzhamcomp
	$ENV{LZHAM_DIR}/include)
	
	
add_library(${TARGET} src/utils.cpp)

link_directories($ENV{LZHAM_DIR}/build/lzhamdll)

add_executable(${TARGET_TEST} src/utils_test.cpp)

target_link_libraries(${TARGET_TEST} ${TARGET} lzhamdll)
