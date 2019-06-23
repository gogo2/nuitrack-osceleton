//
// file OSCSender.cpp
// Created by Bartosz Sobol
//

#include "OSCSender.h"


namespace osceleton {

    OSCSender::OSCSender(const char *address, const char *port) {
        lo_address_ = lo_address_new(address, port);
    }

    OSCSender::~OSCSender() {
        lo_address_free(lo_address_);
    }

    void OSCSender::sendSkeleton(const std::vector<tdv::nuitrack::Skeleton> &skeletons) {
        for (const auto &skeleton : skeletons) {
            processSkeleton(skeleton);
        }
    }

    void OSCSender::processSkeleton(const tdv::nuitrack::Skeleton &skeleton) {
        lo_bundle skeleton_bundle = lo_bundle_new(LO_TT_IMMEDIATE);
        for (const auto &joint : skeleton.joints) {
            if (joint.confidence >= 0.5) {
//                printf("I");

                lo_message joint_message = lo_message_new();
                lo_message_add_int32(joint_message, skeleton.id);
                lo_message_add_string(joint_message, jointTypeName.at(joint.type).c_str());

                lo_message_add_float(joint_message, joint.proj.x);
                lo_message_add_float(joint_message, joint.proj.y);
                lo_message_add_float(joint_message, joint.proj.z);

                lo_bundle_add_message(skeleton_bundle, "/joint", joint_message);

                if (send_orient_) {
                    lo_message orient_message = lo_message_new();
                    // x data is in first column
                    lo_message_add_float(orient_message, joint.orient.matrix[0]);
                    lo_message_add_float(orient_message, joint.orient.matrix[0 + 3]);
                    lo_message_add_float(orient_message, joint.orient.matrix[0 + 6]);
                    // y data is in 2nd column
                    lo_message_add_float(orient_message, joint.orient.matrix[1]);
                    lo_message_add_float(orient_message, joint.orient.matrix[1 + 3]);
                    lo_message_add_float(orient_message, joint.orient.matrix[1 + 6]);
                    // z data is in 3rd column
                    lo_message_add_float(orient_message, joint.orient.matrix[2]);
                    lo_message_add_float(orient_message, joint.orient.matrix[2 + 3]);
                    lo_message_add_float(orient_message, joint.orient.matrix[2 + 6]);
                    lo_bundle_add_message(skeleton_bundle, "/orient", orient_message);
                }

            }
        }
        printf("\n");
        lo_send_bundle(lo_address_, skeleton_bundle);
    }

    void OSCSender::sendIntMessage(const char *address, const int content) {
        printf("%s: %d", address, content);
        lo_send(lo_address_, address, "i", content);
    }

}
