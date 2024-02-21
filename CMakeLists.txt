
SET(BUILD_TESTS ON)

if (BUILD_TESTS)
    message(STATUS "Tests are included. Set BUILD_TESTS=OFF to diable.")
else ()
    message(STATUS "Tests not included. Set BUILD_TESTS=ON to build tests.")
endif ()

cmake_minimum_required(VERSION 3.27)
project(collections_commons C)
set(CMAKE_C_STANDARD 23)

set(CMAKE_C_STANDARD 23)
if (CMAKE_GENERATOR MATCHES "Visual Studio")
    set(CMAKE_ROOT_DIRECTORY ${CMAKE_SOURCE_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/)
    #set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/compiled)
    #set(CMAKE_PDB_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/build/pdb)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/archive)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)
elseif (CMAKE_GENERATOR MATCHES "MinGW Makefiles")
    set(CMAKE_SYSTEM_PROCESSOR x64)
    set(CMAKE_ROOT_DIRECTORY ${CMAKE_SOURCE_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/mingw32_x86_build/)
    #set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/mingw32_x86_build/compiled)
    #set(CMAKE_PDB_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/mingw32_x86_build/pdb)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/mingw32_x86_build/archive)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/mingw32_x86_build/lib)
    if (CMAKE_SYSTEM_NAME MATCHES "Linux")
        if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
            set(CMAKE_ROOT_DIRECTORY ${CMAKE_SOURCE_DIR})
            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/gnu_build/)
            #set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/gnu_build/compiled)
            #set(CMAKE_PDB_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/gnu_build/pdb)
            set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/gnu_build/archive)
            set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/gnu_build/lib)
        elseif (CMAKE_C_COMPILER_ID STREQUAL "Clang")
            set(CMAKE_ROOT_DIRECTORY ${CMAKE_SOURCE_DIR})
            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/clang_build/)
            #set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/clang_build/compiled)
            #set(CMAKE_PDB_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/clang_build/pdb)
            set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/clang_build/archive)
            set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/clang_build/lib)
        endif ()
    endif ()
endif ()


file(GLOB_RECURSE HEADERS_FILES
        ${PROJECT_SOURCE_DIR}/headers/*.hpp
        ${PROJECT_SOURCE_DIR}/headers/*.h
        ${PROJECT_SOURCE_DIR}/headers/*.inl
)
file(GLOB_RECURSE SOURCES_FILES
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*.c
)

#ADD GTEST
if (BUILD_TESTS)
    add_subdirectory(tests)
    add_subdirectory(third-party/gtest/googletest)
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
endif ()


find_package(Threads REQUIRED)
if (THREADS_HAVE_PTHREAD_ARG)
    target_compile_options(${PROJECT_NAME} PUBLIC "-pthread")
endif ()
if (CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(${PROJECT_NAME} "${CMAKE_THREAD_LIBS_INIT}")
endif ()

include_directories(${PROJECT_SOURCE_DIR}/headers)

add_library(${CMAKE_PROJECT_NAME} SHARED ${SOURCES_FILES} ${HEADERS_FILES})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/headers)
