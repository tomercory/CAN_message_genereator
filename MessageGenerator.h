//
// Created by tomer on 07/07/2022.
//

#ifndef CAN_MESSAGE_GENERATOR_MESSAGEGENERATOR_H
#define CAN_MESSAGE_GENERATOR_MESSAGEGENERATOR_H

#include <iostream>
#include <fstream>

class MessageGenerator
{
public:

    /**
     * creates a MessageGenerator instance the first time this is called.
     * @return
     *      a reference to the MessageGenerator instance.
    */
    static MessageGenerator& getInstance();

    /**
     * there can only be one.
     */
    MessageGenerator(const MessageGenerator& other) = delete;
    MessageGenerator& operator=(const MessageGenerator& other) = delete;

    /**
     * generates CAN messages and sends them into the output file, creates a summary in the summary file
     * @param sessionTime
     *      the amount of time the transmission should run for (in seconds)
     */
    void run(const float sessionTime, const std::string& outputFileName, std::ofstream& summaryFile);

private:
    MessageGenerator() = default;

};


#endif //CAN_MESSAGE_GENERATOR_MESSAGEGENERATOR_H
