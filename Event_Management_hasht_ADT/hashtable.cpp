//hashtable.cpp for Program# 3 by Tejas Menon, CS163, last edited on 5/21.
//Purpose: This file contains the class implementation for the hashtable and is the highest level class
//         that only deals with the basic data type event.
#include "header.h"

//The constructor initiializes the the table array and sets each 'head' node to NULL
hashtable::hashtable()
{
 table = new node*[TABLE];
 for(int i=0;i<TABLE;++i) {
  table[i] = NULL;
 }
}

//The destructor simply calls the remove_before() function with a time_t argument 50 years 
//into the future. This assumes that NO EVENTS BEING ADDED EXCEED THAT DATE. For a complete overview
//of why this approach was chosen, please refer to the remove_before() function below.
hashtable::~hashtable()
{
 remove_before((50*365*86400)+time(NULL));
 delete[]table;
}

//This function produces a hash key by adding the characters in the argument
//and then limits this value to be within the table boundaries by modulo division
int hashtable::hashfunc(char * keyword)
{
 char each = *keyword;
 int hashs = 0;
 for (int i=1;(each && (each != '\0'));++i) {
  hashs += each;
  each = keyword[i]; 
 }
 return hashs%TABLE;
}

//This recursive function removes the first node that has an event with a title matching the 
//argument and deallocates this event depending on the boolean state of 'once'.
bool hashtable::remove_in_table(node *&head,char title[],bool once)
{
 if (!head) return 0;
 if (!strcmp(head->an_event->title,title)) {
  node*hold = head->next;
  if (once) delete head->an_event; 
  delete head;
  head = hold; //pass by reference allows this assignation
  return 1;
 }
 return (remove_in_table(head->next,title,once));
}

//This function is responsible for removing all nodes from the hashtable that point to 
//events held prior to a specific start time. The function also solves the problem
//of possibly deallocating the same event twice by using the hashfunction to visit event duplicates for every keyword
// and removing the nodes at these indexes prior to deallocating the event.
bool hashtable::remove_before(long int time)
{
 bool no_removal = true; //if no nodes were needed to be removed before the time argument
 for(int i=0;i<TABLE;++i) { //for every 'head' node in the table
  node*current = table[i];
  while (current) { //for no chains at a specific index or after removal
   event*an_event = current->an_event; //an_event points to the node's event
   if (an_event->s_time < time) { 
    bool once = no_removal = false; //once is a variable that only turns true once for each event to be deallocated
    event temp;
    temp.copy(*an_event); //copies the current event data into a temporary. (Since the event could already be deallocated when we try to gain info from it)
    for(int j=0;j<(temp.num_key);++j) { //for each keyword in the event
     int index = hashfunc((temp.words[j]).word); //finds the index to be removed from for this particular keyword
     if (table[index] == table[i]) current = current->next; //if the node to be removed is in the chain we are in, then we must traverse each time that happens
     if (j == temp.num_key-1) once = true; //if we are at the last keyword for an event, let's deallocate the event
     remove_in_table(table[index],temp.title,once); //calls the function above and passes it once
    }
   } else current = current->next; //if the current event wasn't before the time passed in, traverse further until current is NULL
  }
 }
 return (!no_removal); //we return true if we could remove any nodes at all
}

//This function adds into the hashtable every event multiple times depending 
//on the number of keywords they contain. Rather than creating duplicates each time,
//each event has multiple pointers pointing to a single instance of it. The additions
//occur at the beginnings of each chain
bool hashtable::add(event&an_event)
{
 event * temp = new event; //temporarily points to the event to be added
 if(!temp->copy(an_event)) { //if the copy was unsuccessful, return a failure
  delete temp;
  return 0;
 }
 for (int i=0;i<(temp->num_key);++i) { //for each keyword
  int index = hashfunc(((temp->words)[i]).word); //find the index to store in
  node*hold = table[index]; 
  table[index] = new node;
  node*head=table[index];
  head->next = hold;
  head->an_event = temp; //point each event pointer to the same temporary allocated at the beginning
 }
 return 1;
}

//This function retrieves from the hashtable all the events (upto the value num_found) that has 
//a keyword matching the argument and stores these within an events array. Note that duplicate 
//events may be retrieved for small hashtable sizes simply due to the higher chance of event duplicates
//winding up (for different keywords) at the same index.
bool hashtable::retrieve(char keyword[],event all_matches[],int &num_found)
{
 node*current = table[hashfunc(keyword)]; //points to the index to be retrieved from
 int max = num_found;
 num_found = 0;
 while (num_found<max && current) { //while we stay within array bounds and hasven't reached the end of the chain
  if (key_in_event(*(current->an_event),keyword)) all_matches[num_found++].copy(*(current->an_event)); //if the current event has a keyword matching the argument then retrieve
  current=current->next;
 }
 return num_found; 
}

//This function checks within an event if it contains the keyword specified. This is a requirement
//for the function above since another keyword might produce a hashvalue that winds up at the same 
//index and doesn't contain a keyword that matches the argument. This is most likely to be true for
//small or non-prime hashtable sizes
bool hashtable::key_in_event(event &an_event,char keyword[])
{
 bool check = false;
 for(int i=0;i<(an_event.num_key);++i) {
  if (!strcmp(keyword,(an_event.words[i]).word)) check = true;
 }
 return check;
}

//This function like retrieve() displays all events with a matching keyword. As before, the same event may be displayed twice
//for small hashtable sizes due to different keywords winding up at the same spot.
bool hashtable::display(char keyword[])
{
 bool check = false; 
 node*current = table[hashfunc(keyword)];
 while (current) { 
  if (key_in_event(*(current->an_event),keyword)) { //calls key_in_event() as before
   current->an_event->display();
   check = true;
  }
  current=current->next;
 }
 return check;
}

//This function displays everything in the hashtable multiple times depending on the number of keywords
//each event contains.
bool hashtable::display_all()
{
 for (int i=0;i<TABLE;++i) {
  node * current = table[i];
  while (current) { 
   current->an_event->display();
   current = current->next;
  }
 }
} 

