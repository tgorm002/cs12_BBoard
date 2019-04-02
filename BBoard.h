//BBoard.h
#ifndef BBOARD_H
#define BBOARD_H

#include <string>
#include <vector>
using namespace std;

#include "Message.h"
#include "User.h"
#include "Reply.h"
#include "Topic.h"

class BBoard {
 private:
 
    string title;
    vector<User> userList;
    User* currentUser;
    vector<Message*> messageList;

 public:

    BBoard();
    BBoard(const string &userIn);
    ~BBoard();
    bool loadUsers(const string & userfile);
    bool loadMessages(const string &datafile);
    bool saveMessages(const string &datafile);
    void login();
    void run();
    
 private:
 
    void display() const;
    void addUser(const string&name, const string &pass);
    const User* getUser(const string &name, const string &pw) const;
    void addTopic();
    void addReply();
};

#endif