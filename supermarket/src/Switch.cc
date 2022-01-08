#include "Switch.h"


Define_Module(Switch);

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
       error("initialize(): no till allocated");
    }

    if (percentage_quick_tills < 0 || percentage_quick_tills > 1) {
        error("initialize(): percentage of quick tills out of range [0,1]");
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

/**
 * Handle a message received from the external world.
 * A message represent a shopping cart, with an associated service time.
 * Depending on the service time and on the policy adopted for the tills
 * (undistinguished or quick-checkout), a cart could be send to a standard
 * till or to a quick till.
 * In the context of "quick-checkout" tills, cart with a service time greater than
 * the threshold are called "standard carts" and cart with a lower service time
 * are called "quick carts".
 *
 * @param msg the received message to handle
 */
void Switch::handleMessage(cMessage* msg)
{
    CartMessage* cart = check_and_cast< CartMessage*>(msg);
    // Extract the service time of the cart
    simtime_t service_time = cart->getService_time();

    if(logging) {
        EV << "SWITCH: new cart arrived (" << service_time << ")" << endl;
    }

    // Select of the right till, using the threshold parameter
    if (!quick_tills.empty() && service_time <= quick_checkout_threshold) { 
        // Quick tills
        handle_quick_cart(msg);
    }
    else if (!standard_tills.empty()) { 
        // Standard tills
            handle_standard_cart(msg);
    }
    else if (service_time > quick_checkout_threshold) {
        // Only quick tills and we received a standard cart
        if (logging) EV << "SWITCH: cart dropped" << endl;
        delete msg;
    }
    else {
        // Error: no tills 
        error("SWITCH: no till allocated");
    }
}

/**
 * Handle a cart with response time greater than the threshold
 * (i.e. a standard cart)
 * Standard cart can be sent ONLY to standard tills
 *
 * @param msg received message to handle
 */
void Switch::handle_standard_cart (cMessage* msg)
{
    if (logging) {
        EV << "SWITCH: select standard till..." << endl;
    }

    // Select index of the till with lowest number of job
    unsigned int index = select_till_for_standard_cart();


    // Send message
    send(msg, "standard_out", index);
    if (logging) {
        EV << "SWITCH: send the cart to the STANDARD till n." << index << endl;
    }
}

/**
 * Handle a cart with response time smaller than the threshold
 * (i.e. a quick cart)
 * Quick cart scan be sent both to standard and quick tills
 *
 * @param msg received message to handle
 */
void Switch::handle_quick_cart (cMessage* msg)
{
    // Select index of the till with lowest number of job
    if (logging) {
        EV << "SWITCH: select till for quick cart..." << endl;
    }

    bool is_quick_till;
    unsigned int index = select_till_for_quick_cart(is_quick_till);

    // Send message
    if (is_quick_till) {
        send(msg, "quick_out", index);
        if (logging) {
            EV << "SWITCH: send the cart to the QUICK till n." << index << endl;
        }
    }
    else {
        send(msg, "standard_out", index);
        if (logging) {
            EV << "SWITCH: send the cart to the STANDARD till n." << index << endl;
        }
    }
}

/**
 * Select the till where to send a "standard" cart
 * (i.e. service time greater than the threshold).
 *
 * Depending on configuration parameter "optimized_routing", the switch could choose:
 * - The till with the shortest number of jobs
 * - A random till
 *
 * @return the index of the chosen till
 */
unsigned int Switch::select_till_for_standard_cart ()
{
    if (standard_tills.empty()) {
        error("selectTill(): vect can't be empty");
    }

    if (par("optimized_routing")) {
        EV << "SWITCH: Select BEST standard till" << endl;

        // Find the best till between the standard ones
        unsigned int value_best_standard_till = 0;
        unsigned int index = find_till_with_min_number_of_jobs(standard_tills, value_best_standard_till);

        if(logging) {
            EV << "SWITCH: selected STANDARD till " << index << endl;
        }

        return index;
    }
    else {
        if (logging) {
            EV << "SWITCH: Select RANDOM till" << endl;
        }

        return floor(uniform(0, standard_tills.size()));
    }
}

/**
 * Select the till where to send a "quick" cart
 * (i.e. service time smaller than the threshold).
 *
 * Depending on configuration parameter "optimized_routing", the switch could choose:
 * - The till with the shortest number of jobs;
 * - A random till.
 *
 * @param is_quick_till it's set true if the selected till is a quick one, false otherwise.
 *
 * @return the index of the chosen till
 */
unsigned int Switch::select_till_for_quick_cart (bool& is_quick_till)
{
    if (standard_tills.empty() && quick_tills.empty()) {
        error("selectTill(): tills can't be 0 for both types of tills");
    }

    if (par("optimized_routing")) {
        // Find the best till between the standard ones
        if (logging) {
            EV << "SWITCH: standard tills status" << endl;
        }
        unsigned int value_best_standard_till = 0;
        unsigned int index_best_standard_till = 0;

        try {
            index_best_standard_till =
                    find_till_with_min_number_of_jobs(standard_tills, value_best_standard_till);
            if (logging) EV << "SWITCH: best standard till is n." << index_best_standard_till << endl;
        }
        catch (const std::invalid_argument& ex) {
            if (logging) EV << "SWITCH: no standard till allocated" << endl;
            value_best_standard_till = std::numeric_limits<unsigned int>::max();
        }



        // Find the best till between the quick ones
        if (logging) {
            EV << "SWITCH: quick tills status" << endl;
        }
        unsigned int value_best_quick_till = 0;
        unsigned int index_best_quick_till = 0;

        try {
            index_best_quick_till =
                find_till_with_min_number_of_jobs(quick_tills, value_best_quick_till);
            if (logging) EV << "SWITCH: best quick till is n." << index_best_quick_till << endl;
        }
        catch (const std::invalid_argument& ex) {
            if (logging) EV << "SWITCH: no quick till allocated" << endl;
            value_best_quick_till = std::numeric_limits<unsigned int>::max();
        }

        // Choose the best result overall
        is_quick_till = (value_best_quick_till <= value_best_standard_till);
        unsigned int selected_index =
                ( is_quick_till ? index_best_quick_till : index_best_standard_till );

        if(logging) {
            EV << "Select till for a quick cart: till type ";
            if (is_quick_till) {
                EV << "quick";
            }
            else {
                EV << "standard";
            }
            EV << ", index " << selected_index << endl;
        }

        return selected_index;
    }
    else {
        if (logging) {
            EV << "SWITCH: Select RANDOM till" << endl;
        }

        // Choose one till randomly, whichever its type
        unsigned int index = floor(uniform(0, standard_tills.size() + quick_tills.size()));
        if (index >= standard_tills.size()) {
            is_quick_till = true;
            return index - standard_tills.size();
        }
        else {
            is_quick_till = false;
            return index;
        }
    }
}

/**
 * Given a non-empty vector of tills, find the one with the minimum number of jobs.
 *
 * @param vect vector of tills
 * @param value return the number of jobs of the selected till
 * 
 * @throws std::invalid_argument if vect is empty
 *
 * @return the index of the selected till
 */
unsigned int Switch::find_till_with_min_number_of_jobs (const std::vector<Till*>& vect, unsigned int& value)
{
    if (vect.empty()) {
        throw std::invalid_argument("Vector is empty");
    }

    unsigned int min_jobs = vect[0]->get_number_of_jobs();
    unsigned int min_jobs_index = 0;

    if (logging) {
        EV << 0 << ": " << min_jobs << endl;
    }

    // Find the best till
    for(unsigned int i = 1; i < vect.size(); i++){
        // compare each element with the next one
        unsigned int this_jobs = vect[i]->get_number_of_jobs();

        if(this_jobs < min_jobs){
            min_jobs_index = i;
            min_jobs = this_jobs;

        }
        if (logging) {
            EV << i << ": " << this_jobs << endl;
        }
    }

    // Return results
    value = min_jobs;
    return min_jobs_index;
}

