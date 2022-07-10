//
// Created by tomer on 07/07/2022.
//

#ifndef CAN_MESSAGE_GENERATOR_UTILITIES_H
#define CAN_MESSAGE_GENERATOR_UTILITIES_H
#include <iostream>
#include <fstream>

/**
 * sends an error message about failure to open file.
 * @param target
 *      where the error message will be sent.
 * @param fileName
 *      the name of the file that failed to open.
 */
void cannotOpenFileErrorMessage(std::ostream& target, std::string fileName);

/**
 * sends an error message about incorrect usage of the program and instructions for correct usage.
 * @param target
 *      where the error message will be sent.
 */
void incorrectUsageErrorMessage(std::ofstream& target);

/**
 * @param argc
 *      number of arguments that have been used to call the program.
 * @param argv
 *      the array of the arguments that have been used to call the program.
 * @param defaultVal
 *      the default value for the session time.
 * @return
 *      returns the session time (in seconds), based on the arguments received.
 */
float setSessionTime(int argc, char** argv, const float defaultVal);

/**
 * to be used when an exception is caught- prints the exception's description into a chosen file.
 * @param target
 *      the file to print into.
 * @param e
 *      the caught exception.
 */
void exceptionHandler (std::ofstream& target, std::exception e);







#endif //CAN_MESSAGE_GENERATOR_UTILITIES_H
