//
// Created by tomer on 08/07/2022.
//

#include "BrakeModuleMessage.h"
#include "random"
#include <sstream>

const int BRAKE_MODULE_MESSAGE_TYPE = 446;


std::string randomBrakeData()
{
    int brakeMode = rand()%2;
    std::stringstream buffer;
    buffer << "BRAKE_PRESSED: " << brakeMode;
    return buffer.str();
}

BrakeModuleMessage::BrakeModuleMessage(std::chrono::high_resolution_clock::duration time):
    Message(BRAKE_MODULE_MESSAGE_TYPE, randomBrakeData(), time)
{}