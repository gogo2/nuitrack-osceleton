project(nuitrack_osceleton_main)

set(SRC_FILES
        OSCSender.cpp
        SkeletonTracker.cpp
        OSCeleton.cpp
        )

add_executable(OSCeleton ${SRC_FILES})

target_link_libraries(OSCeleton PRIVATE
        lo
        nuitrack
        )

