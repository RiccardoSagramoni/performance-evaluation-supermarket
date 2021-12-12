#include "ExternalWorld.h"

Define_Module(ExternalWorld);

void ExternalWorld::initialize()
{
    beep_ = new cMessage("timer");

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
    cMessage* msg = new cMessage(SIMTIME_STR(service_time));
    send(msg, "out");

    if (logging) {
        EV << "EXTERNAL_WORLD: generated new cart (" << service_time << ")" << endl;
    }
}

void ExternalWorld::wait_new_arrival ()
{
    // Wait for a random time, extracted from an exponential distribution
    simtime_t arrival_time = exponential(arrival_mean, ARRIVAL_RNG);
    scheduleAt(simTime() + arrival_time, beep_);

    if(logging) {
        EV << "EXTERNAL_WORLD: next cart arrival in " << arrival_time << endl;
    }
}












