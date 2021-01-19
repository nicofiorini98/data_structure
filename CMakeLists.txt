project(data_structure)

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set (CMAKE_CXX_STANDARD 14)

# ottengo tutti i sorgenti
file(GLOB my_sources *.h *.cpp *.qrc)

# aggiungo eseguibile
add_executable(data_structure ${my_sources})
