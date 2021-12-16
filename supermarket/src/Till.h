#ifndef __SUPERMARKET_TILL_H_
#define __SUPERMARKET_TILL_H_

#include <omnetpp.h>
#include <queue>
#include <string>

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
    virtual void process_job(cMessage* job);
    virtual void print_EV(std::string str);
    virtual void response_time();
  public:
    int getNumberOfJobs();

};

#endif
