cmake_minimum_required(VERSION 3.22.3)

set(PROJECT_NAME collections_tests)

project(${PROJECT_NAME} CXX)

file(GLOB_RECURSE TEST_HEADERS_FILES
        ${PROJECT_SOURCE_DIR}/headers/*.h)

file(GLOB_RECURSE TEST_SOURCES_FILES
        ${PROJECT_SOURCE_DIR}/src/*.cpp)

include_directories(${PROJECT_SOURCE_DIR}/headers)


add_executable(${PROJECT_NAME} ${TEST_SOURCES_FILES} ${TEST_HEADERS_FILES} main.cpp)

add_dependencies(${PROJECT_NAME} ${CMAKE_PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} gtest gtest_main ${CMAKE_PROJECT_NAME})
