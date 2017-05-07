//main.cpp for Program# 1 by Tejas Menon, CS163, last edited on 4/16.
//Purpose: This file will test the class implementation using client functions that calls
//         each member function in the class using a menu that allows for any user specified order.
#include "header.h"

int main() 
{
 int menu_opt = 0;
 CS_Chat my_Chat; //create a CS_Chat object
 
 //Loop runs until quit is requested 
 while(menu_opt != 7) { 
  menu_opt = display_menu(); //An integer returned denoting the menu option of the user
  if (menu_opt == 1) { insrtRoom_Client(my_Chat); } 
  if (menu_opt == 2) { appendMessage_Client(my_Chat); }
  if (menu_opt == 3) { displayRoom_Client(my_Chat); }
  if (menu_opt == 4) { displayUsrGroup_Client(my_Chat); }
  if (menu_opt == 5) { displayMessage_Client(my_Chat); }
  if (menu_opt == 6) { removeMessageBefore_Client(my_Chat); }
 }
 return 0;
}

//Display the menu and return an integer
int display_menu() {
 int menu_opt;
 
 cout << "\n\nHi there! Please choose a task from the list below by entering a numeral between 1-7.\n"
      << "1. Insert a new chat room at the beginning\n"
      << "2. Append a message to the end of a chat room\n"
      << "3. Display messages in a particular chat room\n"
      << "4. Display the groups a user belongs to\n"
      << "5. Display messages containing a particular keyword\n"
      << "6. Remove messages older than a specified number of seconds ago\n"
      << "7. Quit\n\n"
      << "Enter here:";
 cin >> menu_opt;
 cin.ignore(100, '\n');
 
 while((menu_opt < 1) || (menu_opt > 7)) {
  cout << "Your response was invalid. Select another number between 1-7" << endl;
  cin >> menu_opt;
  cin.ignore(100, '\n');
 }
 return menu_opt;
}

//Create the necessary arguments to make a chat room
void insrtRoom_Client(CS_Chat & my_Chat) 
{
 char nameTEMP[TEMP];
 char descTEMP[TEMP];
 int people;
 person * list;
 cout << "For the new chat room, please specify a name" << endl;
 cin.get(nameTEMP,TEMP,'\n');
 cin.ignore(100,'\n');
 cout << "Please enter a description for the chat room" << endl;
 cin.get(descTEMP,TEMP,'\n');
 cin.ignore(100,'\n');
 cout << "How many people would you like to add for this chat room?" << endl;
 cin >> people;
 cin.ignore(100,'\n');
 while (people <= 0) {
  cout << "You entered a zero or negative value for the number of people. Please re-enter" << endl;
  cin >> people;
  cin.ignore(100,'\n');  
 }
 list = new person[people]; //Person array created
 char details[TEMP];
 for (int i = 0; i < people; ++i) {
  cout << "For person no. " << i+1 << ", please enter their username" << endl;
  cin.get(details,TEMP,'\n');
  cin.ignore(100,'\n');
  list[i].username = new char[strlen(details)+1];
  strcpy(list[i].username,details);
  cout << "Please also enter their email address" << endl;
  cin.get(details,TEMP,'\n');
  cin.ignore(100,'\n');
  list[i].email = new char[strlen(details)+1];
  strcpy(list[i].email,details);
 }
 if (my_Chat.insrtRoom(nameTEMP,descTEMP,people,list)) { //Result of the insertion evaluated
  cout << "Chat room successfully inserted!" << endl;
 } else {
  cout << "Insertion failed, due to NULL arguments" << endl;
 }
 delete[]list; //The person list can be deleted since a deep copy has been created within the data structure
}

//add a message 
void appendMessage_Client(CS_Chat & my_Chat) 
{
 char room_name[TEMP];
 char message[TEMP];
 cout << "Please enter the chat room name you want to add a message in:" << endl;
 cin.get(room_name,TEMP,'\n');
 cin.ignore(100,'\n');
 cout << "Please enter the message" << endl;
 cin.get(message,TEMP,'\n');
 cin.ignore(100,'\n'); 
 if (my_Chat.appendMessage(room_name,message)) { //Return value evaluated
  cout << "Message added successfully!" << endl;
 } else {
  cout << "Message not added due to unmatched room name" << endl;
 }
}

//Display all messages in a room
void displayRoom_Client(CS_Chat & my_Chat)
{
 char room_name[TEMP];
 cout << "Please enter the chat room to display messages of:" << endl;
 cin.get(room_name,TEMP,'\n');
 cin.ignore(100,'\n');
 if (!my_Chat.displayRoom(room_name)) {
  cout << "Sorry, no messages to display!" << endl;
 }
}

//Display all messages containing a keyword
void displayMessage_Client(CS_Chat & my_Chat)
{
 char keyword[TEMP];
 cout << "Please enter the keyword you want to find instances of:" << endl;
 cin.get(keyword,TEMP,'\n');
 cin.ignore(100,'\n');
 if (!my_Chat.displayMessage(keyword)) {
  cout << "Sorry, no messages to display!" << endl;
 }
} 

//Display all groups a username participates in
void displayUsrGroup_Client(CS_Chat & my_Chat)
{
 char username[TEMP];
 cout << "Please enter the username to check for participation in each chat room" << endl;
 cin.get(username,TEMP,'\n');
 cin.ignore(100,'\n');
 if (!my_Chat.displayUsrGroup(username)) {
  cout << "Sorry, this username participates in no groups!" << endl;
 }
}

//remove all messages before a timestamp
void removeMessageBefore_Client(CS_Chat & my_Chat) {
 time_t timestamp;
 int secondsBefore;
 cout << "Please enter the seconds before the time currently, before which you want all messages added to be removed" << endl; 
 cin >> secondsBefore;
 cin.ignore(100,'\n');
 timestamp = time(NULL)-secondsBefore; //Timestamp is calculated after the user enters the seconds before the current time that all messages need to be removed
 if (my_Chat.removeMessageBefore(timestamp)) {
  cout << "The removal has been successful!" << endl;
 } else {
  cout << "There were no messages to remove!" << endl;
 }
}


