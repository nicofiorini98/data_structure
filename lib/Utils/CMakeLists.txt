set(UTILS_LIB utils)

set(UTILS_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/Node.h
				  ${CMAKE_CURRENT_SOURCE_DIR}/include/Edge.h)

set(UTILS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/sources/Node.cpp
				  ${CMAKE_CURRENT_SOURCE_DIR}/sources/Edge.cpp)


add_library(${UTIL_LIB_NAME} STATIC ${UTILS_HEADERS} ${UTILS_SOURCES})

target_include_directories(${UTIL_LIB_NAME} PUBLIC include)