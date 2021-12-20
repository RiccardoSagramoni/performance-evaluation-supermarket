#ifndef __SUPERMARKET_EXTERNALWORLD_H_
#define __SUPERMARKET_EXTERNALWORLD_H_

#include <omnetpp.h>
#include "CartMessage_m.h"

// Index of the Random Number Generators
#define ARRIVAL_RNG     0
#define SERVICE_RNG     1

using namespace omnetpp;

class ExternalWorld : public cSimpleModule
{
    // Enable/disable logging
    bool logging = false;

    // Distribution parameters
    double arrival_mean = 0;
    double service_mean = 0;
    double service_std_deviation = 0;

    int arrival_distribution = 0;
    int service_distribution = 0;

    // Messages
    cMessage* timer_ = nullptr;

    // Methods
    void generate_new_cart ();
    void wait_new_arrival ();

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
