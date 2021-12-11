#ifndef __SUPERMARKET_EXTERNALWORLD_H_
#define __SUPERMARKET_EXTERNALWORLD_H_

#include <omnetpp.h>

using namespace omnetpp;

class ExternalWorld : public cSimpleModule
{
    // Distribution parameters
    const double arrival_mean = par("arrival_mean");
    const int service_distribution = par("service_distribution");
    const double service_mean = par("service_mean");
    const double service_std_deviation = par("service_std_deviation");

    // RNG
    const int ARRIVAL_RNG = 0;
    const int SERVICE_RNG = 1;

    // Messages
    cMessage* beep_;

    // Methods
    void generate_new_cart ();
    void wait_new_arrival ();

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
