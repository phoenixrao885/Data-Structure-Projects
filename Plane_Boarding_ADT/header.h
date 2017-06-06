//header.h file for Program# 2 by Tejas Menon, CS163, last edited 4/29.
//Purpose: This file lists the 4 classes and two data connecting nodes for an airline boarding application
//         along with their respective function prototypes. The funcdamental data type to store and interpret
//         data is the passenger class and the highest order class for client interaction is the plane class.
           
#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

const int TEMP = 200; //For client purposes

class passenger {

 public:
 
 passenger(); 
 ~passenger();
 bool add(char name[],int row,char seat); //Prior to performing any higher order interaction with this ADT, a passenger instance must be populated
 bool copy(passenger & from); //Used frequently within the ADT for deep-copy
 void getSeat(int &row, char &seat); //Arguments populated with row and seat data
 bool boardAt(int position); //Used within the ADT to initialize the boarding position
 bool display();
 int getPos(); //Returns a number denoting the passenger's boarding position. (Can be used to check for emptiness)
 
 private:
 
 char * name; 
 char seat;
 int row;
 int position; //A number denotes an integer position of where a passenger sits in an airplane. The smallest numbered passenger boards first
};

struct s_node { //The stack housing node (A single 'halfrow')

 passenger * halfrow; //Passenger details for a 'halfrow' stored. (One side of the aisle)
 s_node * next; //To the next halfrow

 ~s_node() { //Recursively deallocate (Data structures other than an LLL must mimic an LLL prior to deletion)
  if (halfrow) delete[]halfrow;
  if (next) delete next;
 } 
};

struct q_node { //A queue node storing details of a single passenger

 passenger a_person; 
 q_node * next;

 ~q_node() { //Recursively deallocate (Data structures other than an LLL must mimic an LLL prior to deletion)
  if (next) delete next;
 }
};

class queue { //Used for maintaining and ordering passengers and check their validity within a boarding sequence

 public:

 queue(int halfrow_size,int num_of_rows); //A queue must know the plane size prior to creation
 ~queue();
 bool enqueue(passenger & a_passenger,bool sort_check); //Checks for an ascending ordered enqueue based of the boarding position if sort_check is true. Disregards if false
 bool dequeue(passenger & a_passenger);
 bool dequeue();
 int getSize(); 
 bool peek(passenger & a_passenger); 
 bool display();
 
 private:

 q_node * rear; //A circular linked list implemented for this queue
 int max; //Maximum size
 int count; //Current size
};

class stack { //Mimics the physical structure of one side of the plane for an airplane with two aisles. (Rightwing or leftwing)
 
 public:

 stack(int halfrow_size,int num_of_rows); 
 ~stack();
 bool push(passenger & a_passenger);
 bool pop(passenger & a_passenger);
 bool pop();
 bool isempty();
 bool peek(passenger & a_passenger);
 bool display();
 
 private:
 
 s_node * head; //An LLL of arrays implemented for this stack
 int top; //The index to currently add to on the stack
 int max; 
 int row_size; //'halfrow' size
 int count; //current size
}; 

class plane { //Deals with and implements instances of all prior classes to perform boarding operations on

 public:

 plane(int halfrow_size,int num_of_rows); //a plane instance intitalizes the two queues, left and right wing stacks.
 bool add_to_preboard(passenger & a_passenger); //Adds a passenger if valid, to the preboard queue
 bool move_to_board(); //Moves preboarded passengers to the board queue. (Performs a sort)
 bool seat_in_plane(); //Seats passengers from the board queue into the plane at their seat positions
 bool disembark(passenger & a_passenger); //Adds into argument the next disembarked passenger from the plane
 bool display_preboard(); //Displays the preboard queue from front to rear
 bool display_board();
 bool display_plane(); //Displays both left and right sides of the plane

 private:

 bool sortList(int*sort_list,int size); //A secondary function used for sorting boarding positions in an integer array
 int exactPos(char seat); //A secondary function to calculate the offset boarding position within a row
 int maxSeats,maxRows,halfrow,latest; //latest counts the number of passengers (empty and non-empty) 'pushed' and 'popped' from the plane
 queue preboard;
 queue board;
 stack leftwing;
 stack rightwing;
};

//Client functions to test the ADT
int display_menu();
void add_to_preboard(plane &);
void move_to_board(plane &);
void seat_in_plane(plane &);
void disembark(plane &);
void display_preboard(plane &);
void display_board(plane &);
void display_plane(plane &);
