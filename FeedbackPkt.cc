#include "FeedbackPkt.h"

FeedbackPkt::FeedbackPkt(const char *name) : cPacket(name) {
    remainingBuffer = 0;
}

FeedbackPkt::~FeedbackPkt() {
}

int FeedbackPkt::getRemainingBuffer() const {
    return remainingBuffer;
}

void FeedbackPkt::setRemainingBuffer(int value) {
    remainingBuffer = value;
    EV_INFO << "Sending feedback with remainingBuffer = " << remainingBuffer << endl;
}
