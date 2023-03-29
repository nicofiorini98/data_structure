set(LIBRARY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/sources/Node.cpp
                     ${CMAKE_CURRENT_SOURCE_DIR}/sources/Edge.cpp
                     ${CMAKE_CURRENT_SOURCE_DIR}/sources/TreePtrList.cpp
)

set(LIBRARY_INCLUDES "./include" ) #"${CMAKE_BINARY_DIR}/configured_files/include"

# Nico Library
add_library(${LIBRARY_NAME} INTERFACE)
target_include_directories(${LIBRARY_NAME} INTERFACE ${LIBRARY_INCLUDES})
target_sources(${LIBRARY_NAME} PUBLIC ${LIBRARY_SOURCES})