//main.cpp for Program# 3 by Tejas Menon, CS163, last edited on 5/21.
//Purpose: main.cpp reads in data from the external file 'events_tej.cpp' and allows testing of
//         all the BST functions in any user specified order
#include "header.h" 

int main()
{
 BST all_events;

 ifstream in_file;
 in_file.open("events_tej.txt"); //PLEASE USE THE EVENTS_TEJ.TXT FILE PROVIDED WITH THE PROGRAM AS SEVERAL EDITS HAVE BEEN MADE TO IT!
 while (in_file && !in_file.eof()) {
  char title[TEMP];
  char venue[TEMP];
  char desc[TEMP];
  time_t s_time = 0; struct tm buff; char date[TEMP]; char time[TEMP];
  keyword words[TEMP];
  bool check = true;
  int num_key = 0; 
  in_file.getline(title,TEMP,'|'); 
  in_file.getline(venue,TEMP,'|');
  in_file.getline(date,TEMP,'|');strptime(date,"%Y-%m-%d",&buff); //parses and stores the date into the buffer 'tm' struct
  in_file.getline(time,TEMP,'|');strptime(time,"%H:%M",&buff); buff.tm_isdst = -1; s_time = mktime(&buff); //parses and stores the time into the 'tm' structure and then sets
                                                                                                           //daylight savings time to 'unconfirmed'. mktime() converts the 'tm'
                                                                                                           //structure to calendar time (seconds from epoch)
  in_file.getline(desc,TEMP,'|');
  while(check) { //for all the keywords
   char temp_key[TEMP];
   check = in_file.get(temp_key,TEMP,','); in_file.ignore(100,','); in_file.clear(); //attempts to read a keyword after the last one (error flag signalled and the result passed
                                                                                     //to check). All flags reset with in_file.clear()
   if (check) {words[num_key].add(temp_key); ++num_key;} //keyword only added if check is true
  }

  event an_event;
  an_event.add(title,venue,desc,s_time,num_key,words); //add the data into event
  all_events.add(an_event); //add the event to the BST

  in_file.ignore(); in_file.ignore(); in_file.ignore(); //ignore twice for the two 'COMMAS' that weren't removed due to the error above and once again for the newline
 } 
 in_file.clear(); in_file.close(); 

 int menu_opt = 0;
 while(menu_opt!=7) {
  menu_opt = display_menu(); //user option from the menu passed to menu_opt
  if(menu_opt == 1) add(all_events);
  if(menu_opt == 2) retrieve(all_events);
  if(menu_opt == 3) remove(all_events);
  if(menu_opt == 4) remove_key(all_events);
  if(menu_opt == 5) display_all(all_events);
  if(menu_opt == 6) getHeight(all_events);
 } 
 return 0;
}

//prompts from the user their menu option and returns this value to main
int display_menu() 
{ 
 int menu_opt;
 cout << "Please choose an option from the table below.\n\n"
      << "1. Add an event into the existent database\n"
      << "2. Retrieve an event from the database\n"
      << "3. Remove an event containing said title\n"
      << "4. Remove all events containing said keyword\n"
      << "5. Display all the events in the database\n"
      << "6. Display the current height of the database\n"
      << "7. Quit\n\n"
      << "Enter here:";

 cin >> menu_opt; cin.ignore(100,'\n');
 while (menu_opt < 1 && menu_opt > 7) {
  cout << "Please enter again" << endl;
  cin >> menu_opt; cin.ignore(100,'\n');
 }
 return menu_opt;
} 

//Prompts information for event addition to the BST and performs this addition
void add(BST &table)
{ 
  int events_add; int count = 0;
  cout << "Enter the number of events you want to add" << endl;
  cin >> events_add; cin.ignore(100,'\n');
  while (events_add <=0) { 
   cout << "Please re-enter" << endl;
   cin >> events_add; cin.ignore(100,'\n');
  } 
  while (events_add--) {
  char title[TEMP];
  char venue[TEMP];
  char desc[TEMP];
  time_t s_time = 0; struct tm buff; char date[TEMP]; char time[TEMP];
  keyword words[TEMP];
  int num_key = 0; 
  cout << "Please enter the title of event number " << ++count << " that you want to add" << endl;
  cin.getline(title,TEMP,'\n'); 
  cout << "Please enter the venue" << endl;
  cin.getline(venue,TEMP,'\n');
  cout << "Please enter the date of the event in this format: 'YYYY-MM-DD'\n";
  cin.getline(date,TEMP,'\n');strptime(date,"%Y-%m-%d",&buff);
  cout << "Now please enter the 24 hour start time of the event in this format: 'HH:MM'" << endl;
  cin.getline(time,TEMP,'\n');strptime(time,"%H:%M",&buff); buff.tm_isdst = -1; s_time = mktime(&buff);
  cout << "Please also add a description" << endl;
  cin.getline(desc,TEMP,'\n');
  cout << "Now please enter the number of keywords you want to search for this event with(there is no 5 keyword bound in my program)" << endl;
  cin >> num_key; cin.ignore(100,'\n');
  for(int i=0;i<num_key;++i) {
   cout <<"Enter the word" << endl;
   char temp_key[TEMP];
   cin.getline(temp_key,TEMP,'\n');
   words[i].add(temp_key);
  }
  event an_event;
  an_event.add(title,venue,desc,s_time,num_key,words);
  if (table.add(an_event)) cout << "Event added successfully!" << endl;
  else cout << "The event probably did not contain a unique title. Please try again." << endl;
 }
}

//This function retrieves an event from the database and displays it
void retrieve(BST &table)
{
 char title[TEMP];
 event an_event;
 cout << "Please enter the title of the event you want to retrieve" << endl;
 cin.getline(title,TEMP,'\n');
 if (table.retrieve(title,an_event)) an_event.display();
 else cout << "There was no matching event. Please try again" << endl; 
}
//This function removes an event containing the specified title
void remove(BST &table) 
{
 char title[TEMP];
 cout << "Please enter the title of the event you want to remove" << endl;
 cin.getline(title,TEMP,'\n');
 if (table.remove(title)) cout << "Event successfully removed" << endl;
 else cout << "There was no matching title to remove. Please try again" << endl; 
}

//This function removes all events with the matching keyword
void remove_key(BST &table)
{
 char keyword[TEMP];
 cout << "Please enter the keyword you want to remove events for\n";
 cin.getline(keyword,TEMP,'\n');
 if (!table.remove_key(keyword)) cout << "No events to remove with said keyword" << endl;
}

//This function displays all events
void display_all(BST &table)
{ 
 if (!table.display_all()) cout << "Nothing to display!" << endl;
}

void getHeight(BST &table)
{
 cout << "The current height of the table is: "<< table.getHeight() << endl;
}
