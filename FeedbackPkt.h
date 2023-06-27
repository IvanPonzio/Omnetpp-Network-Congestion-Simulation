#ifndef FEEDBACKPKT_H
#define FEEDBACKPKT_H

#include <omnetpp.h>

using namespace omnetpp;

#define FEEDBACK_PKT 101
#define CONTROL_PKT 102

class FeedbackPkt : public cPacket {
private:
    int remainingBuffer;

public:
    FeedbackPkt(const char *name = nullptr);
    virtual ~FeedbackPkt();

    int getRemainingBuffer() const;
    void setRemainingBuffer(int value);
};

#endif /* FEEDBACKPKT_H */
