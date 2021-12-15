#ifndef __SUPERMARKET_TILL_H_
#define __SUPERMARKET_TILL_H_

#include <omnetpp.h>
#include <queue>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Till : public cSimpleModule
{
  std::queue <cMessage*> queue;
  std::queue <double> responseT_queue;
  bool under_service;
  cMessage* timer_;
  simsignal_t responseTimeSignal;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual int getNumberOfJobs();
    virtual void process_job(cMessage* job);
    virtual void print_EV(const char* str);
    virtual void response_time();
};

#endif
