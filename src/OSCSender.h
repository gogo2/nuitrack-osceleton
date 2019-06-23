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

        void sendSkeleton(const std::vector<tdv::nuitrack::Skeleton> &skeletons);

    private:

        void processSkeleton(const tdv::nuitrack::Skeleton &skeleton);

        bool send_orient_ = false;
        lo_address lo_address_;

        const std::map<tdv::nuitrack::JointType, std::string> jointTypeName{
                {tdv::nuitrack::JointType::JOINT_HEAD,           "head"},
                {tdv::nuitrack::JointType::JOINT_NECK,           "neck"},
                {tdv::nuitrack::JointType::JOINT_LEFT_COLLAR,    "l_collar"},
                {tdv::nuitrack::JointType::JOINT_LEFT_SHOULDER,  "l_shoulder"},
                {tdv::nuitrack::JointType::JOINT_LEFT_ELBOW,     "l_elbow"},
                {tdv::nuitrack::JointType::JOINT_LEFT_WRIST,     "l_wrist"},
                {tdv::nuitrack::JointType::JOINT_LEFT_HAND,      "l_hand"},
//                {tdv::nuitrack::JointType::JOINT_HEAD, "l_fingertip"},
                {tdv::nuitrack::JointType::JOINT_RIGHT_COLLAR,   "r_collar"},
                {tdv::nuitrack::JointType::JOINT_RIGHT_SHOULDER, "r_shoulder"},
                {tdv::nuitrack::JointType::JOINT_RIGHT_ELBOW,    "r_elbow"},
                {tdv::nuitrack::JointType::JOINT_RIGHT_WRIST,    "r_wrist"},
                {tdv::nuitrack::JointType::JOINT_RIGHT_HAND,     "r_hand"},
//                {tdv::nuitrack::JointType::JOINT_HEAD, "r_fingertip"},
                {tdv::nuitrack::JointType::JOINT_TORSO,          "torso"},
                {tdv::nuitrack::JointType::JOINT_WAIST,          "waist"},
                {tdv::nuitrack::JointType::JOINT_LEFT_HIP,       "l_hip"},
                {tdv::nuitrack::JointType::JOINT_LEFT_KNEE,      "l_knee"},
                {tdv::nuitrack::JointType::JOINT_LEFT_ANKLE,     "l_ankle"},
//                {tdv::nuitrack::JointType::JOINT_HEAD, "l_foot"},
                {tdv::nuitrack::JointType::JOINT_RIGHT_HIP,      "r_hip"},
                {tdv::nuitrack::JointType::JOINT_RIGHT_KNEE,     "r_knee"},
                {tdv::nuitrack::JointType::JOINT_RIGHT_ANKLE,    "r_ankle"},
//                {tdv::nuitrack::JointType::JOINT_HEAD, "r_foot"}
        };

    };

}


#endif //NUITRACK_OSCELETON_OSCSENDER_H
