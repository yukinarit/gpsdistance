cmake_minimum_required(VERSION 2.8)

option(test "Build all tests." ON)

set(PROJECT_NAME gpsdistance)
project(${PROJECT_NAME})

#--------------------
# directories 
#--------------------
set(PROJECT_DIR ${CMAKE_SOURCE_DIR})
set(SRC_DIR ${PROJECT_DIR}/src)
set(INCLUDE_DIR ${PROJECT_DIR}/include)
set(GTEST_INCLUDE_DIR ${PROJECT_DIR}/lib/googletest/include)

#--------------------
# compiler options
#--------------------
set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

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
# executable/library  
#--------------------
add_library(${PROJECT_NAME} ${SRC_DIR}/gpsdistance.cpp)

#--------------------
# Testing  
#--------------------
if (test)
	add_subdirectory(lib/googletest)

	enable_testing()

	include_directories(
			${INCLUDE_DIR},
			${GTEST_INCLUDE_DIR}
		)

	add_executable(runUnitTests test/main.cpp)
	target_link_libraries(runUnitTests  gtest gtest_main)
	target_link_libraries(runUnitTests  ${PROJECT_NAME})

	add_test(gpsdistance_test runUnitTests)
endif()

