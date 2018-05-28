cmake_minimum_required (VERSION 3.5.1)

set (PROJECT"NeuralNetwork")

project (${PROJECT} CXX)

set (CURRENT_VERSION 1.0)


# EXTERNAL LIBRARIES
include (CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)

if(COMPILER_SUPPORTS_CXX14)
	add_compile_options("-std=c++14")
else()
	message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER} has no C++14 support.")
endif()

add_compile_options("-Wall")
add_compile_options("-Wextra")
add_compile_options("-Wpedantic")
# LIBRARIES AND DIRECTORIES OF PROJECT
include_directories ("${PROJECT_BINARY_DIR}")

configure_file (
	"${PROJECT_SOURCE_DIR}/Config.h.in"
	"${PROJECT_BINARY_DIR}/Config.h"
	)

include_directories (include)


# FILE(GLOB_RECURSE SRCS ${PROJECT_SOURCE_DIR}/src/*.cpp)

#IF(CMAKE_BUILD_TYPE STREQUAL "Debug").....

add_library(NN "src/NN.cpp")

enable_testing()
add_subdirectory(test)