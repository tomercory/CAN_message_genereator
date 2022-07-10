//
// Created by tomer on 08/07/2022.
//

#ifndef CAN_MESSAGE_GENERATOR_MESSAGE_H
#define CAN_MESSAGE_GENERATOR_MESSAGE_H

#include <iostream>
#include <fstream>
#include <chrono>


class Message
{
public:

    /**
     * @return
     *      returns the string that is used to separate between the parts of a message.
     */
    static std::string messageDivision();

    /**
     * @return
     *      returns the character that is used to separate between minutes, seconds, milliseconds and microseconds
     *      in string representation.
     */
    static char timeDivision();

    /**
     * << operator:
     * Prints a Message instance into a desired file.
     *
     * @param os - a reference to the the file into which we print.
     * @param healthPoints - a reference to the Message instance we want to print.
     * @return
     *      os
     */
    friend std::ostream& operator<<(std::ostream& os, const Message& message);

protected:
    Message(int type, std::string data, std::chrono::high_resolution_clock::duration time);
    void print(std::ostream& os) const;

private:
    int m_type;
    std::string m_data;
    std::chrono::high_resolution_clock::duration m_time;

};

#endif //CAN_MESSAGE_GENERATOR_MESSAGE_H
