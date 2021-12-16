#ifndef __SUPERMARKET_EXTERNALWORLD_H_
#define __SUPERMARKET_EXTERNALWORLD_H_

#include <omnetpp.h>

// Index of the Random Number Generators
#define ARRIVAL_RNG     0
#define SERVICE_RNG     1

using namespace omnetpp;

class ExternalWorld : public cSimpleModule
{
    // Enable/disable logging
    const bool logging = par("logging");

    // Distribution parameters
    const double arrival_mean = par("arrival_mean");
    const double service_mean = par("service_mean");
    const double service_std_deviation = par("service_std_deviation");

    const int arrival_distribution = par("arrival_distribution");
    const int service_distribution = par("service_distribution");

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
