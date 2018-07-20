cmake_minimum_required(VERSION 2.8.9)
 


set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -Wall")

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


add_executable(Server src/Server.cpp)


add_executable(Client src/Client.cpp)



 
