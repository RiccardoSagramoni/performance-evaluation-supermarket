//
// Generated file, do not edit! Created by nedtool 5.7 from CartMessage.msg.
//

#ifndef __CARTMESSAGE_M_H
#define __CARTMESSAGE_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0507
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>CartMessage.msg:2</tt> by nedtool.
 * <pre>
 * message CartMessage
 * {
 *     simtime_t service_time;
 * }
 * </pre>
 */
class CartMessage : public ::omnetpp::cMessage
{
  protected:
    ::omnetpp::simtime_t service_time;

  private:
    void copy(const CartMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const CartMessage&);

  public:
    CartMessage(const char *name=nullptr, short kind=0);
    CartMessage(const CartMessage& other);
    virtual ~CartMessage();
    CartMessage& operator=(const CartMessage& other);
    virtual CartMessage *dup() const override {return new CartMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual ::omnetpp::simtime_t getService_time() const;
    virtual void setService_time(::omnetpp::simtime_t service_time);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const CartMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, CartMessage& obj) {obj.parsimUnpack(b);}


#endif // ifndef __CARTMESSAGE_M_H

