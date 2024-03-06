cmake_minimum_required(VERSION 3.27)

project(collections_commons C)

OPTION(BUILD_TESTS "Build unit tests" ON)

OPTION(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    if (BUILD_TESTS)
        message(STATUS "Tests are included. Set BUILD_TESTS to OFF to diable.")
    else ()
        message(STATUS "Tests not included. Set BUILD_TESTS to ON to enable tests.")
    endif ()

    if (BUILD_DOC)
        find_package(Doxygen REQUIRED)

        if (DOXYGEN_FOUND)
            # set input and output files
            set(DOXYGEN_IN doc/Doxyfile.in)
            set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

            # request to configure the file
            configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
            message(STATUS "Doxygen build started")

            # note the option ALL which allows to build the docs together with the application
            add_custom_target(${PROJECT_NAME}_doc  ALL
                    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    COMMENT "Generating API documentation with Doxygen"
                    VERBATIM )
        else (DOXYGEN_FOUND)
            message(STATUS "Doxygen need to be installed to generate the doxygen documentation")
        endif (DOXYGEN_FOUND)
    endif ()

    #ADD GTEST

endif ()

### OUTPUT LIBRARY CONFIGURATION PER COMPILER ###
set(CMAKE_C_STANDARD 99)
if (CMAKE_GENERATOR MATCHES "Visual Studio")
    set(CMAKE_ROOT_DIRECTORY ${CMAKE_SOURCE_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/msbuild)
    set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/msbuild/compiled)
    set(CMAKE_PDB_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/build/msbuild/pdb)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/msbuild/archive)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/msbuild/lib)
elseif (CMAKE_GENERATOR MATCHES "MinGW Makefiles")
    set(CMAKE_SYSTEM_PROCESSOR x64)
    set(CMAKE_ROOT_DIRECTORY ${CMAKE_SOURCE_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/mingw32_x86/)
    #set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/mingw32_x86/compiled)
    #set(CMAKE_PDB_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/build/mingw32_x86/pdb)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/mingw32_x86/archive)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/mingw32_x86/lib)
    if (CMAKE_SYSTEM_NAME MATCHES "Linux")
        if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
            set(CMAKE_ROOT_DIRECTORY ${CMAKE_SOURCE_DIR})
            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/gnu/)
            #set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/gnu/compiled)
            #set(CMAKE_PDB_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/build/gnu/pdb)
            set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/gnu/archive)
            set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/gnu/lib)
        elseif (CMAKE_C_COMPILER_ID STREQUAL "Clang")
            set(CMAKE_ROOT_DIRECTORY ${CMAKE_SOURCE_DIR})
            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/clang/)
            #set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/clang/compiled)
            #set(CMAKE_PDB_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/build/clang/pdb)
            set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/clang/archive)
            set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/clang/lib)
        endif ()
    endif ()
endif ()


file(GLOB_RECURSE HEADERS_FILES
        ${PROJECT_SOURCE_DIR}/headers/*.h
        ${PROJECT_SOURCE_DIR}/headers/*.inl
)
file(GLOB_RECURSE SOURCES_FILES
        ${PROJECT_SOURCE_DIR}/src/*.c
)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    if (BUILD_TESTS)
        add_subdirectory(tests)
        add_subdirectory(third-party/googletest)
        include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
    endif ()
endif ()

find_package(Threads REQUIRED)
if (THREADS_HAVE_PTHREAD_ARG)
    target_compile_options(${PROJECT_NAME} PUBLIC "-pthread")
endif ()
if (CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(${PROJECT_NAME} "${CMAKE_THREAD_LIBS_INIT}")
endif ()

include_directories(${PROJECT_SOURCE_DIR}/headers)

add_library(${PROJECT_NAME} SHARED ${SOURCES_FILES} ${HEADERS_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/headers)
