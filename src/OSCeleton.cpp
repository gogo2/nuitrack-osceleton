
//
// file OSCeleton.cpp
// Created by Bartek
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <functional>

#include "SkeletonTracker.h"
#include "OSCSender.h"

char *ADDRESS = (char *) "127.0.0.1";
char *PORT = (char *) "7110";

int usage(char *name);

int main(int argc, char **argv) {
    int return_code = EXIT_SUCCESS;
    std::cout << "Starting OSCeleton..." << std::endl;
    unsigned arg = 1;
    bool require_argument = false;

    while (arg < argc and argv[arg][0] == '-') {
        switch (argv[arg][1]) {
            case 'h':
                usage(argv[0]);
                break;
            case 'a':
            case 'p':
                require_argument = true;
                break;
            default:
                break;
        }

        if (require_argument and arg + 1 >= argc) {
            std::cout << "The option " << argv[arg] << " require an argument." << std::endl;
            usage(argv[0]);
        }

        switch (argv[arg][1]) {
            case 'h':
                usage(argv[0]);
                break;
            case 'a':
                ADDRESS = argv[arg + 1];
                break;
            case 'p':
                if (strtol(argv[arg + 1], nullptr, 10)) {
                    PORT = argv[arg + 1];
                } else {
                    std::cout << "Bad port number given." << std::endl;
                    exit(-1);
                }
                break;
            default:
                break;
        }
    }

    try {
        osceleton::OSCSender osc_sender(ADDRESS, PORT);
        osceleton::SkeletonTracker skeleton_tracker{};

        auto on_new = [&osc_sender](tdv::nuitrack::SkeletonTracker::Ptr tracker,
                                    int user_id) {
            osc_sender.sendIntMessage("/new_user", user_id);
            printf("dddddd");
        };
        auto on_lost = [&osc_sender](tdv::nuitrack::SkeletonTracker::Ptr tracker,
                                     int user_id) {
            osc_sender.sendIntMessage("/lost_user", user_id);
            printf("dddddd");
        };

        skeleton_tracker.registerOnNewUserCallback(on_new);
        skeleton_tracker.registerOnLostUserCallback(on_lost);
        while (true) {
            try {
                skeleton_tracker.update();
            }
            catch (tdv::nuitrack::LicenseNotAcquiredException &e) {
                std::cerr << "LicenseNotAcquired exception (ExceptionType: " << e.type() << ")" << std::endl;
                return_code = EXIT_FAILURE;
                break;
            }
            printf("d\n");
            osc_sender.sendSkeleton(skeleton_tracker.getSkeletons());
        }

        skeleton_tracker.release_nuitrack();
    }
    catch (const tdv::nuitrack::Exception &e) {
        std::cerr << "Nuitrack release failed (ExceptionType: " << e.type() << ")" << std::endl;
        return_code = EXIT_FAILURE;
    }

    return return_code;
}

int usage(char *name) {
    printf("\nUsage: %s [OPTIONS]\n \
Example: %s -a 127.0.0.1 -p 7110 \n\
\n\
(The above example corresponds to the defaults)\n\
\n\
Options:\n\
  -a <addr>\t Address to send OSC packets to (default: localhost).\n\
  -p <port>\t Port to send OSC packets to (default: 7110).\n\
  -h\t\t Show help.\n\n\
For a more detailed explanation of options consult the README file.\n\n",
           name, name);
    exit(1);
}
