//plane.cpp class implementation for Program# 2 by Tejas Menon, CS163, last edited 4/29.
//Purpose: This file contains class functions for boarding operations to be called from the client 
#include "header.h"

//Uses delegation of arguments to create other objects
plane::plane(int a_halfrow, int rows)
 : preboard(a_halfrow,rows), board(a_halfrow,rows), leftwing(a_halfrow,rows), rightwing(a_halfrow,rows)
{
 latest = 0; //no passengers 'pushed' into the plane yet
 maxSeats = a_halfrow*rows*2; 
 maxRows = rows;
 halfrow = a_halfrow; 
}

//This function calculates the boarding position and adds the passenger into the queue
bool plane::add_to_preboard(passenger & a_pass)
{
 int row;
 char seat;
 a_pass.getSeat(row,seat); //gets row and seat info
  
 //Out of bounds row and seat numbers invalidated
 if (maxSeats<1 || maxRows<1 || row>maxRows || toupper(seat)<'A' || toupper(seat)>=('A'+(halfrow*2))) return 0;
 a_pass.boardAt(halfrow*2*(maxRows-row)+exactPos(seat)); 
 return preboard.enqueue(a_pass,false); 
}

//This function translates the seat character to a boarding position
int plane::exactPos(char seat) 
{
 int side = toupper(seat)-'A'+1; 
 if (side<=halfrow) return (side*2-1); //For seats between A and halfrow
 else { //for seats after halfrow
  int lastSeat=('A'+(halfrow*2)-1);
  return ((lastSeat-toupper(seat))*2+2);
 }
}

//This function moves preboarded characters to the board queue after performing 
//a sort on the data on the basis of the boarding position 
bool plane::move_to_board()
{
 int presize = preboard.getSize(); //presize stores the current size of the preboard queue
 int b_size = board.getSize(); //Stores the current size of the board queue
 if (!presize || b_size) return 0; //empty preboard or a board that already has passengers not allowed boarding 
 int * sort_hold = new int [presize]; //temporary array allows for quicker sorting
 passenger temp;

 //dequeue and enqueue back, storing all boarding positions into the integer array 
 for (int i=0;i<(presize);++i) {
  preboard.dequeue(temp);
  preboard.enqueue(temp,false);
  sort_hold[i] = temp.getPos();
 }
 if (!sortList(sort_hold,presize)) { //if sortList evaluates there to be repeated seat numbers, the function is aborted
  delete[]sort_hold;
  return 0;
 } 
 //for the ordered integer array, dequeue and enqueue back into preboard until a matching boarding position is found for each passenger
 for (int i=0;i<presize;++i) {
  bool check =0;
  while (!check) {
   preboard.dequeue(temp);
   if ((sort_hold[i]) == temp.getPos()) {
    check = board.enqueue(temp,true);
   } else preboard.enqueue(temp,false);
  }
 }
 delete[]sort_hold;
 return 1;
}

//Performs the sort operation on the integer array
bool plane::sortList(int * sort_hold,int size)
{ 
 //Checks for the smallest integer within incrementing subsections of the array and replaces them into an ascending order of integers
 for (int i=0;i<size;++i) {
  int smallest = maxSeats;
  int smallest_i;
  for (int j=i;j<size;++j) {
   if (sort_hold[j]<=smallest) {
    smallest=sort_hold[j]; 
    smallest_i=j;
   }
  } 
  int hold = sort_hold[i];
  sort_hold[i]=smallest;
  sort_hold[smallest_i]=hold;
  if (i && (sort_hold[i] == sort_hold[i-1])) return 0; //Checks for repeated boarding positions
 }
 return 1;
}

//This function seats boarded passengers into the plane and any empty seats between passengers 
//is also 'pushed' using an empty temporary passenger. It is important to note that this function only adds rows
//until the boarding position of the last passenger, therefore for a plane of 25 rows and a
//last passenger having seat 24C, the only rows generated would be 25(last) and 24.  
bool plane::seat_in_plane()
{
 passenger temp; //Stores non-empty passengers
 passenger temp2; //Stores empty passengers
 board.peek(temp);
 if (temp.getPos()<=latest) return 0; //if the first passenger to be seated from the board queue has a boarding position smaller or same as the latest already in plane
 while (board.getSize()) { //dequeues all from the boarding queue 
  board.dequeue(temp);
  int offset = temp.getPos()-latest; //empty seats to be 'pushed'
  while (--offset) {
   if (latest%2) rightwing.push(temp2); //all even pushes to be made into the leftwing and all odd pushes into the rightwing
   else leftwing.push(temp2);
   if (latest < maxSeats) ++latest; //denotes a push
   else return 0;
  }
  if (latest%2) rightwing.push(temp); //pushes the actual passenger into the appropriate wing.
  else leftwing.push(temp);
  if (latest < maxSeats) ++latest;
  else return 0;
 }
 return 1;
} 

//This function disembarks the next seated passenger from the airplane, popping away any empty seats in between.
//After disembarking the last passenger, any empty seats are also popped. 
bool plane::disembark(passenger & a_pass)
{
 passenger temp;
 if (leftwing.isempty() && rightwing.isempty()) return 0; //If both are empty
 if (latest%2) leftwing.pop(a_pass); //Pops a passenger from the left wing if the latest passenger 'pushed' is odd or from the right wing if the latest passenger is even
 else  rightwing.pop(a_pass);
 --latest; //denotes a pop
 while (!temp.getPos() && latest) { //Keeps popping until a passenger disembarks or until the plane is empty
  if (latest%2) leftwing.pop(temp);
  else  rightwing.pop(temp);
  --latest;
 }
 if (temp.getPos()) { //If the plane isn't empty then push this extra passenger back into the plane
  if (latest%2) rightwing.push(temp);
  else leftwing.push(temp);
  ++latest; 
 }
 return 1;
}

//This function displays the preboard queue from front to back if passengers exist
bool plane::display_preboard()
{
 return preboard.display();
}

//This function displays the board queue from front to back if passengers exist
bool plane::display_board()
{
 return board.display();
}

//This function displays the entire plane until the seat of the latest passenger pushed
bool plane::display_plane()
{
 if (leftwing.isempty() && rightwing.isempty()) return 0;
 cout << "Passengers on the left wing:" << "\n\n";
 leftwing.display();
 cout << "Passengers on the right wing:"<< "\n\n";
 rightwing.display();
 return 1;
}
 
