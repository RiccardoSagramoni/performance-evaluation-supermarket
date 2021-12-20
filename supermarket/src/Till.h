#ifndef __SUPERMARKET_TILL_H_
#define __SUPERMARKET_TILL_H_

#include <omnetpp.h>
#include <queue>
#include <string>
#include "CartMessage_m.h"

using namespace omnetpp;

struct Cart {
    cMessage* message;
    simtime_t enter_queue_time;
};

class Till : public cSimpleModule
{
    static unsigned int counter_id_quick;
    static unsigned int counter_id_standard;
    unsigned int id = 0;

    std::queue <Cart*> queue;

    cMessage* timer_;
    simsignal_t responseTimeSignal;

    // Methods
    void process_job();
    void print_EV(std::string str);
    void record_response_time();

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

public:
    unsigned int get_number_of_jobs();

};

#endif
