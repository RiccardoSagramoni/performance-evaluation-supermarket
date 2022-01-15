#include "ExternalWorld.h"

Define_Module(ExternalWorld);

void ExternalWorld::initialize()
{
    // Initialize parameters
    logging = par("logging");
    arrival_mean = par("arrival_mean");
    service_mean = par("service_mean");
    service_std_deviation = par("service_std_deviation");
    arrival_distribution = par("arrival_distribution");
    service_distribution = par("service_distribution");

    if (arrival_mean < 0 || service_mean < 0 || service_std_deviation < 0) {
        error("initialize(): negative distribution parameters, expected positive values");
    }

    // Log current distribution
    if (logging) {
        if (arrival_distribution == 0) { // exponential
            EV << "EXTERNAL_WORLD: exponential interarrival distribution" << endl;
        }
        else { // constant
            EV << "EXTERNAL_WORLD: constant interarrival distribution" << endl;
        }

        if (service_distribution == 0) { // exponential
            EV << "EXTERNAL_WORLD: exponential service distribution" << endl;
        }
        else if (service_distribution == 1){ // lognormal
            EV << "EXTERNAL_WORLD: lognormal service distribution" << endl;
        }
        else { // constant
            EV << "EXTERNAL_WORLD: constant service distribution" << endl;
        }
    }

    timer_ = new cMessage("timer");

    // Wait for first arrival
    wait_new_arrival();
}

void ExternalWorld::handleMessage(cMessage *msg)
{
    generate_new_cart();
    wait_new_arrival();
}

void ExternalWorld::generate_new_cart ()
{
    // Extract from the chosen distribution how much time
    // it will take to serve the new cart
    simtime_t service_time;

    if (service_distribution == 0) { // exponential
        service_time = exponential(service_mean, SERVICE_RNG);
    }
    else if (service_distribution == 1){ // lognormal
        service_time = lognormal(service_mean, service_std_deviation, SERVICE_RNG);
    }
    else { // constant
        service_time = service_mean;
    }

    // Send the new cart to the supermarket module,
    // as a message containing the service time
    CartMessage* msg = new CartMessage();
    msg->setService_time(service_time);
    send(msg, "out");

    if (logging) {
        EV << "EXTERNAL_WORLD: generated new cart (" << service_time << ")" << endl;
    }
}

void ExternalWorld::wait_new_arrival ()
{
    // Wait for a random time, extracted from an exponential distribution
    simtime_t arrival_time;
    if (arrival_distribution == 0) { // exponential
        arrival_time = exponential(arrival_mean, ARRIVAL_RNG);
    }
    else { // constant
        arrival_time = arrival_mean;
    }

    scheduleAt(simTime() + arrival_time, timer_);

    if(logging) {
        EV << "EXTERNAL_WORLD: next cart arrival in " << arrival_time << endl;
    }
}

/**
 * Overrides parent's finish method,
 * in order to deallocate dynamic memory before recording statistics
 */
void ExternalWorld::finish()
{
    if (this == timer_->getOwner()) {
        EV << "Delete timer_" << endl;
        delete timer_;
    }

    cSimpleModule::finish();
}











