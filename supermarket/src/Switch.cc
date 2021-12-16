#include "Switch.h"

Define_Module(Switch);

void Switch::initialize(){

    cModule *supermarket = getParentModule();
    for(int i = 0; i<num_std_tills; i++){
        cModule *standard_till = module->getSubmodule("standard_tills", i);
        standard_tills.push_back((Till*)standard_till);
    }
    for(int i = 0; i<num_quick_tills; i++){
        cModule *quick_till = module->getSubmodule("quick_tills", i);
        quick_tills.push_back((Till*)quick_till);
    }

}

void Switch::handleMessage(cMessage *msg){

    int index = 0;
    // extracting the service time of the cart
    simtime_t *service_time = SimTime::parse(msg->getName());

    if(loggig) {
        EV << "SWITCH: new cart arrived" << service_time << endl;
    }

    // creation of the message to send to the right till
    cMessage* msg = new cMessage(SIMTIME_STR(service_time));

    // select of the right till, using the threshold as parameter
    if(service_time < quick_checkout_threshold ){

        index = selectTill(quick_tills);
    }
    else{

        index = selectTill(standard_tills);
    }

    if(console_log) {
       EV << "SWITCH: selected the till with lowest response time" << endl;
    }

    // sending the message on the right till
    send(msg, "out", index);

    if(console_log) {
        EV << "SWITCH: sent the cart to the till" << endl;
    }
}

int Switch::selectTill(vector<Till*> vect){

    int index = 0;

    for(int i = 0; i < vect.size()-1; i++){

        if(vect[i+1]->get_number_of_job() < vect[i]->get_number_of_job()){
            index = i+1;
        }
    }

    return index;
}



