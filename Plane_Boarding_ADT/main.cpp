//main.cpp class implementation for Program# 2 by Tejas Menon, CS163, last edited 4/29.
//Purpose: This file will test the ADT functions in any user specified order
#include "header.h"

int main()
{
 int halfrow,rows;
 int menu_opt = 0;
 cout << "Hello, for this airplane boarding test program, please begin by entering the total number of seats\n"
      << "in half a row for a single aisle airplane" << endl;
 cin >> halfrow;
 cin.ignore(100,'\n');

 while(halfrow <1) {
  cout << "Invalid data entered, please re-enter" << endl;
  cin >> halfrow;
  cin.ignore(100,'\n');
 }
 cout << "Next, please enter the total number of rows in the airplane" << endl;
 cin >> rows;
 cin.ignore(100,'\n');

 while(rows <1) {
  cout << "Invalid data entered, please re-enter" << endl;
  cin >> rows;
  cin.ignore(100,'\n');
 } 

 plane united(halfrow,rows); //classic

 while (menu_opt !=8) {
  menu_opt = display_menu(); //calls the display menu function everytime unless quit is requested
  if (menu_opt == 1) add_to_preboard(united);
  if (menu_opt == 2) move_to_board(united);
  if (menu_opt == 3) seat_in_plane(united);
  if (menu_opt == 4) disembark(united);
  if (menu_opt == 5) display_preboard(united);
  if (menu_opt == 6) display_board(united);
  if (menu_opt == 7) display_plane(united);
 }
 return 0;
}

//displays the menu and inputs from the user their choice
int display_menu() 
{
 int menu_opt;
 cout << "Please choose from the boarding operations below\n\n"
      << "1. Add a passenger into the preboard queue\n"
      << "2. Move all passengers from the preboard queue to the board queue\n"
      << "3. Seat all passengers from the board queue into the plane\n"
      << "4. Disembark a passenger from the plane\n"
      << "5. Display the preboard queue\n"
      << "6. Display the board queue\n"
      << "7. Display the entire plane\n"
      << "8. Exit\n\n"
      << "Enter here:";
 cin >> menu_opt;
 cin.ignore(100,'\n');

 while (menu_opt <1 || menu_opt >8) {
  cout << "Invalid menu option. Please re-enter" << endl;
  cin >> menu_opt;
  cin.ignore(100,'\n');
 } 
 return menu_opt;
}

//client function for collecting passenger details before calling functions on 'united'
void add_to_preboard(plane & united)
{
 passenger temp;
 char name[TEMP];
 int row;
 char seat;
 cout << "Please enter a passenger name to add" << endl;
 cin.get(name,TEMP,'\n'); 
 cin.ignore(100,'\n');
 cout << "Please enter their ROW number" << endl;
 cin >> row;
 cin.ignore(100,'\n');
 cout << "Please enter their SEAT character" << endl;
 cin >> seat;
 cin.ignore(100,'\n');
 temp.add(name,row,seat);
 if (united.add_to_preboard(temp)) 
  cout << "Passenger was successfully added!" << endl;
 else
  cout << "Operation failed due to invalid seat numbers" << endl;
}

//Client function to move preboarded passengers to the board queue
void move_to_board(plane & united)
{
 if (united.move_to_board()) cout << "Successful transfer!" << endl;
 else cout << "Empty preboard queue or boarding had already begun for an earlier batch or there contained two or more\n"
           << "identical seat numbers in the preboard queue. Please move the previous batch into the plane if there were any and try again" << endl;
}

//Client function to seat boarded passengers into the plane
void seat_in_plane(plane & united)
{
 if (united.seat_in_plane()) cout << "All passengers were seated successfully!" << endl;
 else cout << "Empty boarding queue or the plane already contained passengers seated after the first person in the boarding queue\n"
           << "or the first passenger from the boarding queue had the same seat as the latest passenger in the plane. Display\n"
           << "passengers to troubleshoot\n";
}

//disembarks and displays their details
void disembark(plane & united)
{
 passenger temp;
 if (united.disembark(temp)) {
  cout << "Disembarked passenger details:" << endl;
  temp.display();
 } else cout << "No more passengers left to disembark" << endl;
}

//displays the preboard queue
void display_preboard(plane & united)
{
 if (!united.display_preboard()) cout << "No passengers in the preboard queue\n";
} 

//displays the board queue
void display_board(plane & united)
{
 if (!united.display_board()) cout << "No passengers in the board queue\n";
}

//displays the entire plane
void display_plane(plane & united)
{
 if (!united.display_plane()) cout << "No passengers in the plane\n";
}
