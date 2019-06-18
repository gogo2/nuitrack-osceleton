//
// file OSCeleton.cpp
// Created by Bartek
//

#include <lo.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>


char *ADDRESS = (char *) "127.0.0.1";
char *PORT = (char *) "7110";

#define OUTPUT_BUFFER_SIZE 1024*16
char osc_buffer[OUTPUT_BUFFER_SIZE];

char tmp[64]; //Temp buffer for OSC address pattern
int userID;
float jointCoords[3];
float jointOrients[9];

float posConfidence;
float orientConfidence;

//Multipliers for coordinate system. This is useful if you use
//software like animata, that needs OSC messages to use an arbitrary
//coordinate system.
double mult_x = 1;
double mult_y = 1;
double mult_z = 1;

//Offsets for coordinate system. This is useful if you use software
//like animata, that needs OSC messages to use an arbitrary coordinate
//system.
double off_x = 0.0;
double off_y = 0.0;
double off_z = 0.0;

// hand data
float handCoords[3];
bool haveHand = false;

bool kitchenMode = false;
bool handMode = false;
bool mirrorMode = true;
bool play = false;
bool record = false;
bool sendRot = false;
bool filter = false;
bool preview = false;
bool raw = false;
bool sendOrient = false;
int nDimensions = 3;

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

    while (true) {
        try {
            tdv::nuitrack::Nuitrack::waitUpdate(handTracker);
        }
        catch (tdv::nuitrack::LicenseNotAcquiredException &e) {
            std::cerr << "LicenseNotAcquired exception (ExceptionType: " << e.type() << ")" << std::endl;
            return_code = EXIT_FAILURE;
            break;
        }
        catch (const tdv::nuitrack::Exception &e) {
            std::cerr << "Nuitrack update failed (ExceptionType: " << e.type() << ")" << std::endl;
            return_code = EXIT_FAILURE;
            break;
        }
    }

    try {
        tdv::nuitrack::Nuitrack::release();
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

void genOscMsg(lo_bundle *bundle, char *name) {

    if (handMode || posConfidence >= 0.5f) {
        lo_message msg = lo_message_new();

        lo_message_add_string(msg, name);

        if (!kitchenMode)
            lo_message_add_int32(msg, userID);

        for (int i = 0; i < nDimensions; i++)
            lo_message_add_float(msg, jointCoords[i]);

        lo_bundle_add_message(*bundle, "/joint", msg);
    }

    if (!kitchenMode && sendOrient && orientConfidence >= 0.5f) {
        lo_message msg = lo_message_new();

        lo_message_add_string(msg, name);

        if (!kitchenMode)
            lo_message_add_int32(msg, userID);

        // x data is in first column
        lo_message_add_float(msg, jointOrients[0]);
        lo_message_add_float(msg, jointOrients[0 + 3]);
        lo_message_add_float(msg, jointOrients[0 + 6]);

        // y data is in 2nd column
        lo_message_add_float(msg, jointOrients[1]);
        lo_message_add_float(msg, jointOrients[1 + 3]);
        lo_message_add_float(msg, jointOrients[1 + 6]);

        // z data is in 3rd column
        lo_message_add_float(msg, jointOrients[2]);
        lo_message_add_float(msg, jointOrients[2 + 3]);
        lo_message_add_float(msg, jointOrients[2 + 6]);

        lo_bundle_add_message(*bundle, "/orient", msg);
    }
}
