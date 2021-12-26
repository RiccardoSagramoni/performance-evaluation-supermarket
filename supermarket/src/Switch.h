#ifndef __SUPERMARKET_SWITCH_H_
#define __SUPERMARKET_SWITCH_H_

#include <omnetpp.h>
#include <vector>
#include <tgmath.h>
#include "Till.h"
#include "CartMessage_m.h"

using namespace omnetpp;


class Switch : public cSimpleModule
{
    // Parameters for the till
    unsigned int number_of_tills = 0;
    double percentage_quick_tills = 0;
    unsigned int quick_checkout_threshold = 0;

    
    // Enable/disable logging
    bool logging = false;

    // Pointers to the tills
    std::vector<Till*> quick_tills;
    std::vector<Till*> standard_tills;

    // Methods
    unsigned int selectTill(const std::vector<Till*>& vect);

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage* msg);
};

#endif
