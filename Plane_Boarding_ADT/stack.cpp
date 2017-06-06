//stack.cpp class implementation for Program# 2 by Tejas Menon, CS163, last edited 4/29.
//Purpose: This file includes the functions that can be called on the stack class, or in
//         the case of this program, half a plane
#include "header.h"

stack::stack(int halfrow,int rows) 
{
 max = halfrow*rows; //Max seats are only half of total seats
 row_size = halfrow;
 count = top = 0;
 head = NULL;
}

//Utilizes the recursive deallocator of the node
stack::~stack()
{
 if (head) delete head;
}

//The function pushes a passenger onto the stack, regardless of its emptiness
bool stack::push(passenger & a_pass) 
{
 if (count>max) return 0; //max size reached
 if (!top || top==row_size) { //for the first push or a full stack
  s_node * hold = head;
  head = new s_node;
  head->halfrow = new passenger[row_size];
  head->next = hold;
  top = 0;
 } 
 (head->halfrow)[top].copy(a_pass); //in both cases
 ++count;
 ++top;
 return 1;
}

//This function pops a passenger from the stack of there are any left and stores it within the argument
bool stack::pop(passenger & a_pass)
{
 if (!head) return 0; //empty
 if (top==1) { //last empty seat/passenger in the halfrow
  s_node * hold = head->next;
  head->next = NULL;
  a_pass.copy((head->halfrow)[0]);
  delete head;
  head = hold;
  if (!head) --top; else top = row_size; 
 } else { 
  a_pass.copy((head->halfrow)[top-1]); //normal case
  --top;
 }
 --count;
 return 1;
}

//Evaluates if the stack is empty and returns true if so
bool stack::isempty()
{
 if (head) return 0;
 return 1;
}

//Non-argument version of the previous dequeue function
bool stack::pop()
{
 passenger temp;
 if (!pop(temp)) return 0;
 return 1;
}

//This function peeks to the passenger at top and copies its details into the argument
bool stack::peek(passenger & a_pass)
{
 if (!head) return 0;
 a_pass.copy((head->halfrow)[top-1]);
 return 1;
}

//This function displays a side of the plane displaying seats from the aisle to the window (opposite order) for each row
bool stack::display()
{
 if (!head) return 0;
 s_node * current = head;
 int row;
 if (count%row_size) row = (max/row_size)-(count/row_size); //if count is perfectly divisible, then sets row to the actual value of the last row
 else row = (max/row_size)-(count/row_size-1);
 while (current) { 
  cout << "Row " << row++ << "\n" //displays the row of the last passenger and moves deeper into the stack
       << "From aisle to window:" << endl; 
  for (int i=row_size-1;i>=0;--i) {
   (current->halfrow)[i].display();
  }
  current = current->next;
 } 
 return 1;
}
