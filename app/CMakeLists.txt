set(APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/City.h
                ${CMAKE_CURRENT_SOURCE_DIR}/DistanceCity.h)

                

add_executable(${EXECUTABLE_NAME} ${APP_SOURCES})

#message(----- ${TREE_LIB_NAME})

target_link_libraries(
    ${EXECUTABLE_NAME}
    PUBLIC ${BRADIPO_LIB_NAME})

