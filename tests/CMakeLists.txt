cmake_minimum_required(VERSION 3.22.3)

set(PROJECT_NAME collections_tests)

project(${PROJECT_NAME} CXX C)

file(GLOB_RECURSE HEADERS_FILES
        ${PROJECT_SOURCE_DIR}/headers/*.h

)
file(GLOB_RECURSE SOURCES_FILES
        ${CMAKE_SOURCE_DIR}/src/*.c
        ${PROJECT_SOURCE_DIR}/src/*.cpp
)
include_directories( ${CMAKE_SOURCE_DIR}/headers)
include_directories( ${PROJECT_SOURCE_DIR}/headers)

add_executable(${PROJECT_NAME} ${SOURCES_FILES} ${HEADERS_FILES})


if(WIN32)
    target_link_libraries(${PROJECT_NAME} gtest gtest_main)
else ()
    target_link_libraries(${PROJECT_NAME} gtest gtest_main)
endif()

add_test(NAME randomized_set_test  COMMAND ${PROJECT_NAME}  )
target_sources(${PROJECT_NAME} PRIVATE  ${CMAKE_SOURCE_DIR}/src/randomized_set.c)
target_sources(${PROJECT_NAME} PRIVATE  ${CMAKE_SOURCE_DIR}/src/linked_list.c)