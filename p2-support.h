////////////////////////////////////////////////////////////////////////
//
// File           : p2-support.h
// Description    : Header file for project2 
// Author         : Israel Alan Agoe-Sowah
// Date           : 11/03/2023
// Notes          : ***Type bug fixes/other with dates for your records 

#ifndef P2Header //To prevent double inclusion of header
#define P2Header //To prevent double inclusion of header

#include <stdio.h>
#define byID 1
#define byNAME 2
#define dbSIZE 100
#define idSIZE 6
#define nameSIZE 10
#define emailSIZE 20


typedef struct date// do not modify
{
  int day; 
  int month;
  int year;
}date;

typedef struct Employee
{
  char ID[idSIZE];
  char first_name[nameSIZE];
  char last_name[nameSIZE];
  char email[emailSIZE];
  double salary;
  struct date hire_date;
  //declare other members
}employee, *employee_ptr;

typedef struct DataBase
{
  int total;
  struct Employee* emp;
  //a pointer to first element of empoloyee array
  //number of employees in database
}*dataBase_ptr;

// Functional Prototypes

// Function     : initialize
// Description  : This function creates an array in the database
//                then initalializes each array elemet with the data 
//                in the given file
// Inputs       : a pointer to DataBase struct
// Output       : none
void initialize (dataBase_ptr);

//Write formal comments for each function header. 
//In the same format with the initialize function


//Function	:create_record
//Description	:Creates employee record to be added to database
//Inputs	:Strings for employee ID, first and last name, email, a date struct for hire date, and database struct's pointer
//Outputs	:none  
void create_record (char* id, char* first_n, char* last_n, char* email, double sal, struct date h_date, struct DataBase *db );//specify parameters types. Clues are in the initalize function.

//Function	:print_title
//Description	:prints the header with the labels for the employee details
//Inputs	:none
//Outputs	:none
void print_title ();

//Function	:display_menu
//Description	:displays the total number of employees within the database and the options of what can be done to/with the database
//Inputs	:database struct's pointer
//Outputs	:none
void display_menu (dataBase_ptr);

//other function headers here

//Function	:save
//Description	:saves all changes to database file to a new file called database_updated
//Inputs	:database struct's pointer
//Outputs	:none  
void save(dataBase_ptr);


//Function	:comp_ID
//Description	:This function is a helper comparator function for the 
//		 sort_ID function to sort the database by ID
//Inputs	:2 pointers to the employees within the database array that are to be compared
//Outputs	:A 0 is equal ID's, 1 employee a comes after employee b, and -1 is the opposite of 1  
int comp_ID(const void *a, const void *b);

//Function	:comp_date
//Description	:This function is a helper comparator for the sort_date function to sort the database by hire date
//		 first it compares by year, then month, and lastly day
//Inputs	:2 pointers to the employees within the database array that are to be compared
//Outputs	:A 0 is equal hire dates, 1 employee a was hired after employee b, and -1 is the opposite of 1 
int comp_date(const void *a, const void *b);


//Function	:sort_ID
//Description	:Sorts the database from lowest to highest according to their ID's for each employee 
//		 by using the database pointer and qsort with it's helper comparator function
//Inputs	:database struct's pointer (db)
//Outputs	:none  
void sort_ID(dataBase_ptr db);


//Function	:sort_date
//Description	:Sorts the database from earlier to most recent according to the hire dates of the
//		 employees using the database pointer, qsort and it's helper function
//Inputs	:database struct's pointer
//Outputs	:none
void sort_date(dataBase_ptr db);


//Function	:search_id
//Description	:Prints out the details of the employee whose ID matches with user inputted ID and otherwise prints that the ID is not in the database
//Inputs	:database struct's pointer
//Outputs	: none
void search_ID(dataBase_ptr db);


//Function	:search_id
//Description	:Prints out the details of the employee(s) whose last name match with the user inputted name and other prints that no employee in the database has that last name
//Inputs	:database struct's pointer
//Outputs	: none
void search_Lname(dataBase_ptr db);

//Function	:display_em
//Description	:Displays all employees and their details from the database
//Inputs	:database struct's pointer db
//Outputs	:none
void display_em(dataBase_ptr db);


//Function	:del_Employee
//Description	:locates the employee to be deleted by user inputted ID and if match found itis removed from the employee array and the detailed of the deleted employee is printed
//Inputs	:database struct's pointer db
//Outputs	:none  
void del_Employee(dataBase_ptr db);


//Function	:quit
//Description	:Frees all dynamically allocated memory in the program before program is exited
//Inputs	:database struct's pointer (db)
//Outputs	:none  
void quit(dataBase_ptr db);

#endif //To prevent double inclusion of header
