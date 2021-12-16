#include "Till.h"

Define_Module(Till);

void Till::initialize()
{
    under_service = false;
    timer_=new cMessage("beep");
    responseTimeSignal=registerSignal("responseTime");
}

void Till::handleMessage(cMessage *msg)
{
    //service time ends
    if(msg->isSelfMessage()){
        response_time();
        if(!queue.empty()){
            process_job(nullptr);
        }
        else{
            under_service = false;
        }
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

        //save the arrival time for this cart
        responseT_queue.push(simTime().dbl());
    }
}

int Till::getNumberOfJobs(){
    return queue.size() + under_service;
}

void Till::process_job(cMessage* job){
    if (job == nullptr){
        job = (cMessage*)this->queue.front();
        queue.pop();
    }
    under_service = true;
    scheduleAt(simTime()+SimTime::parse(job->getName()), timer_);
    delete(job);
}

void Till::print_EV(std::string str){
    if(par("is_quick")){
            EV << "Quick Till["<<this->getId()<<"]: "<<str<<endl;
    }
    else{
            EV << "Standard Till["<<this->getId()<<"]: "<<str<<endl;
    }

}

void Till::response_time(){
    double time=(double)responseT_queue.front();
    responseT_queue.pop();
    emit(responseTimeSignal, (simtime_t)(simTime()-time));
}
