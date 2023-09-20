#ifndef HEADER_H_
#define HEADER_H_
#include<iostream>
#include<fstream>
#include<string>
#include <vector>
#include <chrono>//delay
#include <thread>//delay
#include <conio.h>//password

using namespace std;


#define Max_Users 100
#define Max_Admins 100
#define Max_Books 100
#define USER "USER.txt"
#define ADMIN "ADMIN.txt"
#define BOOK "BOOK.txt"
#define BORROWER "BORROWER.txt"
#define RETURNER "RETURNER.txt"

struct User{
	string name;
	int id{};  //is randomly by the system from 400 to 600
	string pass;
};
struct Admin {
	string name;
	int id{};     //is randomly by the system from 700 to 900
	string pass;
};
struct Book {
	string name;
	string category;
	int id{};     //is randomly by the system from 100 to 300
	int quantity{};
	vector<int>borrower;
	vector<int>returner;
};

void Lib_System();
void Lib_Structure();

//dealing with file stream
void Get_from_U_file(string);
void Send_to_U_file(string);
void Get_from_A_file(string);
void Send_to_A_file(string);
void Get_from_BK_file(string);
void Send_to_BK_file(string);
void Get_from_BR_file(string);
void Send_to_BR_file(string);
void Get_from_BT_file(string);
void Send_to_BT_file(string);

string Pass_encript(string);

void Sign_up();

int Random_ID(char);
bool ID_Check(char,int);

void Log_in();
string Pass_to_stars();

void User_Home(int);
void Book_Search(int);
void Borrow_Book(int);
void Return_Book(int);

void Book_Details(int);
int Get_Book_By_Id(int);
int Get_Borrower_By_User(int,int);

void Admin_Home(int);
void Add_new_Book(int);
void Print_All_Books(int);
void Add_User(int);
void Remove_User(int);
void Print_All_Users(int);
void Print_Borrowed_Books(int);
void Print_Returned_Books(int);
int Get_User_By_Id(int);

#endif // 
