//inclusion guards
//includes

#ifndef TOPIC_H
#define TOPIC_H
#include "Message.h"
#include <iostream>

using namespace std;


  class Topic : public Message {   
   // no new member variables
   public:

     //default constructor
     Topic();

     //Parameterized constructor
     Topic(const string &athr, 
           const string &sbjct, 
           const string &body, 
           unsigned id);
	 
	virtual bool isReply() const;  // Returns false
          
     /* toFormattedString writes the contents of the Topic to a 
      * string in the following format:

        <begin_topic>
        :id: 4
        :subject: single line
        :from: author
        :children: 5 6 [this line should not be printed if there are no children.]
        :body: multiple lines - line 1
        line 2
        line 3
        <end>

      * line starting with :children: has the ID's of all children (See file specs. 
      * for details)
      * This function should not assume the last character in body is a newline.
      * In other words, this function must manually add a newline after the last    
      * line of the body (line 3 in this example).
      * Also, the last character in the string must be a newline.
      */
     virtual string toFormattedString() const;  // New !!

  };

  //end inc guards
    #endif

