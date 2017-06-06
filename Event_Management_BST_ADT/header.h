//header.h for Program# 4 by Tejas Menon, CS163, last edited on 5/28.
//Purpose: This file contains the class interfaces for the BST and also the structures for the node and the event
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <time.h> //uses the strptime(), mktime() ctime() and time() functions from this library for conversions between different time formats
#include <algorithm> //for std::max

using namespace std;

const int TEMP = 1000; //temporary usage

struct keyword
{
 char * word; //each keyword struct stores a collections of characters 

 bool add(char keyword[]); //for addition to a structure. Note that the public access for all of these members do not affect their integrity within the BST data structure
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

//This structure forms the nodes for the BST 
struct node 
{
 event  an_event;
 node * left;
 node * right;

 ~node() {
  if (left) delete left;
  if (right) delete right;
 }
};

//This structure is the highest level class that the client interacts with to perform functions on pre-created events
class BST
{
 public:
 BST();
 ~BST();
 bool add(event & an_event); //adds an event to the BST
 bool retrieve(char title[],event&an_event); //retrieves an event matching the title and copies this event into an_event
 bool remove(char *title); //removes an event matching title
 bool remove_key(char keyword[]); //removes ALL events matching keyword
 bool display_all(); //displays all the events
 int getHeight();
 private:
 bool key_in_event(event&an_event,char keyword[]); //returns true if the keyword is present in the event argument
 int getHeight(node* root); //Recursively finds the height of the BST (the number of nodes in the longest path from the root to a leaf) 
 bool remove(char *title,node*&root); //Recursive removal of the first node containing an event matching title
 bool remove_key(node*&root,char keyword[]); //recursive removal of all nodes with a matching keyword
 bool add(node*&root,event&an_event); //recursive addition of the event to the BST. THE TITLE MUST BE UNIQUE
 bool retrieve(node*root,char*title,event&an_event); //Recursive retrieval of the event matching title from the BST
 bool display_all(node*root); //Recursively displays all the events
 node*root;
};

//These functions are called by the main file to test the data structure in any user specified order
int display_menu(); 
void add(BST &table);
void getHeight(BST &);
void display_all(BST &);
void retrieve(BST &);
void remove(BST &);
void remove_key(BST &);


