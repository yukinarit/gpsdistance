cmake_minimum_required(VERSION 2.8)

option(test "Build all tests." OFF)

set(PROJECT_NAME gpsdistance)
project(${PROJECT_NAME})

#--------------------
# directories 
#--------------------
set(PROJECT_DIR ${CMAKE_SOURCE_DIR})
set(SRC_DIR ${PROJECT_DIR}/src)
set(INCLUDE_DIR ${PROJECT_DIR}/include)

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
add_library(lib${PROJECT_NAME} ${SRC_DIR}/gpsdistance.cpp)
#add_executable(${PROJECT_NAME} ${SRC_DIR}/main.cpp)
#target_link_libraries(${PROJECT_NAME} lib${PROJECT_NAME})

#--------------------
# Testing  
#--------------------
if (test)
	add_subdirectory(lib/googletest)

	enable_testing()

	include_directories()

	add_executable(runUnitTests test/main.cpp)
	target_link_libraries(runUnitTests  gtest gtest_main)
	target_link_libraries(runUnitTests  lib${PROJECT_NAME})

	add_test(NAME that-test-I-made COMMAND runUnitTests)
	add_test(that-other-test-I-made runUnitTests)
endif()

