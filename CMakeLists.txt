cmake_minimum_required(VERSION 2.8.9)
 


PROJECT (SKI_ROBOT)

set (COMMON_SRC "${PROJECT_SOURCE_DIR}/Common/src/time.cpp")

add_subdirectory(./IR_Server)
add_subdirectory(./IR_Handler)
 
