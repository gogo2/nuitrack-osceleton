project(nuitrack_osceleton_main)

set(SRC_FILES
        OSCeleton.cpp
        )

add_executable(OSCeleton ${SRC_FILES})

target_link_directories(OSCeleton PRIVATE lo)

