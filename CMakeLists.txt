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
	wget https://pjreddie.com/media/files/mnist_train.csv --output-document=../data/mnist_train.csv
	wget https://pjreddie.com/media/files/mnist_test.csv --output-document=../data/mnist_test.csv)
endif()

# Valgrind check
find_program(VALGRIND valgrind)
if(NOT VALGRIND)
	message(WARNING "missing valgrind, this feature will not be active!")
else()
	add_custom_target(valgrind
	valgrind ./vectorNeuralNetwork -t ../data/mnist_train.csv -p ../data/mnist_test.csv)
endif()

# Statistics
find_program(CLOC cloc)
if(NOT CLOC)
	message(WARNING "missing cloc, this feature will not be active!")
else()
	add_custom_target(stats
	cloc ${CMAKE_SOURCE_DIR} --exclude-dir=build)
endif()

# Complexity
find_program(LIZARD lizard)
if(NOT LIZARD)
	message(WARNING "missing lizard, this feature will not be active!")
else()
	add_custom_target(cyclo
	lizard --exclude \"*build*\" ../)
endif()

	
# EXTERNAL LIBRARIES
include (CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)

if(COMPILER_SUPPORTS_CXX11)
	add_compile_options("-std=c++11")
else()
	message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER} has no C++11 support.")
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
