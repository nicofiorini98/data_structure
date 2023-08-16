set(LIBRARY_HEADERS 
                     ${CMAKE_CURRENT_SOURCE_DIR}/include/Graph.h
                     ${CMAKE_CURRENT_SOURCE_DIR}/include/GraphAdjList.h
                     ${CMAKE_CURRENT_SOURCE_DIR}/include/GraphEdgeList.h
                     ${CMAKE_CURRENT_SOURCE_DIR}/include/GraphIncList.h
                     ${CMAKE_CURRENT_SOURCE_DIR}/include/GraphIncMatrix.h
                     )

set(LIBRARY_SOURCES  ${CMAKE_CURRENT_SOURCE_DIR}/sources/GraphAdjList.cpp
                     ${CMAKE_CURRENT_SOURCE_DIR}/sources/GraphEdgeList.cpp
                     ${CMAKE_CURRENT_SOURCE_DIR}/sources/GraphIncList.cpp
)

set(LIBRARY_INCLUDES "./include" ) #"${CMAKE_BINARY_DIR}/configured_files/include"

# Nico Library
add_library(${GRAPH_LIB_NAME} STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_link_libraries(${GRAPH_LIB_NAME} PUBLIC ${UTIL_LIB_NAME} ${TREE_LIB_NAME})
target_include_directories(${GRAPH_LIB_NAME} PUBLIC ${LIBRARY_INCLUDES})
#target_sources(${LIBRARY_NAME} PUBLIC ${LIBRARY_SOURCES})
