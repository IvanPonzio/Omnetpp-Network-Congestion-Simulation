#ifndef TRANSPORTRX_H
#define TRANSPORTRX_H

#include <omnetpp.h>
#include "FeedbackPkt.h"

using namespace omnetpp;

class TransportRx : public cSimpleModule {
private:
    cStdDev bufferSizeStdRec;
    cOutVector bufferSizeRec;
    cOutVector packetDropVector;
    cQueue buffer;

public:
    TransportRx();
    virtual ~TransportRx();
protected:
    virtual void initialize() override;
    virtual void finish() override;
    virtual void handleMessage(cMessage *msg) override;
    void scheduleNextPacketTransmission();
};

#endif /* TRANSPORTRX_H */
