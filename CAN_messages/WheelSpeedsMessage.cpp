//
// Created by tomer on 08/07/2022.
//
#include "WheelSpeedsMessage.h"
#include <random>
#include <sstream>

const int WHEEL_SPEEDS_MESSAGE_TYPE = 464;
const int MAX_SPEED = 25000; //unit: 0.01 kph

std::string randomSpeed()
{
    float speed = ((float)(rand()%MAX_SPEED+1))/100;
    std::stringstream buffer;
    buffer << speed;
    return buffer.str();
}

std::string randomWheelsData()
{
    std::string unit = " kph";
    std::string divider = " | ";
    std::string data=
            "WHEEL_SPEED_FL: " + randomSpeed() + unit + divider + "WHEEL_SPEED_FR: "+ randomSpeed() + unit + divider +
            "WHEEL_SPEED_RL: " + randomSpeed() + unit + divider + "WHEEL_SPEED_RR: " + randomSpeed() + unit;
    return data;
}

WheelSpeedsMessage::WheelSpeedsMessage(std::chrono::high_resolution_clock::duration time):
    Message(WHEEL_SPEEDS_MESSAGE_TYPE, randomWheelsData(), time)
{}