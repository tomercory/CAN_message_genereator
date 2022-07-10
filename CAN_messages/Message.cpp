//
// Created by tomer on 08/07/2022.
//

#include "Message.h"

Message::Message(int type, std::string data, std::chrono::high_resolution_clock::duration time):
m_type(type),
m_data(data),
m_time(time)
{}

std::string Message::messageDivision()
{
    return ", ";
}

char Message::timeDivision()
{
    return ':';
}

void printTime (std::ostream& os, std::chrono::high_resolution_clock::duration duration)
{
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    duration -= minutes;
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    duration -= seconds;
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    duration -= milliseconds;
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration);

    os << minutes.count() << Message::timeDivision() << seconds.count() << Message::timeDivision()
        << milliseconds.count() << Message::timeDivision() << microseconds.count() << Message::messageDivision();
}

void Message::print(std::ostream& os) const
{
    printTime(os, m_time);
    os << m_type << messageDivision() << m_data << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Message& message)
{
    message.print(os);
    return os;
}