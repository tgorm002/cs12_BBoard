#include <iostream>
#include <sstream>
#include "Reply.h"
using namespace std;

Reply::Reply(){}

Reply::Reply(const string &athr,const string &sbjct, const string &body, unsigned id)
:Message(athr,sbjct,body,id) { }


bool Reply::isReply() const {
    return true;
}


string Reply::toFormattedString() const {
    string reply = "<begin_reply>\n";
    reply += Message::toFormattedString();
    return reply;
}