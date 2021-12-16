#ifndef __SUPERMARKET_SWITCH_H_
#define __SUPERMARKET_SWITCH_H_

#include <omnetpp.h>
#include <vector>
#include <tgmath.h>

using namespace omnetpp;


class Switch : public cSimpleModule{


    const int percentage_quick_tills = par("percentage_quick_tills");
    const int quick_checkout_threshold = par("quick_checkout_threshold");
    const int number_of_tills = par("number_of_tills");
    const bool logging = par("logging");


    int num_quick_tills = floor(number_of_tills * percentage_quick_tills);
    int num_std_tills = number_of_tills - num_quick_tills;

    vector<Till*> quick_tills;
    vector<Till*> standard_tills;

    int selectTill(vector<Till*> vect);

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
};

#endif
