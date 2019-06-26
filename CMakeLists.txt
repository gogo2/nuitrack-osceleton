cmake_minimum_required(VERSION 3.0)
project(nuitrack_osceleton VERSION 0.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -pedantic -Wall -static-libstdc++ ")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
#set(CMAKE_VERBOSE_MAKEFILE on)

set(BUILD_DIR ${PROJECT_SOURCE_DIR}/build)
set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib)
set(LO_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/lib/liblo-0.30)
link_directories(${BUILD_DIR})
include_directories(${LIB_DIR})
include_directories(${LO_INCLUDE_DIR})


set(USER_LIB_DIR ${PROJECT_SOURCE_DIR}/../../_lib/lib)
set(USER_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../../_lib/include)
link_directories(${USER_LIB_DIR})
include_directories(${USER_INCLUDE_DIR})


add_subdirectory(${PROJECT_SOURCE_DIR}/lib/liblo-0.30/cmake)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)