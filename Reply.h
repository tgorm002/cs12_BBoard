#ifndef REPLY_H
#define REPLY_H

#include "Message.h"
using namespace std;

class Reply : public Message {
    public:
        
        Reply();
        Reply(const string &athr, const string &sbjct, const string &body, unsigned id);
        virtual bool isReply() const;
        virtual string toFormattedString() const;
};

#endif