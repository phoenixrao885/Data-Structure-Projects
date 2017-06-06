//main.cpp for Program# 3 by Tejas Menon, CS163, last edited on 5/21.
//Purpose: main.cpp reads in data from the external file 'events.cpp' and allows testing of
//         all the hashtable functions in any user specified order
#include "header.h" 

int main()
{
 hashtable all_events;

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
  all_events.add(an_event); //add the event to the hashtable

  in_file.ignore(); in_file.ignore(); //ignore once for the first 'COMMA' that wasn't removed due to the error above and once again for the newline
 } 
 in_file.clear(); in_file.close(); 
 int menu_opt = 0;
 while(menu_opt!=6) {
  menu_opt = display_menu(); //user option from the menu passed to menu_opt
  if(menu_opt == 1) add_event(all_events);
  if(menu_opt == 2) retrieve(all_events);
  if(menu_opt == 3) remove_before(all_events);
  if(menu_opt == 4) display(all_events);
  if(menu_opt == 5) display_all(all_events);
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
      << "3. Remove an event before the date and time requested\n"
      << "4. Display all events matching a keyword\n"
      << "5. Display all the events in the table\n"
      << "6. Quit\n\n"
      << "Enter here:";

 cin >> menu_opt; cin.ignore(100,'\n');
 while (menu_opt < 1 && menu_opt > 6) {
  cout << "Please enter again" << endl;
  cin >> menu_opt; cin.ignore(100,'\n');
 }
 return menu_opt;
} 

//Prompts information for event addition to the hashtable and perfroms this addition
void add_event(hashtable &table)
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
  cout << "Please enter the date of the event in this format: 'YYYY-MM-DD'. PLEASE NOTE THAT A DATE\n"
       << "FURTHER THAN 50 YEARS INTO THE FUTURE CANNOT BE MAINTAINED BY THE PROGRAM DUE TO DATA TYPE\n"
       << "AND DEALLOCATION LIMITATIONS\n";
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
  else cout << "The date and time probably didn't match the format specified. Please try again." << endl;
 }
}

//This function retrieves data from the data structure and displays these
void retrieve(hashtable &table)
{
 int events_add;
 bool check;
 char keyword[TEMP];
 cout << "Please enter the keyword you want to retrieve events for. Note that small hashtable sizes\n"
      << "may retrieve the same event more than once because of key values mapping to the same hash index\n";
 cin.getline(keyword,TEMP,'\n'); 
 cout << "Now please enter the maximum number of events you want to find. (Includes repeated events)\n";
 cin >> events_add; cin.ignore(100,'\n');
 while(events_add <=0) {
  cout <<"Please re-enter this value" << endl;
  cin>> events_add; cin.ignore(100,'\n');
 }
 event * all_matches = new event[events_add];
 check = table.retrieve(keyword,all_matches,events_add);
 if (!check) cout << "No matches to display" << endl;
 else { 
  cout << "Here are your matches:\n\n";
  for(int i=0;i<events_add;++i) {
   all_matches[i].display();
  }
 }
 delete[]all_matches;
} 

//This function removes all events from the data structure before a certain date
void remove_before(hashtable &table) 
{
 time_t s_time = 0; 
 struct tm buff; 
 char date[TEMP]; 
 char time[TEMP];
 cout << "Please enter the date before which you want events to be removed. Please enter it in this format: YYYY-MM-DD" << endl;
 cin.getline(date,TEMP,'\n');strptime(date,"%Y-%m-%d",&buff);
 cout << "Now please enter the time before which you want all events to be removed. Please enter it in this format HH:MM" << endl;
 cin.getline(time,TEMP,'\n');strptime(time,"%H:%M",&buff); s_time = mktime(&buff);
 if (table.remove_before(s_time)) cout << "Removal was successful. To verify, please display by keyword" << endl;
 else cout << "Nothing to remove" << endl;
}

//This function displays all the events matching a keyword
void display(hashtable &table)
{
 char keyword[TEMP];
 cout << "Please enter the keyword you want to display events for. Note that small hashtable sizes\n"
      << "may cause the same event to display repeatedly, due to the higher chance of keywords in the same event\n"
      << "mapping to one index. For example, if the hashtable size was 1, all events would repeat in the list as\n" 
      << "many times as the number of keywords they have\n";
 cin.getline(keyword,TEMP,'\n');
 if (!table.display(keyword)) cout << "No events to display with a matching keyword" << endl;
}

//This function displays all events
void display_all(hashtable &table)
{ 
 bool check;
 cout << "This function will display all the events in the hashtable a multiple number of times depending on the number of the keywords they have.\n"
      << "It might not be useful to use this function for debugging purposes as the number of entries may cause accessing any previous input difficult\n"
      << "Please press 1 to proceed or 0 to return to the main menu\n";
 cin >> check; cin.ignore(100,'\n');
 if (check) table.display_all(); 
}
