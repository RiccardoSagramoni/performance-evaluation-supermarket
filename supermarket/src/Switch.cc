#include "Switch.h"

Define_Module(Switch);

void Switch::initialize(){

    beep_ = new cMessage("timer");
}

void Switch::handleMessage(cMessage *msg){

    // timeout? if we put it we should use a backlog?
    cMessage *msg = receive();

    if (msg==nullptr){

        //handle error?
    }
    else if(msg->isSelfMessage()){

        // togli una quantità equivalente di service time a quell'index
    }
    else{
        if (dynamic_cast<simtime_t *>(msg) != nullptr){
            simtime_t *service_time = (simtime_t *)msg;

            if(console_log) {
                EV << "SWITCH: new cart arrived" << service_time << endl;
            }

            receive_new_cart(service_time);
        }
    }
}


void Switch::cart_routing(simtime_t service_time){

    int dimension = 0;
    int index = 0;
    int selected_till_index = 0;

    if(service_time < percentage_quick_tills){

        dimension = this->num_quick_tills;
        index = this->index_quick;
    }
    else{
        dimension = this->num_standard_tills;
        index = 0;
    }


    if(console_log) {
        EV << "SWITCH: selecting the quick till with lowest response time" << endl;
    }

    selected_till_index = getIndexTill(dimension,index);
    this->tills[selected_till_index] += service_time;

    scheduleAt(simTime() + service_time, beep_);

    cMessage* msg = new cMessage(SIMTIME_STR(service_time));
    send(msg, "out[selected_till_index]");

    if (console_log) {
        EV << "SWITCH: cart (" << service_time << ") has been routed" << endl;
    }

}

int Switch::getIndexTill(int dimension, int index){

    int min_index_responsetime_till= 0;

    for(int i=index; i< dimension-1; i++){
        if(this->tills[i+1] < this->tills[i]){
            min_index_responsetime_till = i+1;
        }
    }

    return min_index_responsetime_till;
}



