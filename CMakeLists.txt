cmake_minimum_required(VERSION 2.8)

option(test "Build all tests." OFF)

set(PROJECT_NAME gpsdistance)
project(${PROJECT_NAME})

#--------------------
# directories 
#--------------------
set(SRC_DIR ./src)
set(INCLUDE_DIR ./include)

#--------------------
# compiler options
#--------------------
set(CMAKE_CXX_FLAGS "-g -Wall")

#--------------------
# include paths
#--------------------
include_directories(
		${INCLUDE_DIR}
	)

#--------------------
# source files
#--------------------
file(GLOB SRCS ${SRC_DIR})

#--------------------
# liker paths
#--------------------
link_directories(
	)

#--------------------
# 
#--------------------
add_library(lib${PROJECT_NAME} ${SRC_DIR}/distance.cpp)
add_executable(${PROJECT_NAME} ${SRC_DIR}/main.cpp)
target_link_libraries(${PROJECT_NAME} lib${PROJECT_NAME})

