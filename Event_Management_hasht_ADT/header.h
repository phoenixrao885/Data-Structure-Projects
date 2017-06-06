//header.h for Program# 3 by Tejas Menon, CS163, last edited on 5/21.
//Purpose: This file contains the class interfaces for the hashtable and also the structures for the node and the event
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <time.h> //uses the strptime(), mktime() ctime() and time() functions from this library for conversions between different time formats

using namespace std;

const int TEMP = 1000; //temporary usage
const int TABLE = 269; //Size of the table. Do not set this to a zero or negative number. 

struct keyword
{
 char * word; //each keyword struct stores a collections of characters 

 bool add(char keyword[]); //for addition to a structure. Note that the public access for all of these members do not affect their integrity within the hashtable data structure
 keyword();
 ~keyword();
}; 

//This structure stores data relevant to an event and all functions and members can be accessed publicly since it would be cumbersome and meaningless
//if all these members were private but yet could be accessed and modified by way of member functions
struct event 
{
 char * title;
 char * venue;
 char * desc;
 time_t s_time; //time_t (an integer data type fundamentaly) stores the start time
 int num_key; //number of keywords in an event. (Not limited to five)
 keyword * words; //a pointer to 'num_key' keywords
 
 event();
 ~event();
 bool add(char name[],char place[],char info[],time_t start_time,int keywords,keyword*words); //creates an event using the specified argments
 bool copy(event&to_copy); //copies an event passed by reference
 bool display(); //displays the contents of the event
};

//This structure forms the chain for each index in the hashtable and contains a pointer to an event rather than the event itself
struct node 
{
 event * an_event;
 node * next;
};

//This structure is the highest level class that the client interacts with to perform functions on pre-created events
class hashtable 
{
 public:
 hashtable();
 ~hashtable();
 bool add(event & an_event); //adds an event to the hashtable
 bool retrieve(char  keyword[],event all_matches[],int&num_found); //retrieves num_found events from the hashtable matching keyword
 bool remove_before(long int time); //removes events before the specified time
 bool display(char keyword[]); //displays all events containing the keyword
 bool display_all(); //displays all the events
 private:
 int hashfunc(char * keyword); //private function called on by several functions above
 bool remove_in_table(node*&head,char title[],bool once); //removes a specific titled event from a single chain
 bool key_in_event(event&an_event,char keyword[]); //returns true if the keyword is present in the event argument

 node**table; 
};

//These functions are called by the main file to test the data structure in any user specified order
int display_menu(); 
void add_event(hashtable &table);
void display_all(hashtable &);
void retrieve(hashtable &);
void display(hashtable &);
void remove_before(hashtable &);


