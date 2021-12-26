#include "Switch.h"


Define_Module(Switch);

//counter to select tills

void Switch::initialize()
{
    // Initialize parameters
    number_of_tills = par("number_of_tills");
    percentage_quick_tills = par("percentage_quick_tills");
    quick_checkout_threshold = par("quick_checkout_threshold");
    logging = par("logging");

    unsigned int num_quick_tills = floor(number_of_tills * percentage_quick_tills);
    unsigned int num_std_tills = number_of_tills - num_quick_tills;

    if (number_of_tills <= 0 || num_quick_tills + num_std_tills != number_of_tills) {
       error("initialize(): Tills doesn't exists");
    }

    if (percentage_quick_tills < 0 || percentage_quick_tills > 1) {
        error("initialize(): percentage quick tills not valid");
    }


    // accessing supermarket, that is the parent module
    cModule* supermarket = getParentModule();

    // taking the module pointer of each till
    // and put it in the right vector
    for(int i = 0; i < num_std_tills; i++){
        cModule* standard_till = supermarket->getSubmodule("standard_tills", i);
        standard_tills.push_back(check_and_cast<Till*>(standard_till));
    }

    for(int i = 0; i < num_quick_tills; i++){
        cModule* quick_till = supermarket->getSubmodule("quick_tills", i);
        quick_tills.push_back(check_and_cast<Till*>(quick_till));
    }
}

void Switch::handleMessage(cMessage* msg)
{
    CartMessage* cart = check_and_cast< CartMessage*>(msg);
    // Extract the service time of the cart
    simtime_t service_time = cart->getService_time();

    if(logging) {
        EV << "SWITCH: new cart arrived (" << service_time << ")" << endl;
    }

    // Select of the right till, using the threshold parameter
    if (standard_tills.empty() ||
        (!quick_tills.empty() && service_time < quick_checkout_threshold))
    { // Quick tills

        // Select index of the till with lowest number of job
        if (logging) {
            EV << "SWITCH: select quick till..." << endl;
        }

        unsigned int index = selectTill(quick_tills);
        if(logging) {
            EV << "SWITCH: selected QUICK till " << index << endl;
        }

        // Send message
        send(msg, "quick_out", index);
        if (logging) {
            EV << "SWITCH: send the cart to the QUICK till n." << index << endl;
        }
    }
    else if (!standard_tills.empty()) { // Standard tills
        if (logging) {
            EV << "SWITCH: select standard till..." << endl;
        }

        // Select index of the till with lowest number of job
        unsigned int index = selectTill(standard_tills);
        if(logging) {
            EV << "SWITCH: selected STANDARD till " << index << endl;
        }

        // Send message
        send(msg, "standard_out", index);
        if (logging) {
            EV << "SWITCH: send the cart to the STANDARD till n." << index << endl;
        }
    }
    else {
        error("handleMessage(): no tills allocated");
    }
}

/**
 * Select the till with the lowest number of job
 *
 * @vect vector of the tills
 * @return the index of the till in the vector with the lowest number of job
 */
unsigned int Switch::selectTill(const std::vector<Till*>& vect)
{
    if (vect.empty()) {
        error("selectTill(): vect can't be empty");
    }

    if (par("optimized_routing")) {
        unsigned int min_job = vect[0]->get_number_of_jobs();
        unsigned int min_job_index = 0;

        if (logging) {
            EV << "SWITCH: Select BEST till" << endl;
            EV << 0 << ": " << vect[0]->get_number_of_jobs()<<endl;
        }

        for(int i = 1; i < vect.size() ; i++){
            // compare each element with the next one
            if(vect[i]->get_number_of_jobs() < min_job){
                min_job_index = i;
                min_job = vect[i]->get_number_of_jobs();

            }
            if (logging) {
                EV << i << ": " << vect[i]->get_number_of_jobs() <<endl;
            }
        }

        return min_job_index;
    }
    else {
        if (logging) {
            EV << "SWITCH: Select RANDOM till" << endl;
        }
        return floor(uniform(0, vect.size()));
    }
}



