//
// file OSCSender.cpp
// Created by Bartosz Sobol
//

#include "OSCSender.h"


namespace osceleton {

    OSCSender::OSCSender(const std::string &address, const std::string &port) : lo_address_{address.c_str(),
                                                                                            port.c_str()} {}

    void OSCSender::sendSkeletons(const std::vector<tdv::nuitrack::Skeleton> &skeletons) {
        for (const auto &skeleton : skeletons) {
            processSkeleton(skeleton);
        }
    }

    void OSCSender::processSkeleton(const tdv::nuitrack::Skeleton &skeleton) {
        lo::Bundle skeleton_bundle{};
        for (const auto &joint : skeleton.joints) {
            if (joint.confidence >= 0.5) {
                printf("%d", skeleton.id);
                lo::Message joint_message{};
                joint_message.add_int32(skeleton.id);
                joint_message.add_string(jointTypeName.at(joint.type).c_str());

                joint_message.add_float(joint.proj.x);
                joint_message.add_float(joint.proj.y);
                joint_message.add_float(joint.proj.z);

                skeleton_bundle.add("/joint", joint_message);

                if (send_orient_) {
                    lo::Message orient_message{};

                    orient_message.add_float(joint.orient.matrix[0]);
                    orient_message.add_float(joint.orient.matrix[0 + 3]);
                    orient_message.add_float(joint.orient.matrix[0 + 6]);

                    orient_message.add_float(joint.orient.matrix[1]);
                    orient_message.add_float(joint.orient.matrix[1 + 3]);
                    orient_message.add_float(joint.orient.matrix[1 + 6]);

                    orient_message.add_float(joint.orient.matrix[2]);
                    orient_message.add_float(joint.orient.matrix[2 + 3]);
                    orient_message.add_float(joint.orient.matrix[2 + 6]);

                    skeleton_bundle.add("/orient", orient_message);
                }
            }
        }
        printf("\n");
        lo_address_.send(skeleton_bundle);
    }

    void OSCSender::sendIntMessage(const char *address, const int content) {
        lo_address_.send(address, "i", content);
    }

}
