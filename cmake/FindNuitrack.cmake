#  NUITRACK_FOUND - system has NUITRACK
#  NUITRACK_INCLUDE_DIRS - the NUITRACK include directories
#  NUITRACK_LIBRARIES - link these to use NUITRACK

include(ext/LibFindMacros)

if (APPLE)
    message(FATAL_ERROR "MAC OS is not supported by Nuitrack")
endif ()

if ("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
    message(STATUS "Looking for 64bit NUITRACK")
    if (WIN32)
        set(NUITRACK_ARCH win64)
    elseif (UNIX AND NOT APPLE)
        set(NUITRACK_ARCH linux64)
    endif ()
else ()
    message(STATUS "Looking for 32bit NUITRACK")
    if (WIN32)
        set(NUITRACK_ARCH win32)
    elseif (UNIX AND NOT APPLE)
        message(FATAL_ERROR "32bit Linux is not supported by Nuitrack")
    endif ()
endif ()

set(NUITRACK_BASE_DIR ${NUITRACK_SDK_DIR}/Nuitrack)

#if (WIN32)
#    set(NUITRACK_BASE_DIR $ENV{NUITRACK_SDK_DIR})
#elseif (UNIX AND NOT APPPLE)
    #set(NUITRACK_BASE_DIR ${NUITRACK_INSTALL_DIR})
#endif ()

message(STATUS ${NUITRACK_BASE_DIR}/lib/${NUITRACK_ARCH})
find_path(NUITRACK_INCLUDE_DIR
        NAMES
        Nuitrack.h
        PATHS
        ${NUITRACK_BASE_DIR}/include/nuitrack
        )

find_library(NUITRACK_LIBRARY
        NAMES
        nuitrack
        PATHS
        ${NUITRACK_BASE_DIR}/lib/${NUITRACK_ARCH}
        )

set(NUITRACK_PROCESS_INCLUDES NUITRACK_INCLUDE_DIR)
set(NUITRACK_PROCESS_LIBS NUITRACK_LIBRARY)
libfind_process(NUITRACK)

message(STATUS "NUITRACK_LIBRARIES: ${NUITRACK_LIBRARIES}")
message(STATUS "NUITRACK_INCLUDE_DIRS: ${NUITRACK_INCLUDE_DIRS}")
