//CS_Chat.cpp class implementation for Program# 1 by Tejas Menon, CS163, last edited 4/16.
//Purpose: This file contains the class implentation for CS_Chat, and all the parameters for its usage and client requirements.
#include "header.h"

CS_Chat::CS_Chat() 
{
 head = NULL;
 tail = NULL;
}

//The parent destructor that invokes the deallocation of the entire data structure
CS_Chat::~CS_Chat() 
{
 if (head) delete head; 
} 

//This function takes as argument the name, description and the number of elements in the person array
//and creates a room performing a deep copy of all the arguments. The room is inserted at the beginning of the list to simulate 
//chat programs in the real world.
bool CS_Chat::insrtRoom(char name[],char desc[],int people,person * &list) 
{
 if (!name || !desc || !list) return 0; //NULL pointers signals failure
  room * hold = head; //Holds the rest of the list
  head = new room;
  if (!tail) {tail = head;} //NULL tail (empty list)
  head->next = hold; //Reattached
  head->head = NULL; //Message head pointer in the room initialized
  head->tail = NULL; //Message tail pointer initialized
  head->people = people; //Number of people in the room stored
  head->name = new char[strlen(name)+1];
  strcpy(head->name,name);
  head->desc = new char[strlen(desc)+1];
  strcpy(head->desc,desc);
  head->list = new person[people]; 

  //Deep copy of all persons in the array
  for (int i = 0; i < people; ++i) {
   if (!((list[i].username) && (list[i].email))) return 0; //NULL username or email pointers signals failure
   (head->list)[i].username = new char[strlen(list[i].username)+1];
   strcpy((head->list)[i].username,(list[i].username)); 
   (head->list)[i].email = new char[strlen(list[i].email)+1];
   strcpy((head->list)[i].email,(list[i].email));
  }
  return 1;
}

//This function appends a message to the end of the LLL of messages, taking in the chat room name to append in and the 
//contents of the message. 
bool CS_Chat::appendMessage(char room_name[],char mesg_data[]) 
{
 return (appendMessage(room_name,mesg_data,head)); //Calls its recursive secondary
}

bool CS_Chat::appendMessage(char room_name[],char mesg_data[],room * head) 
{
 if (!head || !room_name || !mesg_data) return 0; //NULL pointers signals failure (if there existed no rooms or no rooms matched argument)
 if (!strcmp(head->name,room_name)) { //Match found between room names
  if (!head->tail) { //empty room
   head->head = new message;
   head->tail = head->head;
  } else {
   head->tail->next = new message;
   head->tail = head->tail->next;
  }
  //In both cases (if the message list was empty or not)
  head->tail->next = NULL;
  head->tail->mesg_data = new char[strlen(mesg_data)+1]; 
  strcpy(head->tail->mesg_data,mesg_data);
  head->tail->timestamp = time(NULL); //Set timestamp
  return 1;
 } 
 return appendMessage(room_name,mesg_data,head->next); //recursive call sending in the pointer to the next room
}

//This function displays all rooms matching the room name
bool CS_Chat::displayRoom(char room_name[]) 
{
 if (!head || !room_name) return 0; //No rooms or if char pointer was NULL 
 room * current = head;
 bool check = 0;
 while(current) {
  if (!strcmp(current->name,room_name)) { //Match found
   check = displayRoom(current->head); //Call the recursive displayRoom function
  }
  current = current->next;
 }
 return check;
}

bool CS_Chat::displayRoom(message * head)
{
 if (!head) return 0; //Empty room or last message
 cout << head->mesg_data << endl;
 cout << ctime(&(head->timestamp)) << "\n\n"; //Display the timestamp below each message
 displayRoom(head->next); //Recursive call
 return 1; //Always returns 1 if there existed a single message or more in a chat room
}

//This function displays all messages containing the keyword sent in by the client
bool CS_Chat::displayMessage(char keyword[])
{
 if (!head || !keyword) return 0; //No rooms or empty char pointer
 bool check = 0;
 room * current = head;
 while(current) {
  if (displayMessage(current->head,keyword)) check = 1; //Sets check to 1 if there existed a single room or more with a message containing the keyword
  current = current->next;
 }
 return check; 
}
 
bool CS_Chat::displayMessage(message * head,char keyword[]) 
{
 if (!head) return 0; //No more messages to check or empty room
 if (strstr(head->mesg_data,keyword)) { //If keyword contained in the message
  cout << head->mesg_data << endl;
  cout << ctime(&(head->timestamp)) << "\n\n";
  return (displayMessage(head->next,keyword) +1); //If there ever was a single match then a non-zero value is always returned to the initial call
 } else return (displayMessage(head->next,keyword));
} 

//This function displays all chat group names with a matching username in its array of 'persons'.
bool CS_Chat::displayUsrGroup(char username[]) 
{
 return displayUsrGroup(head,username);
}

bool CS_Chat::displayUsrGroup(room * head,char username[])
{
 if (!head || !username) return 0; //last room or char pointer is NULL
 bool check = 0;
 for (int i=0;i < (head->people);++i) {
  if (!strcmp(head->list[i].username,username)) { //If a match was found for any single participant
   check = 1;
  }
 }
 if (check) { //Display the group name if check was 1 and therefore there existed a matching username
  cout << head->name << endl;
  return (displayUsrGroup(head->next,username) +1); //As in the previous function, if there ever was a match, then a non-zero will be returned out of the intitial function call
 } else return (displayUsrGroup(head->next,username));
} 

//This function compares the timestamp for all messages in a room until the first one appended after the time on the timestamp argument, and then reconnects 
//the head pointer of that room to that first message after deallocating the sequence of messages prior to the timestamp argument
bool CS_Chat::removeMessageBefore(time_t timestamp)
{
 if (!head) return 0; //No rooms to check
 room * current = head;
 message *redirect; //Pointer that can store a message address
 bool check = 0;
 while (current) { //Until the last room
  if (current->head) { //If there exists any messages
   redirect = removeMessageBefore(current->head,timestamp); //The secondary recursive function returns a pointer to the first message appended after the timestamp 
                                                            //and also sets the previous message's next pointer to NULL (or head's).
   if (current->head) { //If messages were supposed to be removed (the secondary function didn't turn the head pointer in the room to NULL).
    delete (current->head); //delete all 'old' messages
    check = 1; //There was definitely something deleted
   }
   current->head = redirect; //Set room's head to the first message after the timestamp
   if (!redirect) {current->tail = NULL;} //If the secondary returned a NULL pointer, that means that all messages required deletion (therefore tail's NULL)
  }
  current = current->next; //Traverse to the next room
 }
 return check;
} 
   
message * CS_Chat::removeMessageBefore(message * &head,time_t timestamp)
{
 if (!head) return NULL; //Only if the last message has been reached and all messages in the room are before the timestamp.
                         //Note we took care of the case where there were no messages in the room already within the primary function.
 if (head->timestamp >= timestamp) { //If larger or same as the argument
  message * hold = head;
  head = NULL; //This assignation means that when delete is requested in the primary, the deallocation happens only till this message. Note that we passed by reference for this
  return hold;
 } else return (removeMessageBefore(head->next,timestamp));
}
  
