
//
// file OSCeleton.cpp
// Created by Bartosz Sobol
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <cxxopts.hpp>

#include "SkeletonTracker.h"
#include "OSCSender.h"

int main(int argc, char **argv) {
    int return_code = 0;
    try {

        cxxopts::Options options("OSCeleton", "nuitrack-osceleton");

        options.add_options("", {
                {"a, address", "OSC server address", cxxopts::value<std::string>()->default_value("127.0.0.1")},
                {"p, port",    "OSC server port",    cxxopts::value<std::string>()->default_value("7110")},
                {"h, help",    "Help"}
        });

        auto parsed_options = options.parse(argc, argv);

        if (parsed_options.count("help")) {
            std::cout << options.help();
            exit(0);
        }

        std::string address = parsed_options["address"].as<std::string>();
        std::string port = parsed_options["port"].as<std::string>();

        std::cout << "Starting OSCeleton..." << std::endl;

        osceleton::OSCSender osc_sender(address, port);
        std::cout << "OSC address: " << address << "::" << port << std::endl;

        osceleton::SkeletonTracker skeleton_tracker{};

        skeleton_tracker.registerOnNewUserCallback(
                [&osc_sender](int user_id) {
                    printf("NEW USER: %d\n", user_id);
                    osc_sender.sendIntMessage("/new_user", user_id);
                });
        skeleton_tracker.registerOnLostUserCallback(
                [&osc_sender](int user_id) {
                    printf("LOST USER: %d\n", user_id);
                    osc_sender.sendIntMessage("/lost_user", user_id);
                });
        while (true) {
            try {
                skeleton_tracker.update();
            }
            catch (tdv::nuitrack::LicenseNotAcquiredException &e) {
                std::cerr << "LicenseNotAcquired exception (ExceptionType: " << e.type() << ")" << std::endl;
                return_code = 1;
                break;
            }
            osc_sender.sendSkeletons(skeleton_tracker.getSkeletons());
        }

        skeleton_tracker.release_nuitrack();
    }
    catch (const tdv::nuitrack::Exception &e) {
        std::cerr << "Nuitrack release failed (ExceptionType: " << e.type() << ")" << std::endl;
        return_code = 1;
    }
    catch (const cxxopts::OptionException &e) {
        std::cout << "error parsing options: " << e.what() << std::endl;
        return_code = 1;
    }

    return return_code;
}
