#ifndef TRANSPORTTx_H
#define TRANSPORTTx_H

#include <omnetpp.h>
#include "FeedbackPkt.h"


using namespace omnetpp;

class TransportTx : public cSimpleModule {
private:
    cOutVector bufferSizeSend;
    cQueue buffer;
    void scheduleNextPacketTransmission();
    cOutVector packetDropVector;

public:
    TransportTx();
    virtual ~TransportTx();
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif /* TRANSPORTSENDER_H */
