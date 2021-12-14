#include "Till.h"
#include <queue>

Define_Module(Till);

void Till::initialize()
{
    under_service = false;
    timer_=new cMessage("beep");
}

void Till::handleMessage(cMessage *msg)
{
    //service time ends
    if(msg->isSelfMessage()){
        print_EV("a job has been processed");
        if(!queue.empty())
            process_job(NULL);
        else
            under_service = false;
    }

    //new cart arrival
    else{

        //empty queue
        if(queue.empty()){
            process_job(msg);
        }

        //non-empty queue
        else{
            queue.push(msg);
        }
    }
}

int Till::getNumberOfJobs(){
    return queue.size() + under_service;
}

void Till::process_job(cMessage* job){
    if (job == NULL){
        job = (cMessage*)this->queue.front();
        queue.pop();
    }
    under_service = true;
    scheduleAt(simTime()+SimTime::parse(job->getClassName()), timer_);
    delete(job);
}

void Till::print_EV(const char* str){
    if(par("isQuick"))
            EV << "Quick Till["<<this->getId()<<"]: "<<str;

}
