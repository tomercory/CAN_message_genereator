//
// Created by tomer on 08/07/2022.
//

#ifndef CAN_MESSAGE_GENERATOR_BRAKEMODULEMESSAGE_H
#define CAN_MESSAGE_GENERATOR_BRAKEMODULEMESSAGE_H

#include "Message.h"


class BrakeModuleMessage : public Message
{
public:
    /**
     * creates a new instance of BrakeModuleMessage with randomized data.
     * @param time
     *      the time in which the object is created.
     */
    explicit BrakeModuleMessage(std::chrono::high_resolution_clock::duration time);

};



#endif //CAN_MESSAGE_GENERATOR_BRAKEMODULEMESSAGE_H
