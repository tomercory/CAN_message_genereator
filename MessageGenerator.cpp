//
// Created by tomer on 07/07/2022.
//
#include <chrono>
#include <thread>
#include "MessageGenerator.h"
#include "CAN_messages/WheelSpeedsMessage.h"
#include "CAN_messages/BrakeModuleMessage.h"
#include "tool/utilities.h"


const int MESSAGE_RATIO = 10;
const int CONVERT_TO_MICRO = 1000000;
const auto TIME_INTERVAL = std::chrono::microseconds(10000);
const auto MESSAGE_TIMING_BIAS = std::chrono::microseconds(3030);

int calculateMessageNum (int numOfRounds)
{
    return numOfRounds + numOfRounds/10;
}

void summarizeSentMessages(std::ostream& summaryFile, int numOfRounds)
{
    int messageNum = calculateMessageNum(numOfRounds);
    summaryFile << "Total number of messages sent: " << messageNum << std::endl;
}

std::chrono::high_resolution_clock::duration decipherTime (const std::string& line)
{
    //auto duration = std::chrono::high_resolution_clock::duration();
    unsigned int startIndex = 0;
    unsigned int endIndex = line.find(Message::timeDivision());
    int minutes = std::stoi(std::string(line, startIndex, endIndex-startIndex));

    startIndex = endIndex+1;
    endIndex = line.find(Message::timeDivision(), startIndex);
    int seconds = std::stoi(std::string(line, startIndex, endIndex-startIndex));

    startIndex = endIndex+1;
    endIndex = line.find(Message::timeDivision(), startIndex);
    int milliseconds = std::stoi(std::string(line, startIndex, endIndex-startIndex));

    startIndex = endIndex+1;
    endIndex = line.find(Message::messageDivision(), startIndex);
    int microseconds = std::stoi(std::string(line, startIndex, endIndex-startIndex));

    auto duration = std::chrono::minutes(minutes) + std::chrono::seconds (seconds) +
            std::chrono::milliseconds(milliseconds) + std::chrono::microseconds(microseconds);

    return duration;
}

int NextLineDiscrepancy (std::ifstream& outputFile, std::chrono::high_resolution_clock::duration expectedTime)
{
    std::string line;
    std::getline(outputFile, line);
    return std::chrono::duration_cast<std::chrono::microseconds>(decipherTime(line)-expectedTime).count();
}

int calculateTotalDeviation(std::ifstream& outputFile, int numOfRounds)
{
    int totalDeviation = 0;
    std::chrono::high_resolution_clock::duration expectedTime = TIME_INTERVAL;
    for (int i=1; i<=numOfRounds; ++i)
    {
        totalDeviation+= NextLineDiscrepancy(outputFile, expectedTime);
        if (i%MESSAGE_RATIO == 0)
        {
            totalDeviation+= NextLineDiscrepancy(outputFile, expectedTime);
        }
        expectedTime+= TIME_INTERVAL;
    }
    return totalDeviation;
}

void summarizeMessageDeviation(std::ostream& summaryFile, std::ifstream& outputFile, int numOfRounds)
{
    int totalDeviation = calculateTotalDeviation(outputFile, numOfRounds);
    int messageNum = calculateMessageNum(numOfRounds);
    float averageDeviation = ((float)totalDeviation)/messageNum;
    summaryFile << "The average message deviation is: " << averageDeviation << " microseconds" << std::endl;
}

void summarize(const std::string& outputFileName, std::ofstream& summaryFile,int numOfRounds)
{
    summarizeSentMessages(summaryFile, numOfRounds);
    std::ifstream outputFile(outputFileName);
    if (!outputFile)
    {
        cannotOpenFileErrorMessage(summaryFile, outputFileName);
        return;
    }
    summarizeMessageDeviation(summaryFile, outputFile, numOfRounds);
}

void transmit(std::ofstream& outputFile, int roundNum, std::chrono::high_resolution_clock::duration timeSinceStart)
{
    outputFile << WheelSpeedsMessage(timeSinceStart);
    if (roundNum%MESSAGE_RATIO == 0)
    {
        outputFile << BrakeModuleMessage(timeSinceStart);
    }
}


void MessageGenerator::run(const float sessionTime, const std::string& outputFileName, std::ofstream &summaryFile)
{
    int roundCount = 0;
    std::ofstream outputFile(outputFileName);
    if (!outputFile)
    {
        cannotOpenFileErrorMessage(summaryFile, outputFileName);
        return;
    }
    auto startTime = std::chrono::high_resolution_clock::now()+TIME_INTERVAL;
    auto end = startTime + std::chrono::microseconds((unsigned int)(sessionTime*CONVERT_TO_MICRO));
    auto nextTime = startTime;
    std::this_thread::sleep_until(startTime);
    while (std::chrono::high_resolution_clock::now()<end)
    {
        ++roundCount;
        transmit(outputFile, roundCount, std::chrono::high_resolution_clock::now()-startTime);
        nextTime += TIME_INTERVAL;
        std::this_thread::sleep_until(nextTime+MESSAGE_TIMING_BIAS);
    }
    outputFile.close();
    summarize(outputFileName, summaryFile, roundCount);
}

MessageGenerator& MessageGenerator::getInstance()
{
    static MessageGenerator instance;
    return instance;
}

