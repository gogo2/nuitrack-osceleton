//
// file SkeletonTracker.h
// Created by Bartosz Sobol
//

#ifndef NUITRACK_OSCELETON_SKELETONTRACKER_H
#define NUITRACK_OSCELETON_SKELETONTRACKER_H

#include <nuitrack/Nuitrack.h>

namespace osceleton {

    class SkeletonTracker {
    public:
        SkeletonTracker();

        ~SkeletonTracker();

        std::vector<tdv::nuitrack::Skeleton> getSkeletons() const;

        void registerOnNewUserCallback(tdv::nuitrack::SkeletonTracker::OnNewUser callback);

        void registerOnLostUserCallback(tdv::nuitrack::SkeletonTracker::OnLostUser callback);

        void update();

        void release_nuitrack();

    private:
        tdv::nuitrack::SkeletonTracker::Ptr skeleton_tracker_;
        tdv::nuitrack::SkeletonData::Ptr skeleton_data_;

    };

}


#endif //NUITRACK_OSCELETON_SKELETONTRACKER_H
