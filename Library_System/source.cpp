#include "header.h"

static vector<User>Users;
static vector<Admin>Admins;
static vector<Book>Books;


void Lib_System() {
	
	Get_from_A_file(ADMIN);
	Get_from_U_file(USER);
	Get_from_BK_file(BOOK);
	Get_from_BR_file(BORROWER);
	Get_from_BT_file(RETURNER);
	Lib_Structure();
}
void Lib_Structure() {
	system("cls");
	cout << "\t||----------------------------------||\n"
		<<  "\t||  Welcome to the Online Libtary.  ||\n"
		<<  "\t||----------------------------------||\n";
	cout << " 1) Sign up\n"
		<< " 2) Log in\n"
		<< " 3) Exit\n";
	int ans;
	cin >> ans;
	switch (ans) {
	case 1:
		Sign_up();
		break;
	case 2:
		Log_in();
		break;
	case 3:
		Send_to_A_file(ADMIN);
		Send_to_U_file(USER);
		Send_to_BK_file(BOOK);
		Send_to_BR_file(BORROWER);
		Send_to_BT_file(RETURNER);
		exit(0);
	}
}

//dealing with file stream
void Get_from_U_file(string Path) {
	ifstream U_File(Path);
	if (U_File.is_open()) {
		User user;
		while (Users.size() < Max_Users && U_File >>
			     user.name >> user.id >> user.pass) {
			Users.push_back(user);
		}
		U_File.close();
	}
}
void Send_to_U_file(string Path) {
	ofstream U_File(Path, ios::trunc);
	if (U_File.is_open()) {
		for (int i = 0; i < Users.size(); i++) {
			U_File << Users[i].name << " "
				<< Users[i].id << " " << Users[i].pass << endl;
		}
		U_File.close();
	}
}
void Get_from_A_file(string Path) {
	ifstream A_File(Path);
	if (A_File.is_open()) {
		Admin admin;
		while (Admins.size() < Max_Admins && A_File >> admin.name >>
			admin.id >> admin.pass) {
			Admins.push_back(admin);
		}
		A_File.close();
	}
}
void Send_to_A_file(string Path) {
	ofstream A_File(Path, ios::trunc);
	for (int i = 0; i < Admins.size(); i++)
	{
		A_File << Admins[i].name << " " 
			<< Admins[i].id << " " << Admins[i].pass << endl;
	}
	A_File.close();
}
void Get_from_BK_file(string Path) {
	ifstream B_File(Path);
	if (B_File.is_open()) {
		Book book;
		while (Books.size() < Max_Books && B_File >> book.name >>
			book.category >> book.id >> book.quantity) {
			Books.push_back(book);
		}
		B_File.close();
	}
}
void Send_to_BK_file(string Path) {
	ofstream B_File(Path, ios::trunc);
	for (int i = 0; i < Books.size(); i++)
	{
		B_File << Books[i].name << " " << Books[i].category << " " <<
			Books[i].id << " " << Books[i].quantity << endl;
	}
	B_File.close();
}
void Get_from_BR_file(string Path) {
	ifstream BR_File(Path);
	if (BR_File.is_open()) {
		int Id{}, sz{}, U_Id{-1};
		while (Books.size() < Max_Books && BR_File >> Id >>sz) {
			for (int i = 0; i < sz; i++) {
				BR_File >> U_Id;
				Books[Id].borrower.push_back(U_Id);
			}
		}
		BR_File.close();
	}
}
void Send_to_BR_file(string Path) {
	ofstream B_File(Path, ios::trunc);
	for (int i = 0; i < Books.size(); i++)
	{
		if (!Books[i].borrower.empty()) {
			B_File << i << " " << Books[i].borrower.size() << " ";
			for (int j = 0; j < Books[i].borrower.size(); j++) {
				B_File << Books[i].borrower[j];
				if (j != (Books[i].borrower.size() - 1)) {
					B_File << " ";
				}
			}
			B_File << endl;
		}
	}
	B_File.close();
}
void Get_from_BT_file(string Path) {
	ifstream BT_File(Path);
	if (BT_File.is_open()) {
		int Id{}, sz{}, U_Id{ -1 };
		while (Books.size() < Max_Books && BT_File >> Id >> sz) {
			for (int i = 0; i < sz; i++) {
				BT_File >> U_Id;
				Books[Id].returner.push_back(U_Id);
			}
		}
		BT_File.close();
	}
}
void Send_to_BT_file(string Path) {
	ofstream BT_File(Path, ios::trunc);
	for (int i = 0; i < Books.size(); i++)
	{
		if (!Books[i].returner.empty()) {
			BT_File << i << " " << Books[i].returner.size() << " ";
			for (int j = 0; j < Books[i].returner.size(); j++) {
				BT_File << Books[i].returner[j];
				if (j != (Books[i].returner.size() - 1)) {
					BT_File << " ";
				}
			}
			BT_File << endl;
		}
	}
	BT_File.close();
}

string Pass_encript(string pass) {
	for (int i = 0; i < pass.length(); i++) {
		pass[i] = (int)((pass[i] * 3) / 2 + 5);
	}
	return pass;
}

void Sign_up() {
	system("cls");
	cout << "\t||---------------------------------------------------------------------||\n"
		<< "\t||   Please Enter The Admin Password to create a new Admin account..   ||\n"
		<< "\t||---------------------------------------------------------------------||\n";
	string A_pass; 
	A_pass = Pass_to_stars();
	if (A_pass == "Admin") {
		system("cls");
		cout << "\t||-----------------------------------------||\n"
			<< "\t||   Please Enter all the correct data..   ||\n"
			<< "\t||-----------------------------------------||\n";

		Admin admin;
		cout << "  Name : ";
		cin >> admin.name;
		cout << endl;
		cout << "\t||---------------------------------------||\n"
			<< "\t||   Wait till genrating a unique Id ..  ||\n"
			<< "\t||---------------------------------------||\n";
		this_thread::sleep_for(std::chrono::seconds(1));

		admin.id = Random_ID('a');

		cout << "\t||---------------------------------------\n"
			<< "\t||   Your unique ID is : " << admin.id << "\n"
			<< "\t||-----------------------------------------\n";

		cout << " Password : ";
		cin >> admin.pass;
		admin.pass = Pass_encript(admin.pass);
		Admins.push_back(admin);
		cout <<"\t||----------|| \n"
			<< "\t||   Done  ||\n"
			<< "\t||---------||\n";
		this_thread::sleep_for(std::chrono::seconds(1));
		Lib_Structure();
	}
	else {
		cout << "\t||------------------|| \n"
			<< "\t||   Wrong Password ||\n"
			<< "\t||------------------||\n";
		this_thread::sleep_for(std::chrono::seconds(1));
		Lib_Structure();
	}
}

int Random_ID(char ch) {
	int mn{}, mx{}, val{};
	switch (ch)
	{
	case 'u':// for users
		mn = 400; mx = 600;
		break;
	case 'a': //for admins
		mn = 700; mx = 900;
		break;
	case 'b'://for books
		mn = 100; mx = 300;
		break;
	}
		srand(time(nullptr)); // seed the random number generator with the current time
		val=mn + rand() % (mx - mn + 1); // generate a random number within the specified range
		if (ID_Check(ch, val)) {
			return val;
		}
		else {
			Random_ID(ch);
		}
}

bool ID_Check(char ch, int val) {
	bool flag = true;
	switch (ch)
	{
	case 'u':// for users
		for (int i = 0; i < Users.size(); i++) {
			if (Users[i].id == val)
			{
				flag = false;
				break;
			}
		}
		break;
	case 'a': //for admins
		for (int i = 0; i < Admins.size(); i++) {
			if (Admins[i].id == val)
			{
				flag = false;
				break;
			}
		}
			break;
	case 'b'://for books
		for (int i = 0; i < Books.size(); i++) {
			if (Books[i].id == val)
			{
				flag = false;
				break;
			}
			break;
		
		}
	}
	return flag;
}

void Log_in() {
	while (true) {
		system("cls");
		int id;
		string pass;
		cout << "\t||-------------------------------||\n"
			<< "\t||            Log in ...         ||\n"
			<< "\t||-------------------------------||\n";
		cout << "  ID : ";
		cin >> id;
		cout << "  Password : ";
		pass = Pass_to_stars();
		pass = Pass_encript(pass);
		if (id >= 700 && id <= 900) {
			for (int i = 0; i < Admins.size(); i++) {
				if (id == Admins[i].id && pass == Admins[i].pass) {
					Admin_Home(i);
				}
			}
		}
		else if (id >= 400 && id <= 600) {
			for (int i = 0; i < Users.size(); i++) {
				if (id == Users[i].id && pass == Users[i].pass) {
					User_Home(i);
				}
			}
		}
		cout << " There are no matching  Try again\n";
		this_thread::sleep_for(std::chrono::seconds(1));
	}


}
string Pass_to_stars() {
	string password;
	char c;
	while ((c = _getch()) != '\r') {
		if (c == '\b') {
			if (password.length() > 0) {
				cout << "\b \b";
				password.pop_back();
			}
		}
		else {
			cout << "*";
			password += c;
		}
	}
	cout << endl;
	return password;
}

void User_Home(int U_index) {
	system("cls");
	cout << "\t||-------------------------------\n"
		<< "\t||\t\tHi " << Users[U_index].name << "\n"
		<< "\t||\tHow Could we help you..\n"
		<< "\t||-------------------------------\n"
		<< "\t||\t1)Search for a Book\n"
		<< "\t||\t2)Borrow a Book\n"
		<< "\t||\t3)Return a Book\n"
		<< "\t||\t4)Exit\n"
		<< "\t||-------------------------------\n";
	int ans;
	cin >> ans;
	switch (ans) {
	case 1:
		Book_Search(U_index);
		break;
	case 2:
		Borrow_Book(U_index);
		break;
	case 3:
		Return_Book(U_index);
		break;
	case 4:
		Lib_Structure();
		break;
	default:
		cout << "Invalid answer\n";
		this_thread::sleep_for(std::chrono::seconds(1));
		break;
	}
	User_Home(U_index);
}
void Book_Search(int U_index) {
	system("cls");
	cout << "\t||-----------------------------------||\n"
		<< "\t||         Search for a Book...      ||\n"
		<< "\t||-----------------------------------||\n";
	cout << "Enter any sub string of The Book you Need : ";
	string ans;
	cin >> ans;
	int sub_index{ -1 }, cnt{};
	for (int i = 0; i < Books.size(); i++) {
		sub_index = Books[i].name.find(ans);
		if (sub_index != -1) {
			cout <<" "<< ++cnt << ") ";
			Book_Details(i);
		}
	}
	cout << endl;
	system("pause");

}
void Book_Details(int B_index) {
	cout << "  Name : " << Books[B_index].name << "\t Category : " << Books[B_index].category << endl
		<< "  ID : " << Books[B_index].id << "\t Quantity : " << Books[B_index].quantity << endl;
	cout << "------------------------------------------------\n";
}
int Get_Book_By_Id(int Id) {
	for (int i = 0; i < Books.size(); i++) {
		if (Books[i].id == Id) {
			return i;
		}
	}
	return -1;
}
void Borrow_Book(int U_index) {
	system("cls");
	cout << "\t||-------------------------------||\n"
		<< "\t||         Borrow a Book...      ||\n"
		<< "\t||       Enter the Book Id..     ||\n"
		<< "\t||-------------------------------||\n";
	int ans;
	cin >> ans;
	int B_index = Get_Book_By_Id(ans);
	if (B_index == -1) {
		cout << "There are no book with this Id\n";
	}
	else {
		cout << "  Name : " << Books[B_index].name << "\t Category : " << Books[B_index].category << endl
			<< "  ID : " << Books[B_index].id << "\t Quantity : " << Books[B_index].quantity << endl;
		cout << "\t------------------------------------------------\n";
	}
	cout << " 1) Borrow \n 2) Back\n";
	int ans2;
	cin >> ans2;
	switch (ans2)
	{
	case 1:
		Books[B_index].quantity--;
		Books[B_index].borrower.push_back(U_index);
		cout << "\t||---------|| \n"
			<< "\t||   Done  ||\n"
			<< "\t||---------||\n";
		this_thread::sleep_for(std::chrono::seconds(1));
		User_Home(U_index);
		break;
	case 2:
		User_Home(U_index);
		break;
	default:
		cout << "Invaild answer\n";
		system("pause");
		Borrow_Book(U_index);
		break;
	}

}
void Return_Book(int U_index) {
	system("cls");
	cout << "\t||-------------------------------||\n"
		<< "\t||         Return a Book...      ||\n"
		<< "\t||       Enter the Book Id..     ||\n"
		<< "\t||-------------------------------||\n";
	int ans;
	cin >> ans;
	int B_index = Get_Book_By_Id(ans);
	if (B_index == -1) {
		cout << "There are no book with this Id\n";
	}
	else {
		int borrower = Get_Borrower_By_User(B_index, U_index);
		if (borrower == -1) {
			cout << "There are no Borrowed Book by you \n";
			this_thread::sleep_for(std::chrono::seconds(1));
			User_Home(U_index);
		}
		else {
			if (borrower >= 0 && borrower < Users.size()) {
				Books[B_index].borrower.erase(Books[B_index].borrower.begin() + borrower);
			}
			Books[B_index].returner.push_back(U_index);
			Books[B_index].quantity++;
			cout << "\t||------------------------------|| \n"
				<< "\t||   Returned Successfully..    ||\n"
				<< "\t||------------------------------||\n";
			this_thread::sleep_for(std::chrono::seconds(1));
			User_Home(U_index);
		}
	}
}
int Get_Borrower_By_User(int B_index,int U_index) {
	for (int i = 0; i < Books[B_index].borrower.size(); i++) {
		if (Books[B_index].borrower[i] == U_index) {
			return i;
		}
	}
	return -1;
}


void Admin_Home(int A_index)
{
	system("cls");
	cout << "\t||-------------------------------\n"
		<< "\t||\t\tHi " << Admins[A_index].name << "\n"
		<< "\t||\tHow Could we help you..\n"
		<< "\t||-------------------------------\n"
		<< "\t||  1)Add new Book\n"
		<< "\t||  2)Print All Books\n"
		<< "\t||  3)Add User\n"
		<< "\t||  4)Print All Users\n"
		<< "\t||  5)Remove User\n"
		<< "\t||  6)Print Borrowed Books\n"
		<< "\t||  7)Print Returned Books\n"
		<< "\t||  8)Exit\n"
		<< "\t||-------------------------------\n";
	int ans;
	cin >> ans;
	switch (ans) {
	case 1:
		Add_new_Book(A_index);
		break;
	case 2:
		Print_All_Books(A_index);
		break;
	case 3:
		Add_User(A_index);
		break;
	case 4:
		Print_All_Users(A_index);
		break;
	case 5:
		Remove_User(A_index);
		break;
	case 6:
		Print_Borrowed_Books(A_index);
		break;
	case 7:
		Print_Returned_Books(A_index);
		break;
	case 8:
		Lib_Structure();
		break;
	default:
		cout << "Invalid answer\n";
		this_thread::sleep_for(std::chrono::seconds(1));
		Admin_Home(A_index);
	}
}
void Add_new_Book(int A_index) {
	system("cls");
	Book books;
	cout << "\t||-------------------------------||\n"
		<< "\t||         Add New Book ...      ||\n"
		<< "\t||-------------------------------||\n";
	cout << "\tBook Name : ";
	cin >> books.name;
	cout << "\tBook Category : ";
	cin >> books.category;
	cout << "\tBook Quantity : ";
	cin >> books.quantity;
	books.id = Random_ID('b');
	Books.push_back(books);
	cout << "\t||---------|| \n"
		<< "\t||   Done  ||\n"
		<< "\t||---------||\n";
	this_thread::sleep_for(std::chrono::seconds(1));
	Admin_Home(A_index);
}
void Print_All_Books(int A_index) {
	system("cls");
	cout << "\t||-------------------------------||\n"
		<< "\t||         Library Books...      ||\n"
		<< "\t||-------------------------------||\n";
	for (int i = 0,j=0; i < Books.size(); i++) {
		if (Books[i].quantity == 0) {
			continue;
		}
		cout << "  Book no." << ++j << endl
			<< "  Name : " << Books[i].name << "\t Category : " << Books[i].category << endl
			<< "  ID : " << Books[i].id << "\t Quantity : " << Books[i].quantity << endl;
		cout << "------------------------------------------------\n";
	}
	system("pause");
	Admin_Home(A_index);

}
void Add_User(int A_index) {
	system("cls");
	cout << "\t||----------------------------------------------||\n"
		<< "\t||   Please Enter all the correct user data..   ||\n"
		<< "\t||----------------------------------------------||\n";
	User user;
	cout << "  Name : ";
	cin >> user.name;
	cout << endl;
	cout << "\t||-----------------------------------------||\n"
		<< "\t||   Wait till genrating a unique Id ..    ||\n"
		<< "\t||-----------------------------------------||\n";
	this_thread::sleep_for(std::chrono::seconds(1));

	user.id = Random_ID('u');

	cout << "\t||---------------------------------------\n"
		<< "\t||   Your unique ID is : " << user.id << "    \n"
		<< "\t||-----------------------------------------\n";

	cout << " Password : ";
	cin >> user.pass;
	user.pass = Pass_encript(user.pass);
	Users.push_back(user);
	cout << "\t||---------|| \n"
		<< "\t||   Done  ||\n"
		<< "\t||---------||\n";
	this_thread::sleep_for(std::chrono::seconds(1));
	Admin_Home(A_index);

}
void Print_All_Users(int A_index) {
	system("cls");
	cout << "\t||-------------------------------||\n"
		<< "\t||         Library Users...      ||\n"
		<< "\t||-------------------------------||\n";
	for (int i = 0; i < Users.size(); i++) {
		cout << "  User no." << i + 1 << endl
			<< "  Name : " << Users[i].name << "\tID : " << Users[i].id << endl;
		cout << "------------------------------------------------\n";
	}
	system("pause");
	Admin_Home(A_index);
}
void Remove_User(int A_index) {
	system("cls");
	for (int i = 0; i < Users.size(); i++) {
		cout << "  User no." << i + 1 << endl
			<< "  Name : " << Users[i].name << "\tID : " << Users[i].id << endl;
		cout << "------------------------------------------------\n";
	}
	cout << "Enter user Id you want to remove\n";
	int ans; cin >> ans;
	int ind = Get_User_By_Id(ans);
	if (ind == -1) {
		cout << "There are no User with this Id \n";
		this_thread::sleep_for(std::chrono::seconds(1));
		Admin_Home(A_index);
	}
	else {
		if (ind >= 0 && ind < Users.size()) {
			Users.erase(Users.begin() + ind);
		}
		cout << "\t||---------|| \n"
			<< "\t||   Done  ||\n"
			<< "\t||---------||\n";
		this_thread::sleep_for(std::chrono::seconds(1));
		Admin_Home(A_index);
	}
	
}
int Get_User_By_Id(int Id) {
	for (int i = 0; i < Users.size(); i++) {
		if (Users[i].id == Id) {
			return i;
		}
	}
	return -1;
}
void Print_Borrowed_Books(int A_index) {
	system("cls");
	for (int i = 0; i < Books.size(); i++) {
		if (!Books[i].borrower.empty()) {
			for (int j = 0; j < Books[i].borrower.size(); j++) {
				cout << "Book Name : " << Books[i].name << "\t\tBook Category : " 
					<< Books[i].category << "\tId : " << Books[i].id
					<< "\n\tUser Name : " << Users[Books[i].borrower[j]].name
					<< "\t\tUser Id : " << Users[Books[i].borrower[j]].id
					<< "\n-------------------------------------------------\n";
			}
		}
	}
	system("pause");
	Admin_Home(A_index);
}
void Print_Returned_Books(int A_index) {
	system("cls");
	for (int i = 0; i < Books.size(); i++) {
		if (!Books[i].returner.empty()) {
			for (int j = 0; j < Books[i].returner.size(); j++) {
				cout << "Book Name : " << Books[i].name << "\t\tBook Category : "
					<< Books[i].category << "\tId : " << Books[i].id
					<< "\n\tUser Name : " << Users[Books[i].returner[j]].name
					<< "\t\tUser Id : " << Users[Books[i].returner[j]].id
					<< "\n-------------------------------------------------\n";
			}
		}
	}
	system("pause");
	Admin_Home(A_index);
}
