//
// Created by tomer on 08/07/2022.
//

#ifndef CAN_MESSAGE_GENERATOR_WHEELSPEEDSMESSAGE_H
#define CAN_MESSAGE_GENERATOR_WHEELSPEEDSMESSAGE_H


#include "Message.h"

class WheelSpeedsMessage : public Message
{
public:
    /**
     * creates a new instance of WheelSpeedsMessage with randomized data.
     * @param time
     *      the time in which the object is created.
     */
    explicit WheelSpeedsMessage(std::chrono::high_resolution_clock::duration time);

};


#endif //CAN_MESSAGE_GENERATOR_WHEELSPEEDSMESSAGE_H
