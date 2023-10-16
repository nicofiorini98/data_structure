set(LIBRARY_HEADERS  ${CMAKE_CURRENT_SOURCE_DIR}/include/TreePtrList.h
                     ${CMAKE_CURRENT_SOURCE_DIR}/include/TreePosVector.h
                     ${CMAKE_CURRENT_SOURCE_DIR}/include/Tree.h
                     ${CMAKE_CURRENT_SOURCE_DIR}/include/BasicGraph.h
                     ${CMAKE_CURRENT_SOURCE_DIR}/include/Graph.h
                     ${CMAKE_CURRENT_SOURCE_DIR}/include/GraphIncList.h
                     ${CMAKE_CURRENT_SOURCE_DIR}/include/GraphEdgeList.h
                     ${CMAKE_CURRENT_SOURCE_DIR}/include/Node.h
                     ${CMAKE_CURRENT_SOURCE_DIR}/include/Edge.h
                     ${CMAKE_CURRENT_SOURCE_DIR}/include/DHeap.h
)

set(LIBRARY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/sources/TreePtrList.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/sources/TreePosVector.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/sources/GraphIncList.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/sources/GraphEdgeList.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/sources/Node.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/sources/Edge.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/sources/DHeap.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/sources/Tree.cpp
                    )

set(LIBRARY_INCLUDES "./include" )

# Nico Library
add_library(${BRADIPO_LIB_NAME} STATIC ${LIBRARY_SOURCES}) # ${LIBRARY_HEADERS}
# target_link_libraries(${BRADIPO_LIB_NAME} PUBLIC ${UTIL_LIB_NAME})
target_include_directories(${BRADIPO_LIB_NAME} PUBLIC ${LIBRARY_INCLUDES})

# Collego la libreria privata di Utils, questa Utils non dovrà essere visibile come libreria esterna

