#ifndef __SUPERMARKET_SWITCH_H_
#define __SUPERMARKET_SWITCH_H_

#include <exception>
#include <limits>
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
    void handle_standard_cart (cMessage* msg);
    void handle_quick_cart (cMessage* msg);
    unsigned int select_till_for_standard_cart ();
    unsigned int select_till_for_quick_cart (bool& is_quick_till);
    unsigned int find_till_with_min_number_of_jobs (const std::vector<Till*>& vect, unsigned int& value);

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage* msg);
};

#endif
