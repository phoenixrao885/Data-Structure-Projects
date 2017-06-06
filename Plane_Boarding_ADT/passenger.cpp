//passenger.cpp class implementation for Program# 2 by Tejas Menon, CS163, last edited 4/29.
//Purpose: This file implements all the functions that can be called on a passenger
#include "header.h"

passenger::passenger() {
 name = NULL;
 position = seat = row = 0; //initialized to 'invalid' values
}   

passenger::~passenger() {
 if (name) delete[]name;
}

//This function deep copies arguments into itself
bool passenger::add(char a_name[],int a_row,char a_seat) 
{
 if (!a_name) return 0;
 row = a_row;
 seat = a_seat;
 name = new char[strlen(a_name)+1];
 strcpy(name,a_name); 
 return 1;
}

//This function deep copies passenger details from another passenger if applicable
bool passenger::copy(passenger & from) 
{
 if (!from.name) return 0;  
 if (name) delete[]name;
 name = new char[strlen(from.name)+1];
 strcpy(name,from.name);
 row = from.row;
 seat = from.seat;
 position = from.position;
 return 1;
} 

//This function assigns the seat and row details of the current passenger to the argument
void passenger::getSeat(int & a_row,char & a_seat)
{
 a_row = row;
 a_seat = seat;
} 

//This function sets the boarding position of the current passenger to the value of the argument
bool passenger::boardAt(int a_position) 
{
 if (!a_position) return 0;
 position = a_position;
 return 1;
}

//Displays a passenger
bool passenger::display()
{
 if (!name) return 0;
 cout << "Passenger Name: " << name << "\n"
      << "Seat Number: " << row << seat << "\n"
      << "Boarding position: " << position << endl;
 return 1;
}

//Returns the boarding position of the current passenger
int passenger::getPos()
{
 return position;
}
