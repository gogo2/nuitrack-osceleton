//
// file OSCSender.h
// Created by Bartosz Sobol
//

#ifndef NUITRACK_OSCELETON_OSCSENDER_H
#define NUITRACK_OSCELETON_OSCSENDER_H

#include <lo.h>
#include <nuitrack/Nuitrack.h>

namespace osceleton {

    class OSCSender {
    public:
        explicit OSCSender(const char *address = "127.0.0.1", const char *port = "7110");

        void sendSkeleton(const tdv::nuitrack::SkeletonData::Ptr &skeleton_data);


    private:
        lo_address  lo_address_;


    };

}


#endif //NUITRACK_OSCELETON_OSCSENDER_H
