//queue.cpp class implementation for Program# 2 by Tejas Menon, CS163, last edited 4/29.
//Purpose: This file will include all functions that can be called on a queue
#include "header.h"

queue::queue(int halfrow,int rows)
{
 rear = NULL;
 max = halfrow*2*rows; //max size of the queue is the max number of seats on the plane
 count = 0;
}

//Dellocates all nodes in the queue by setting the next pointer of rear to NULL and 
//utilizing the destructor for each node
queue::~queue()
{
 if (!rear) return;
 q_node * hold = rear->next;
 rear->next = NULL;
 delete hold;
} 

//Queues a passenger at the end of the list regardless of its boarding position if sort is false and if not, peeks to the last passenger in queue
//and enqueues only if this passenger has a boarding position smaller than the current passenger
bool queue::enqueue(passenger & a_pass,bool sort) 
{
 if (count>max) return 0; //Max size reached
 passenger temp;
 bool check = peek(temp); //Details of a passenger before rear stored
 if (!check || !sort || (temp.getPos() < a_pass.getPos())) { //if any are true, function proceeds
  q_node * hold = rear;
  rear = new q_node;
  rear->next = NULL;
  if (!((rear->a_person).copy(a_pass))) { //if copy fails (NULL contents)
   delete rear;
   rear = hold;
   return 0;
  }
  if (!hold) rear->next = rear; //one passenger
  else {
   q_node * hold2 = hold->next;
   hold->next = rear;
   rear->next = hold2;
  }
  ++count;
  return 1;
 }
 return 0;
}

//This function dequeues a passenger from the front of the queue if there are any left
bool queue::dequeue(passenger & a_pass) 
{
 if (!rear) return 0;
 if (rear == rear->next) { //one passenger
  a_pass.copy(rear->a_person);
  rear->next = NULL;
  delete rear;
  rear = NULL;
 } else { //multiple passengers
  q_node * hold = rear->next->next;
  a_pass.copy(rear->next->a_person);
  rear->next->next = NULL;
  delete rear->next;
  rear->next = hold;
 }
 --count;
 return 1;
}

//This function is the non-argument version of the above function
bool queue::dequeue() 
{
 passenger temp;
 if (!dequeue(temp)) return 0;
 else return 1;
}

//Returns the current size of the queue
int queue::getSize()
{
 return count;
}

//Peeks to the passenger at rear, copying their details into the argument
bool queue::peek(passenger & a_pass)
{
 if (!rear) return 0;
 return a_pass.copy(rear->a_person);
}

//This function displays a queue from front to back by comparing pointer values
bool queue::display()
{
 if(!rear) return 0;
 q_node * current = rear->next;
 current->a_person.display();
 cout << endl;
 while (current != rear) {
  current = current->next;
  current->a_person.display();
  cout << endl;
 }
 return 1;
}  


