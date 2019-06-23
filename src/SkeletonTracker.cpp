//
// file SkeletonTracker.cpp
// Created by Bartosz Sobol
//


#include "SkeletonTracker.h"

namespace osceleton {

    SkeletonTracker::SkeletonTracker() {
        tdv::nuitrack::Nuitrack::init();
        skeleton_tracker_ = tdv::nuitrack::SkeletonTracker::create();
        tdv::nuitrack::Nuitrack::run();
    }

    SkeletonTracker::~SkeletonTracker() {
        release_nuitrack();
    }

    void SkeletonTracker::update() {
//        tdv::nuitrack::Nuitrack::update();
        tdv::nuitrack::Nuitrack::waitUpdate(skeleton_tracker_);
        skeleton_data_ = skeleton_tracker_->getSkeletons();
    }

    std::vector<tdv::nuitrack::Skeleton> SkeletonTracker::getSkeletons() const {
        return skeleton_data_->getSkeletons();
    }

    void SkeletonTracker::release_nuitrack() {
        tdv::nuitrack::Nuitrack::release();
    }

    void SkeletonTracker::registerOnNewUserCallback(tdv::nuitrack::SkeletonTracker::OnNewUser callback) {
        skeleton_tracker_->connectOnNewUser([](tdv::nuitrack::SkeletonTracker::Ptr tracker,
                                               int user_id) {
            printf("dsadasdasdasda\n");
        });
    }

    void SkeletonTracker::registerOnLostUserCallback(tdv::nuitrack::SkeletonTracker::OnLostUser callback) {
        skeleton_tracker_->connectOnLostUser(callback);
    }

}


#include "SkeletonTracker.h"
