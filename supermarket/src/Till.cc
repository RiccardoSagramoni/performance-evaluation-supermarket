#include "Till.h"

Define_Module(Till);

unsigned int Till::counter_id_standard = 0;
unsigned int Till::counter_id_quick = 0;

void Till::initialize()
{
    timer_ = new cMessage("beep");
    responseTimeSignal = registerSignal("responseTime");

    if(par("is_quick")){
        id = counter_id_quick++;
    }
    else{
        id = counter_id_standard++;
    }
}

void Till::handleMessage(cMessage *msg)
{
    //service time ends
    if (msg->isSelfMessage()) {
        record_response_time();

        std::string log = "Job has been served. Remaining jobs: " + std::to_string(queue.size());
        print_EV(log);

        if(!queue.empty()){         //queue is not empty, I serve the next job
            process_job();
        }
    }
    //new cart arrival
    else {
        Cart* new_cart = new Cart{msg, simTime()};

        queue.push(new_cart);

        if(queue.size() == 1){
            process_job();
        }
    }
}

//return the total number of job in the till
unsigned int Till::get_number_of_jobs(){
    return queue.size();
}

/**
 * Process a job (cart). It reads its service time from the queue and 
 * schedules a timer according to the cart's service time
 */
void Till::process_job (){
    Cart* cart = queue.front();
    CartMessage* msg = check_and_cast<CartMessage*>(cart->message);
    scheduleAt(simTime() + msg->getService_time(), timer_);
}

// print a generic event for the till
void Till::print_EV(std::string str){
    if (par("logging")) {
        if(par("is_quick")){
            EV << "Quick Till[" << id << "]: " << str <<endl;
        }
        else{
            EV << "Standard Till[" << id << "]: " << str <<endl;
        }
    }
}

//Calculate the response time for the served job
void Till::record_response_time()
{
    Cart* cart = queue.front();
    queue.pop();
    emit(responseTimeSignal, simTime() - cart->enter_queue_time);
    delete cart;
}




