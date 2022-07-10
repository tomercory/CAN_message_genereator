//
// Created by tomer on 08/07/2022.
//
#include "utilities.h"


void cannotOpenFileErrorMessage(std::ostream& target, std::string fileName)
{
    target << "Error: Cannot open file " << fileName << std::endl;
}

void incorrectUsageErrorMessage(std::ofstream& target)
{
    target << "Error: Incorrect usage." << std::endl;
    target << "Usage: ./CAN_message_generator or ./CAN_message_generator <DRIVE_SESSION_TIME>" << std::endl;
}

float setSessionTime(int argc, char** argv, const float defaultVal)
{
    float sessionTime;
    if (argc == 1)
    {
        sessionTime = defaultVal;
    }
    else
    {
        sessionTime = std::stof(argv[1]);
    }
    return sessionTime;
}


void exceptionHandler (std::ofstream& target, std::exception e)
{
    target << "Exception: " << e.what();
}

