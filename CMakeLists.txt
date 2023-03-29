cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(nicoLib VERSION 1 LANGUAGES C CXX)


# Global CMake variables are set here
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Project/Library Names
set(LIBRARY_NAME "nico")
## set(UNIT_TEST_NAME "unit_tests")
set(EXECUTABLE_NAME "executable")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)

include(Docs)


# SUB DIRECTORIES

add_subdirectory(configured)
#add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(app)
#add_subdirectory(tests)

# aggiungo eseguibile
#add_executable(${EXECUTABLE_NAME} ${my_sources} GraphIncMatrix.h)

# TODO INSTALL TARGETS