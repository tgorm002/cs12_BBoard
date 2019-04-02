#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
using namespace std;

#include "BBoard.h"

BBoard::BBoard() {
    title = "";
    userList.resize(0);
    messageList.resize(0);
    currentUser = 0;
}

BBoard::BBoard(const string& userIn) {
    title = userIn;
    userList.resize(0);
    messageList.resize(0);
    currentUser = 0;
}

BBoard::~BBoard() {
    for(unsigned i = 0; i < messageList.size(); i++) {
        delete messageList.at(i);
    }
}

bool BBoard::loadUsers(const string& userfile){
    ifstream inFS;
    inFS.open(userfile.c_str());
    if (!inFS.is_open()){
        return false;
    }
string username;
string password;

   while (inFS >> username){
       inFS >> password;
       User userData (username , password);
       userList.push_back(userData);
   }

    return true;
}
bool BBoard::loadMessages(const string &datafile){
    ifstream inFS;
    inFS.open(datafile.c_str());
    if (!inFS.is_open()){
        return false;
    }
    string input , athr, sbjct, bdy, msgType, baby, junk;
    int id;
    unsigned nMessage;
    inFS >> input;
    if (input.empty()){
        return true;
    }
    istringstream x(input);
    x >> nMessage;
    vector<vector<int> >msgChild(nMessage);
    for (unsigned i = 0; i< nMessage; i++){
        input = "";
        bdy = "";
        inFS >>  msgType;
        while (input != "<end>"){
            inFS >> input;
            if (input == ":id:"){
                inFS >> id;
            }
            else if (input == ":subject:"){
                getline (inFS,sbjct);
                sbjct = sbjct.substr(1, sbjct.size()-1) ;

            }
            else if (input == ":from:"){
                inFS >> athr;
            }
            else if (input == ":children:"){
                getline(inFS,baby);
                istringstream y(baby);
                int num;
                while(y >> num){
                    msgChild.at(i).push_back(num);
                }
            }


			else if (input == ":body:") {
                while (input != "<end>") {
                    getline( inFS, input );

                    if (input == "<end>") {
                        break;
                    }

                    bdy = bdy + input + '\n';
                }

            bdy = bdy.substr(1);
            bdy = bdy.substr(0, bdy.size()-1);
            }
        }
        if (msgType == "<begin_topic>"){
            messageList.push_back(new Topic(athr,sbjct,bdy,id));
        }
        else {
            messageList.push_back(new Reply(athr,sbjct,bdy,id));
        }
    }
    inFS.close();
    for (unsigned i = 0; i< messageList.size(); i++){
        for (unsigned j = 0; j<msgChild.at(i).size(); j++){
            messageList.at(i) -> addChild(messageList.at(msgChild.at(i).at(j)-1));
        }
    }
     return true;
}










void BBoard::login(){
    string userInfo;
    cout << "Welcome to " << title;

    while ((userInfo !="q")||(userInfo !="Q")){
        cout << endl << "Enter your username ('Q' or 'q' to quit): ";
        cin >> userInfo;
        if ((userInfo == "q") || (userInfo == "Q")){
            cout << "Bye!" << endl;
            currentUser = 0;
            exit(1);
            return;
        }

        string PW;
        cout << "Enter your password: ";
        cin >> PW;


        for (unsigned i= 0 ; i<userList.size(); i++) {
            if ((userList.at(i).check (userInfo , PW))){
                currentUser = &userList.at(i);
                cout << endl;
                cout << "Welcome back " << userInfo<<'!' << endl;
                return;
            }
        }
        cout << "Invalid Username or Password!"  << endl;
    }

}




void BBoard::run(){
    if (currentUser == 0){
        return;
    }
    char userInput = 'q';
    do {
    cout << endl;
    cout << "Menu" << endl;
    cout << "- Display Messages ('D' or 'd')" << endl;
    cout << "- Add New Topic ('N' or 'n')" << endl;
    cout << "- Add Reply to a Topic ('R' or 'r')" << endl;
    cout << "- Quit ('Q' or 'q')" << endl;
    cout << "Choose an action: ";
    cin>>userInput;
        if ((userInput == 'D')||(userInput == 'd')){
            display();
        }
       else  if ((userInput == 'N')||(userInput == 'n')){
            addTopic();
        }
        else if ((userInput == 'R') ||(userInput == 'r')){
            addReply();

        }
       if ((userInput == 'Q') || (userInput=='q')){
           break;
       }
    } while ((userInput != 'Q')||(userInput != 'q'));
    cout << "Bye!" << endl;
}



void BBoard::addTopic() {
    string yay;
    cout << "Enter Subject: ";
	cin.ignore();
    getline(cin,yay);
    string woah;
    string name;
    cout << "Enter Body: ";
    unsigned loop = 0;
    while (getline(cin,name)){
        if (name.empty()){
            unsigned size = messageList.size() + 1;
            messageList.push_back(new Topic(currentUser->getUsername(),yay,woah,size));
            return;
        }
        if (loop > 0){
            woah += '\n';
        }
    loop ++;
    woah += name;
    }
}

void BBoard::addReply(){
    int goal;
    cout << "Enter Message ID: ";
    cin >> goal;
    if (goal == -1){
        return;
    }
    int b = messageList.size();
    if ((goal > b)||(goal == 0)){
        cout << "Invalid Message ID!!" << endl;
        addReply();
    }
    string Sub = "Re: "+ messageList.at(goal -1)->getSubject();

    string woah;
    string name;
    cout << "\nEnter Body" << endl;
    cin.ignore();
    unsigned loop = 0;
    while (getline(cin,name)){
        if (name.empty()){
            unsigned id = messageList.size() + 1;
            Reply *replyStr = new Reply(currentUser->getUsername(),Sub,woah,id);
            messageList.push_back(replyStr);
            messageList.at(goal -1)-> addChild(replyStr);
            return;
        }
        if (loop > 0){
            woah += '\n';
        }
    loop ++;
    woah += name;
    }
}

void BBoard::display() const{
	cout << endl;
	if (messageList.size() == 0) {
		cout << "Nothing to Display." << endl;
	}
	else {
		for (unsigned i = 0; i < messageList.size(); i++) {

			if (messageList.at(i)->isReply() == false) {
				cout << "---------------------------------------------------------" << endl;
				messageList.at(i)->print(0);
                cout << endl;
			}
		}
		cout << "---------------------------------------------------------" << endl;
	}
}
bool BBoard::saveMessages(const string &datafile) {
    ofstream moveTo;
    moveTo.open(datafile.c_str());
        if (!moveTo.is_open()) {
            return false;
        }
        moveTo << messageList.size() << '\n';
    for (unsigned i = 0; i< messageList.size(); i++){
        moveTo << messageList.at(i)->toFormattedString();

    }
    moveTo.close();
    return true;
}

const User * BBoard::getUser(const string &name, const string &pw) const {
    for(unsigned i = 0; i < userList.size(); i++) {
        if(userList.at(i).check(name, pw)) {
            return &userList.at(i);
        }
    }
    return 0;
}	