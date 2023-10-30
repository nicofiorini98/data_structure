cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(BradipoLib VERSION 1 LANGUAGES CXX)


# Global CMake variables are set here
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_LIBRARIES "-lstdc++")
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# find_path(GRAPHVIZ_INCLUDE_DIRS NAMES graphviz/cgraph.h)
# find_library(GRAPHVIZ_LIBRARIES NAMES cgraph)


#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")

# set(UNIT_TEST_NAME "unit_tests")
set(BRADIPO_LIB_NAME "bradipo")
#set(GRAPH_LIB_NAME "sloth_graph")
#set(UTIL_LIB_NAME "sloth_util")
set(EXECUTABLE_NAME "executable")

# funzione per l'eseguibile di doxygen
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
include(Docs)


# SUB DIRECTORIES

#add_subdirectory(external)
add_subdirectory(lib)
add_subdirectory(app)
#add_subdirectory(tests)

# aggiungo eseguibile
# TODO INSTALL TARGETS

# Specify the installation paths based on the operating system
# if (WIN32)
#     set(install_directory "C:/Program Files/bradipoLib")
# elseif (UNIX)
#     set(install_directory ${CMAKE_SOURCE_DIR}/install)
# endif()

# install(
#     targets ${bradipo_lib_name}
#     destination ${install_directory}
# )

# install(
#     directory ${cmake_source_dir}/lib/bradipolib/include/
#     destination ${install_directory}/include
#     files_matching pattern "*.h"
# )
