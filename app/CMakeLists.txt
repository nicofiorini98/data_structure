set(APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

add_executable(${EXECUTABLE_NAME} ${APP_SOURCES})

#message(----- ${TREE_LIB_NAME})

target_link_libraries(
    ${EXECUTABLE_NAME}
    PUBLIC ${TREE_LIB_NAME} ${GRAPH_LIB_NAME})

