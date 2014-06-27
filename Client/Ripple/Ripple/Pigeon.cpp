//
//  Pigeon.cpp
//  Ripple
//
//  Created by Giancarlo Mariot on 26/06/2014.
//  Copyright (c) 2014 Giancarlo Mariot. All rights reserved.
//

#include <string>
#include "Pigeon.h"
#include "Data.h"
#include "Output.h"

using namespace std;

const char Pigeon::user[16]    = "bot";
const char Pigeon::action[8]   = "bash";
const char Pigeon::trigger[64] = "\\$HOME/trigger.sh";

int Pigeon::post(const char msg[], bool debug) {
    Data d;
    Output o;
    string serverAddr = d.getServerName();
    if (serverAddr.empty()) {
        o.error("No server defined");
        if (debug) {
            o.debug("No command to be executed");
        }
        return 0;
    }
    snprintf(fullCmd, 512, "ssh %s@%s \"%s %s %s\"", user, serverAddr.c_str(), action, trigger, msg);
    if (debug) {
        o.debug(fullCmd);
    } else {
//        o.print(fullCmd);
        system((char *)fullCmd);
    }
    return 0;
}

int Pigeon::checkOnlineServer(string serverAddr) {
    string pingCommand = "ping -c 1 -W 1000 " + serverAddr;
    FILE *output;
    // cout << "Running " << pingCommand.c_str() << " -- " << endl << endl;
    output = popen(pingCommand.c_str(), "r");
    if (!output){
        fprintf (stderr, "incorrect parameters or too many files.\n");
        return EXIT_FAILURE;
    }
    return pclose(output);
}