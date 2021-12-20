#ifndef __SUPERMARKET_SWITCH_H_
#define __SUPERMARKET_SWITCH_H_

#include <omnetpp.h>
#include <vector>
#include <tgmath.h>
#include "Till.h"

using namespace omnetpp;


class Switch : public cSimpleModule {

    // Parameters for the till
    int number_of_tills = 0;
    double percentage_quick_tills = 0;
    int quick_checkout_threshold = 0;

    int num_quick_tills = 0;
    int num_std_tills = 0;
    
    // Enable/disable logging
    bool logging = false;

    // Pointers to the tills
    std::vector<Till*> quick_tills;
    std::vector<Till*> standard_tills;

    // Methods
    unsigned int selectTill(std::vector<Till*> vect);

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage* msg);
};

#endif
