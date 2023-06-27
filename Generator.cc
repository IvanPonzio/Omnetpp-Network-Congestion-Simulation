#ifndef GENERATOR
#define GENERATOR

#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;


class Generator : public cSimpleModule {
private:
    cMessage *sendMsgEvent;
    cStdDev transmissionStats;
    cOutVector packetGenVector;

public:
    Generator();
    virtual ~Generator();
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};
Define_Module(Generator);

Generator::Generator() {
    sendMsgEvent = NULL;

}

Generator::~Generator() {
    cancelAndDelete(sendMsgEvent);
}

void Generator::initialize() {
    transmissionStats.setName("TotalTransmissions");
    // create the send packet
    sendMsgEvent = new cMessage("sendEvent");
    // schedule the first event at random time
    scheduleAt(par("generationInterval"), sendMsgEvent);
    packetGenVector.setName("packetGen");
    // convert packetByteSize from double to int
    //int packetByteSize = par("packetByteSize");

}


void Generator::finish() {
}
void Generator::handleMessage(cMessage *msg) {



        // create new packet
        cPacket *pkt = new cPacket("packet");
        packetGenVector.record(1);
        pkt->setByteLength(par("packetByteSize"));

        // Print packet name before sending
        EV_INFO << "Sending a data packet to TransportTx. Packet name: " << pkt->getName() << endl;

        // send to the output
        send(pkt, "out");

        // compute the new departure time
        simtime_t departureTime = simTime() + par("generationInterval");

        // Slow down generation if a FeedbackPkt packet is received
        if (msg->getKind() == 2) {
            //FeedbackPkt *feedbackPkt = dynamic_cast<FeedbackPkt*>(msg);
           // EV_INFO << "FeedbackPkt received. Packet name: " << feedbackPkt->getName() << ". Slowing down generation." << endl;
            departureTime = departureTime + 0.19;
            delete(msg);
        }

        // cancel the previous event if it is still scheduled
        if (sendMsgEvent->isScheduled()) {
            cancelEvent(sendMsgEvent);
        }
        // schedule the new packet generation
        scheduleAt(departureTime, sendMsgEvent);

}




#endif /* GENERATOR */
