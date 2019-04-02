#include <iostream>
#include <sstream>
#include "Topic.h"
using namespace std;

Topic::Topic(){}

Topic::Topic(const string &athr,const string &sbjct, const string &body, unsigned id)
:Message(athr,sbjct,body,id){}


bool Topic::isReply() const {
	return false;
}

string Topic::toFormattedString() const {
    string reply = "<begin_topic>\n";
    reply += Message::toFormattedString();
    return reply;
}