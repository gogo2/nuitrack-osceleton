//
// file SkeletonTracker.cpp
// Created by Bartosz Sobol
//


#include "SkeletonTracker.h"

namespace osceleton {

    SkeletonTracker::SkeletonTracker() {
        tdv::nuitrack::Nuitrack::init();

        tdv::nuitrack::Nuitrack::run();
    }

    SkeletonTracker::~SkeletonTracker() {
//        release_nuitrack();
    }

    void SkeletonTracker::update() {
        tdv::nuitrack::Nuitrack::update();

        tdv::nuitrack::Nuitrack::waitUpdate(skeleton_tracker_);

        skeleton_data_ = skeleton_tracker_->getSkeletons();
    }

    const tdv::nuitrack::SkeletonData::Ptr &SkeletonTracker::skeleton_data() const {
        return skeleton_data_;
    }

    void SkeletonTracker::release_nuitrack() {
        tdv::nuitrack::Nuitrack::release();
    }

}

#include "SkeletonTracker.h"
