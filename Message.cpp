#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Message.h"
#include "Reply.h"
#include "Topic.h"
using namespace std;

Message::Message() {}

Message::Message(const string &athr,  const string &sbjct, const string &bd, unsigned id){
    author = athr;
    subject = sbjct;
    body = bd;
    this-> id = id;
}

Message::~Message() { }

unsigned Message::getID() const {
    return this->id;
}

void Message::addChild(Message *child) {
    childList.push_back(child);
}

 const string & Message::getSubject() const {
     return subject;
 }



string Message::toFormattedString() const {
    ostringstream stringID;
    ostringstream intString;
	string response;
    stringID << id;
    response = ":id: " + stringID.str()  + '\n';
    response = response + ":subject: " + subject +'\n';
    response = response + ":from: " + author + '\n';
    if (childList.size() != 0) {
        response = response + ":children: ";
        for (unsigned i = 0; i<childList.size();i++){
            intString.str(string() );
            intString << childList.at(i)->getID();

            response += intString.str();
            if (i < childList.size()-1){
                response +=" ";
            }
            else {
                response += '\n';
            }
        }
    }
    response = response +":body: " + body + '\n' + "<end>\n";
    return response;
}


void Message::print(unsigned indentation) const{
        for(unsigned i = 0; i < indentation; i++) {
            cout << "  ";
        }

        cout << "Message #" << id << ": " << subject << endl;
        for(unsigned i = 0; i < indentation; i++) {
            cout << "  ";
        }
        cout << "from " << author << ":";
        cout <<' ';
        for (unsigned j = 0; j < body.size(); j++) {

            cout << body.at(j);

            if ( j == body.size() - 1){
            }

            else if (body.at(j) == '\n'){
                for(unsigned i = 0; i < indentation; i++) {
                    cout << "  ";
                }
            }
        }

        for (unsigned i = 0; i < childList.size(); i++) {
            cout << '\n' << '\n';
            childList.at(i)->print(indentation + 1);
        }

}

