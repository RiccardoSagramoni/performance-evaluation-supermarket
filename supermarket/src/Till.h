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

    cMessage* timer_ = nullptr;

    // Signals
    simsignal_t number_of_jobs_signal = 0;
    simsignal_t number_of_jobs_queue_signal = 0;
    simsignal_t response_time_signal = 0;
    simsignal_t waiting_time_signal = 0;

    // Methods
    void process_job();
    void print_EV(std::string str);
    void complete_job();

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

public:
    unsigned int get_number_of_jobs();

};

#endif
