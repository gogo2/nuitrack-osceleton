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

        explicit SkeletonTracker(bool mirror);

        ~SkeletonTracker();

        std::vector<tdv::nuitrack::Skeleton> getSkeletons() const;

        void registerOnNewUserCallback(const tdv::nuitrack::UserTracker::OnNewUser &callback);

        void registerOnLostUserCallback(const tdv::nuitrack::UserTracker::OnLostUser &callback);

        void update();

        static void release_nuitrack();

    private:
        tdv::nuitrack::DepthSensor::Ptr depth_sensor_;
        tdv::nuitrack::SkeletonTracker::Ptr skeleton_tracker_;
        tdv::nuitrack::UserTracker::Ptr user_tracker_;
        tdv::nuitrack::SkeletonData::Ptr skeleton_data_;

    };

}


#endif //NUITRACK_OSCELETON_SKELETONTRACKER_H
