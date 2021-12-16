#include "Switch.h"

Define_Module(Switch);

void Switch::initialize() {

    // accessing supermarket, that is the parent module
    cModule* supermarket = getParentModule();

    // taking the module pointer of each till
    // and put it in the right vector
    for(int i = 0; i < num_std_tills; i++){
        cModule* standard_till = module->getSubmodule("standard_tills", i);
        standard_tills.push_back((Till*)standard_till);
    }

    for(int i = 0; i < num_quick_tills; i++){
        cModule* quick_till = module->getSubmodule("quick_tills", i);
        quick_tills.push_back((Till*)quick_till);
    }

}

void Switch::handleMessage(cMessage* msg) {

    // extract the service time of the cart
    simtime_t service_time = SimTime::parse(msg->getName());

    if(logging) {
        EV << "SWITCH: new cart arrived" << service_time << endl;
    }

    // Select of the right till, using the threshold as parameter

    if (service_time < quick_checkout_threshold) { // Quick tills
        // Select index of the till with lowest number of job
        unsigned int index = selectTill(quick_tills);
        if(logging) {
            EV << "SWITCH: selected the QUICK till with lowest response time: " << index << endl;
        }

        // Send message
        send(msg, "quick_out", index);
        if (logging) {
            EV << "SWITCH: send the cart to the QUICK till n." << index << endl;
        }
    }
    else { // Standard tills
        // Select index of the till with lowest number of job
        unsigned int index = selectTill(standard_tills);
        if(logging) {
            EV << "SWITCH: selected the STANDARD till with lowest response time: " << index << endl;
        }

        // Send message
        send(msg, "standard_out", index);
        if (logging) {
            EV << "SWITCH: send the cart to the STANDARD till n." << index << endl;
        }
    }
}

/**
 * Select the till with the lowest number of job
 *
 * @vect vector of the tills
 * @return the index of the till in the vector with the lowest number of job
 */
unsigned int Switch::selectTill(vector<Till*> vect){
    
    if (vect.empty()) {
        throw "Error: vect can't be empty";
    }

    unsigned int min_job = vect[0]->get_number_of_job();
    unsigned int min_job_index = 0;

    for(int i = 1; i < vect.size() - 1; i++){
        // compare each element with the next one
        if(vect[i]->get_number_of_job() < min_job){
            min_job_index = i;
            min_job = vect[i]->get_number_of_job();
        }
    }

    return min_job_index;
}



