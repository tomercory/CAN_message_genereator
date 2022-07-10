
#include "utilities.h"
#include "../MessageGenerator.h"
#include <iostream>

const float DEFAULT_DRIVE_SESSION_TIME = 600.0;
const float MIN_SESSION_TIME = 1.0;
const float MAX_SESSION_TIME = 1800.0;
const char* OUTPUT_FILE_NAME = "CAN_message_generator_output";
const char* SUMMARY_REPORT_FILE_NAME = "CAN_message_generator_report";


int main(int argc, char** argv) {
    std::ofstream summaryReport(SUMMARY_REPORT_FILE_NAME);
    if (!summaryReport)
    {
        cannotOpenFileErrorMessage(std::cerr, SUMMARY_REPORT_FILE_NAME);
        return 0;
    }
    if (argc != 2 && argc != 1)
    {
        incorrectUsageErrorMessage(summaryReport);
        return 0;
    }
    float sessionTime;
    try
    {
        sessionTime = setSessionTime(argc, argv, DEFAULT_DRIVE_SESSION_TIME);
        if (sessionTime<MIN_SESSION_TIME || sessionTime > MAX_SESSION_TIME)
        {
            throw std::invalid_argument("Invalid session time\n");
        }
        MessageGenerator::getInstance().run(sessionTime, OUTPUT_FILE_NAME, summaryReport);
    }
    catch (std::exception& e)
    {
        exceptionHandler(summaryReport, e);
        return 0;
    }

    return 0;
}
