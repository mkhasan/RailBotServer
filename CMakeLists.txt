cmake_minimum_required(VERSION 2.8.9)
 


PROJECT (RAIL_ROBOT_SERVER)


add_definitions(-DDEBUG=0)
add_definitions(-DINFO=1)
add_definitions(-DWARN=2)
add_definitions(-DERROR=3)
add_definitions(-DFATAL=2)


set(VERBOSE_LEVEL DEBUG)

set (COMMON_SRC "${PROJECT_SOURCE_DIR}/Common/src/time.cpp")

add_subdirectory(Utils)
add_subdirectory(testUtils)
add_subdirectory(IR_Server)
add_subdirectory(IR_Handler)
add_subdirectory(CompressionTest)
 
