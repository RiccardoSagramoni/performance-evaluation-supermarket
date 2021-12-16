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
        if(!queue.empty()){         //queue is not empty, I serve the next job
            process_job(nullptr);
        }
        else{                       //queue is empty, Till is no longer serving
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
        start_time_queue.push(simTime());
    }
}

//return the total number of job in the till
int Till::get_number_of_jobs(){
    return queue.size() + under_service;
}

/*
 * Process a job scheduling its service time:
 * -If the job is specified by argument it means that the queue is empty and we are serving an arrival job.
 * -If the job is NULL it means that it must be extracted from the queue.
*/
void Till::process_job(cMessage* job){
    if (job == nullptr){
        job = (cMessage*)this->queue.front();
        queue.pop();
    }
    under_service = true; //the system is now serving a job
    try{
        scheduleAt(simTime()+SimTime::parse(job->getName()), timer_);
    }catch(...){
        if(par("logging")){
            EV << "Parse Error, code must be checked";
        }
    }
    delete(job);
}

//print a generic event for the till
void Till::print_EV(std::string str){
    if(par("is_quick")){
            EV << "Quick Till["<<this->getId()<<"]: "<<str<<endl;
    }
    else{
            EV << "Standard Till["<<this->getId()<<"]: "<<str<<endl;
    }

}

//Calculate the response time for the served job
void Till::response_time(){
    simtime_t time = start_time_queue.front();
    start_time_queue.pop();
    emit(responseTimeSignal, (simtime_t)(simTime()-time));
}
