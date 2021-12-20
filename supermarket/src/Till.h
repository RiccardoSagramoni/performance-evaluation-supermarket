#ifndef __SUPERMARKET_TILL_H_
#define __SUPERMARKET_TILL_H_

#include <omnetpp.h>
#include <queue>
#include <string>

using namespace omnetpp;

class Till : public cSimpleModule
{
    std::queue <cMessage*> queue;
    std::queue <simtime_t> start_time_queue; //indicates the
    bool under_service; //indicates if the till is currently serving a job
    cMessage* timer_;
    simsignal_t responseTimeSignal;

    // Methods
    void process_job(cMessage* job);
    void print_EV(std::string str);
    void response_time();

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

public:
    int get_number_of_jobs();

};

#endif
