cmake_minimum_required(VERSION 3.22.3)

set(PROJECT_NAME tests)

project(${PROJECT_NAME} CXX)

file(GLOB_RECURSE HEADERS_FILES
        ${PROJECT_SOURCE_DIR}/headers/*.h

)
file(GLOB_RECURSE SOURCES_FILES
        ${PROJECT_SOURCE_DIR}/src/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES_FILES} ${HEADERS_FILES})

include_directories( ${CMAKE_SOURCE_DIR}/headers)
include_directories( ${PROJECT_SOURCE_DIR}/headers)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} gtest gtest_main)
else ()
    target_link_libraries(${PROJECT_NAME} gtest gtest_main)
endif()

add_test(NAME client_run_test  COMMAND ${PROJECT_NAME}  )