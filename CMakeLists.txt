cmake_minimum_required (VERSION 3.5.1)

set (PROJECT"GeometricNeuralNetwork")

project (${PROJECT} CXX)

# Verion of the program
set (CURRENT_MAJOR_VERSION 0)
set (CURRENT_MINOR_VERSION 9)

# Doxygen documentation setup
option(BUILD_DOC "Build documentation" ON)
find_package(Doxygen)
if(DOXYGEN_FOUND)
	message("Doxygen found!")

	add_custom_target(doc
	doxygen ${CMAKE_SOURCE_DIR}/docs/Doxyfile)

else (DOXYGEN_FOUND)
	message("Doxygen need to be installed to generate the doxygen documentation")
endif(DOXYGEN_FOUND)

# Medium dataset download
find_program(WGET wget)
if(NOT WGET)
	message(WARNING "missing wget, check the site https://pjreddie.com/projects/mnist-in-csv to download datasets!")
else()
	add_custom_target(get_csv 
	wget https://pjreddie.com/media/files/mnist_train.csv ../data/mnist_train.csv && 
	wget https://pjreddie.com/media/files/mnist_test.csv ../data/mnist_test.csv)
endif()

# EXTERNAL LIBRARIES
include (CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)

if(COMPILER_SUPPORTS_CXX14)
	add_compile_options("-std=c++14")
else()
	message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER} has no C++14 support.")
endif()

find_package(Boost COMPONENTS program_options REQUIRED)

# Warning flag
add_compile_options("-Wall")
add_compile_options("-Wextra")
add_compile_options("-Wpedantic")

# LIBRARIES AND DIRECTORIES OF PROJECT
include_directories ("${PROJECT_BINARY_DIR}")

configure_file (
	"${PROJECT_SOURCE_DIR}/Config.h.in"
	"${PROJECT_BINARY_DIR}/Config.h"
	)

include_directories (include ${Boost_INCLUDE_DIRS})

add_library(NN "src/NN.cpp")

enable_testing()
add_subdirectory(test)

add_executable(vectorNeuralNetwork src/MainActivity.cpp)
target_link_libraries(vectorNeuralNetwork NN)
target_link_libraries(vectorNeuralNetwork ${Boost_LIBRARIES})

install(TARGETS vectorNeuralNetwork
		RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin
		LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/lib)