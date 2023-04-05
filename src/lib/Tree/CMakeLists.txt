set(LIBRARY_HEADERS  ${CMAKE_CURRENT_SOURCE_DIR}/include/TreePtrList.h
                     ${CMAKE_CURRENT_SOURCE_DIR}/include/TreePosVector.h
                     ${CMAKE_CURRENT_SOURCE_DIR}/include/Tree.h
)

set(LIBRARY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/sources/TreePtrList.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/sources/TreePosVector.cpp
                    )

set(LIBRARY_INCLUDES "./include" )

# Nico Library
add_library(${TREE_LIB_NAME} STATIC ${LIBRARY_SOURCES}) # ${LIBRARY_HEADERS}
target_link_libraries(${TREE_LIB_NAME} PUBLIC ${UTIL_LIB_NAME})
target_include_directories(${TREE_LIB_NAME} PUBLIC ${LIBRARY_INCLUDES})

# Collego la libreria privata di Utils, questa Utils non dovrà essere visibile come libreria esterna

