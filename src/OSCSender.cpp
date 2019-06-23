//
// file OSCSender.cpp
// Created by Bartosz Sobol
//

#include "OSCSender.h"


namespace osceleton {

    OSCSender::OSCSender(const char *address, const char *port) : lo_address_{lo_address_new(address, port)} {

    }

    void OSCSender::sendSkeleton(const tdv::nuitrack::SkeletonData::Ptr &skeleton_data) {
        XnUserID aUsers[15];
        XnUInt16 nUsers = 15;
        userGenerator.GetUsers(aUsers, nUsers);
        for (int i = 0; i < nUsers; ++i) {
            if (userGenerator.GetSkeletonCap().IsTracking(aUsers[i])) {
                lo_bundle bundle = lo_bundle_new(LO_TT_IMMEDIATE);

                if (jointPos(aUsers[i], XN_SKEL_HEAD) == 0) {
                    genOscMsg(&bundle, "head");
                }
                if (jointPos(aUsers[i], XN_SKEL_NECK) == 0) {
                    genOscMsg(&bundle, "neck");
                }
                if (jointPos(aUsers[i], XN_SKEL_LEFT_COLLAR) == 0) {
                    genOscMsg(&bundle, "l_collar");
                }
                if (jointPos(aUsers[i], XN_SKEL_LEFT_SHOULDER) == 0) {
                    genOscMsg(&bundle, "l_shoulder");
                }
                if (jointPos(aUsers[i], XN_SKEL_LEFT_ELBOW) == 0) {
                    genOscMsg(&bundle, "l_elbow");
                }
                if (jointPos(aUsers[i], XN_SKEL_LEFT_WRIST) == 0) {
                    genOscMsg(&bundle, "l_wrist");
                }
                if (jointPos(aUsers[i], XN_SKEL_LEFT_HAND) == 0) {
                    genOscMsg(&bundle, "l_hand");
                }
                if (jointPos(aUsers[i], XN_SKEL_LEFT_FINGERTIP) == 0) {
                    genOscMsg(&bundle, "l_fingertip");
                }
                if (jointPos(aUsers[i], XN_SKEL_RIGHT_COLLAR) == 0) {
                    genOscMsg(&bundle, "r_collar");
                }
                if (jointPos(aUsers[i], XN_SKEL_RIGHT_SHOULDER) == 0) {
                    genOscMsg(&bundle, "r_shoulder");
                }
                if (jointPos(aUsers[i], XN_SKEL_RIGHT_ELBOW) == 0) {
                    genOscMsg(&bundle, "r_elbow");
                }
                if (jointPos(aUsers[i], XN_SKEL_RIGHT_WRIST) == 0) {
                    genOscMsg(&bundle, "r_wrist");
                }
                if (jointPos(aUsers[i], XN_SKEL_RIGHT_HAND) == 0) {
                    genOscMsg(&bundle, "r_hand");
                }
                if (jointPos(aUsers[i], XN_SKEL_RIGHT_FINGERTIP) == 0) {
                    genOscMsg(&bundle, "r_fingertip");
                }
                if (jointPos(aUsers[i], XN_SKEL_TORSO) == 0) {
                    genOscMsg(&bundle, "torso");
                }
                if (jointPos(aUsers[i], XN_SKEL_WAIST) == 0) {
                    genOscMsg(&bundle, "waist");
                }
                if (jointPos(aUsers[i], XN_SKEL_LEFT_HIP) == 0) {
                    genOscMsg(&bundle, "l_hip");
                }
                if (jointPos(aUsers[i], XN_SKEL_LEFT_KNEE) == 0) {
                    genOscMsg(&bundle, "l_knee");
                }
                if (jointPos(aUsers[i], XN_SKEL_LEFT_ANKLE) == 0) {
                    genOscMsg(&bundle, "l_ankle");
                }
                if (jointPos(aUsers[i], XN_SKEL_LEFT_FOOT) == 0) {
                    genOscMsg(&bundle, "l_foot");
                }
                if (jointPos(aUsers[i], XN_SKEL_RIGHT_HIP) == 0) {
                    genOscMsg(&bundle, "r_hip");
                }
                if (jointPos(aUsers[i], XN_SKEL_RIGHT_KNEE) == 0) {
                    genOscMsg(&bundle, "r_knee");
                }
                if (jointPos(aUsers[i], XN_SKEL_RIGHT_ANKLE) == 0) {
                    genOscMsg(&bundle, "r_ankle");
                }
                if (jointPos(aUsers[i], XN_SKEL_RIGHT_FOOT) == 0) {
                    genOscMsg(&bundle, "r_foot");
                }

                lo_send_bundle(addr, bundle);
            } else {
                sendUserPosMsg(aUsers[i]);
            }
        }
    }
}
