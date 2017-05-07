// header.h file for Program# 1 by Tejas Menon, CS163, last edited 4/16.
// Purpose: This file will outline the structures 'room', 'person' and 'message' and the class interface
//          for the class 'CS_Chat'. The destructor function for each stucture will also be outlined here.

#include <iostream>
#include <cctype>
#include <cstring>
#include <ctime>

using namespace std;

const int TEMP = 1000; //Temporary size for static arrays in main.cpp

//This structure stores the details for a single person dynamically. To add a chat room, a pointer to an instance of this structure
//must be passed to the insrtRoom function.
struct person {
 char * username;
 char * email;

//Destructor function called if the struct goes out of scope.
 ~person(){
  if (username) delete[]username;
  if (email) delete[]email;
 }
};

//An instance of this structure is created and appended to a chat room whenever the addMessage function is called.
struct message {
 char * mesg_data;
 time_t timestamp; //Timestamp stores the value of the time in seconds of when the message was appended
 message * next; //Since the client will not pass in this structure as an argument to any function, we can store the next pointer in this structure itself.

//A recursive destructor means the LLL can be deallocated without a separate function in CS_Chat 
 ~message(){
  if (mesg_data) delete[]mesg_data;
  if (next) delete next;
 }
};

//An instance of this structure is created when insrtRoom is requested and it stores pointers to the structures above. 
//Again, this structure stores pointers to parts of the data structure since the client will not be passing this structure as an argument to any function.
struct room {
 char * name;
 person * list; //Each room has a list of participants
 char * desc;
 int people;
 message * head; //Each room points to a head message
 room * next;
 message * tail; //A message is always appended using the tail pointer present in every room

//This recursive destructor begins the chain reaction for the entire data structure.
 ~room(){
  if (name) delete[]name;
  if (list) delete[]list;
  if (desc) delete[]desc;
  if (head) delete head;
  if (next) delete next;
 }
};

class CS_Chat {

 public:
 CS_Chat();
 ~CS_Chat();
 bool insrtRoom(char name[],char desc[],int people,person * &list); //Static character arrays taken as arguments and a pointer to a list of person(S).
 bool appendMessage(char room_name[],char mesg_data[]); //Add a message to a certain room specified in room_name
 bool displayRoom(char room_name[]); //Display all the messages present within a certain room
 bool displayMessage(char keyword[]); //Display all messages in all rooms containing the keyword specified in the argument
 bool displayUsrGroup(char username[]); //All groups participated by a user displayed by this function
 bool removeMessageBefore(time_t timestamp); //All messages before the timestamp specified as argument removed from the data structure

 private:
 bool appendMessage(char room_name[],char mesg_data[],room * head); //The recursive secondary function called by the appendMessage above
 bool displayRoom(message * head); //The secodary function of the displayRoom above
 bool displayMessage(message * head,char keyword[]); //The secondary function of the displayMessage above.
 bool displayUsrGroup(room * head,char keyword[]); //The secondary function of the displayUsrGroup above
 message * removeMessageBefore(message *&head,time_t timestamp); //The secondary recursive function returning a 'message' pointer to the removeMessageBefore above.
 room * head;
 room * tail;
};

//All the client functions for main that requests the functions above in any user specified order

int display_menu();
void insrtRoom_Client(CS_Chat & my_Chat);
void appendMessage_Client(CS_Chat & my_Chat);
void displayRoom_Client(CS_Chat & my_Chat);
void displayMessage_Client(CS_Chat & my_Chat);
void displayUsrGroup_Client(CS_Chat & my_Chat);
void removeMessageBefore_Client(CS_Chat & my_Chat);


 
