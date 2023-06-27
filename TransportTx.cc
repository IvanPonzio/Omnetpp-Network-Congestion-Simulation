#ifndef TRANSPORTTX
#define TRANSPORTTX

#include <string.h>
#include <omnetpp.h>
#include "FeedbackPkt.h"

using namespace omnetpp;

class TransportTx : public cSimpleModule {
private:
    cQueue buffer;
    cMessage *endServiceEvent;
    simtime_t serviceTime;
    cOutVector bufferSizeVector;
    cOutVector packetDropVector;
    int congestionWindow;
    int ssthresh;

public:
    TransportTx();
    virtual ~TransportTx();

protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
    void handleCongestionFeedback(int remainingBuffer);
};

Define_Module(TransportTx);

TransportTx::TransportTx() {
    endServiceEvent = nullptr;
}

TransportTx::~TransportTx() {
    cancelAndDelete(endServiceEvent);
}

void TransportTx::initialize() {
    buffer.setName("buffer");
    //int packetByteSize;
   // packetByteSize = par("gen.packetByteSize");
    endServiceEvent = new cMessage("endService");
    bufferSizeVector.setName("bufferVector");
    packetDropVector.setName("packetDoped");
    congestionWindow = 1;  // Set initial congestion window size
    ssthresh = 10;        // Set initial ssthresh value
}

void TransportTx::finish() {}

void TransportTx::handleMessage(cMessage *msg) {
    if (msg == endServiceEvent) {
        // if packet in buffer, send next one
        if (!buffer.isEmpty()) {
            // dequeue packet
            cPacket *pkt = (cPacket*)buffer.pop();
            // send packet
            send(pkt, "toOut$o");
            // start new service
            serviceTime = pkt->getDuration();
            scheduleAt(simTime() + serviceTime, endServiceEvent);
            EV_INFO << "Packet sent: " << pkt->getName() << endl;
        }
    } else if (msg->getKind() == 2) {
        FeedbackPkt *feedbackPkt = (FeedbackPkt*)msg;
        int remainingBuffer = feedbackPkt->getRemainingBuffer();
        handleCongestionFeedback(remainingBuffer);

        delete msg;
        EV_INFO << "Received FeedbackPkt. Remaining buffer: " << remainingBuffer << endl;
    } else if (msg->getKind() == 0) {
        // if msg is a data packet
        // check buffer limit
        if (buffer.getLength() >= (unsigned long int)par("bufferSize")) {
            // drop the packet
            delete msg;
            this->bubble("packet dropped");
            packetDropVector.record(1);
            EV_INFO << "Packet dropped: Buffer is full" << endl;
        } else {
            // enqueue the packet
            buffer.insert(msg);
            bufferSizeVector.record(buffer.getLength());
            // if the server is idle
            if (!endServiceEvent->isScheduled()) {
                // start the service
                scheduleAt(simTime(), endServiceEvent);
            }
        }
    } else {
        // Unknown message type, handle it accordingly
        delete msg;
        EV_WARN << "Unknown message received" << endl;
    }
    int packetByteSize = 12500; // Asigna el valor deseado para el tamaño del paquete
       // Resto del código...
       int bytesSent = congestionWindow * packetByteSize;



    double sendingRate = bytesSent / serviceTime.dbl(); // Calculate the sending rate in bytes per second

    EV_INFO << "Buffer size: " << buffer.getLength() << endl;
    EV_INFO << "Congestion Window: " << congestionWindow << endl;
    EV_INFO << "Buffer size: " << buffer.getLength() << endl;
    EV_INFO << "Congestion Window: " << congestionWindow << endl;

    if (bytesSent > 0) {
        EV_INFO << "Bytes sent: " << bytesSent << endl;
        EV_INFO << "Sending rate: " << sendingRate << " B/s" << endl;
    }
}

void TransportTx::handleCongestionFeedback(int remainingBuffer) {
    if (remainingBuffer <= 10) {
        congestionWindow = 1;
        FeedbackPkt *feedbackPkt = new FeedbackPkt("FeedbackPacket");
        feedbackPkt->setRemainingBuffer(remainingBuffer);
        feedbackPkt->setKind(2);  // Configurar el campo kind como 2
        send(feedbackPkt, "outInstructions");

    } else if (congestionWindow < ssthresh) {
        // Slow Start
        congestionWindow += 1;
    } else {
        // Congestion Avoidance
        congestionWindow += 1.0 / congestionWindow;
    }
    EV_INFO << "Congestion Window: " << congestionWindow << endl;
}

#endif /* TRANSPORTTX */

