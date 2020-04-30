/*
ID:U1910196 Name:Jamshid Erzakov
ID:U1910229 Name: Aziz Arifkhanov
*/

#include<iostream>
#include<string>
#include<fstream> //for files
#include<windows.h> //for colors, keyboard logging
#include <conio.h> //for _getch() function
#include <ctime> //for time measurements
using namespace std;


//all menus
void mainMenu();
void adminMenuPanel();
void memberEntryPanel();
void computerEntryPanel();
void cafeManagement();
void Booking();
void Charges();
void specificMemberMenu();

//all menu texts 
string Main_menu[3] = { " Master Entry", "Cafe management", "   E x i t " };
string admin_menu[3] = { "Member entry", "Computer entry", "   Return" };
string member_menu[8] = { "Add new member", "Show members", "Delete record ", "Search member","Update member" , "   Return" };
string computer_menu[8] = { "Add new computer", "Show computer", "Delete computer ", "Search computer", "Update computer" , "   Return" };
string cafe_management[3] = { "\tBooking", "\tCharges", "\tReturn" };
string booking[3] = { "\tLog-in", "\tLog-out", "\tReturn" };
string charges[3] = { "\tTake charges", "\tShow charges", "\t  Return" };
string specific_member_menu[3] = { "\tShow Profile", "\tUpdate Profile", "\t   Return" };
string menu_headers[10] = { "  Main Menu", "Admin panel" , "Member Menu" , "Computer Menu" , "    Cafe Management" , "\tBooking" , "\t  Charges" };

//Helper functions 
void color(int color = 15) { //changing color of text in terminal
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
template <class inputTemplate> //for comfortable input
inputTemplate input(inputTemplate& inputValue, string whatTowrite, string additionalString = "") {
	cout << additionalString << whatTowrite; cin >> inputValue;
	return inputValue;
}

template <class inputTemplateInt> //checking validation
void checkValidation(inputTemplateInt& choice) {
	while (!(cin >> choice)) {
		color(12);
		cout << "\n\t\t\tError! Enter integer : ";
		cin.clear();
		cin.ignore(123, '\n');
		color();
	}
}

string askPassword(string str, string str2 = "") {  //asking password displays '*'
	cout << str2 << "\n" << str;
	char pass[32];//to store password.
	int i = 0;
	char a;//a Temp char
	for (i = 0;;)//infinite loop
	{
		a = _getch();//stores char typed in a
		if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
			//check if a is numeric or alphabet
		{
			pass[i] = a;//stores a in pass
			++i;
			cout << "*";
		}
		if (a == '\b' && i >= 1)//if user typed backspace
			//i should be greater than 1.
		{
			cout << "\b \b";//rub the character behind the cursor.
			--i;
		}
		if (a == '\r')//if enter is pressed
		{
			pass[i] = '\0';//null means end of string.
			break;//break the loop
		}
	}

	string temp;
	for (int i = 0; i < 32; i++) {
		if (pass[i] == '\0')
			break;
		temp += pass[i];
	}
	return temp;
}
void pressEsc() {   //asking to press space to continue
	color(12);
	cout << "\n\n        \t\t\t\tPress 'escape' to continue\n";
	while (true) {
		if (GetAsyncKeyState(VK_ESCAPE) != 0)
		{
			break;
		}
	}
	color(15);
}


void display_text(string text, int color = 15, int sleep = 35) //displaying text without ping
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	int len_text = text.length();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "\n\n\n\n\t\t\t\t";
	for (int x = 0; x < len_text; x++)
	{
		SetConsoleTextAttribute(console, color);
		cout << text[x];
		Sleep(30);
	}

}  
void display_text_no_ping(string text, int color = 15) //displaying text with some ping using sleep
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	cout << "\n\n\t\t\t\t\t";
	cout << text;

}

//Classes
class User {  //abstract User class
protected:
	char login[50] = { ' ' }, password[50] = { ' ' }, email[50] = { ' ' };
public:
	User() {};
	void setData(string loginInput, string passwordInput, string emailInput) {
		for (int i = 0; i < 50; i++) {
			//for login
			if (i < loginInput.length()) {
				this->login[i] = loginInput[i];
			}
			else if (i == loginInput.length()) {
				this->login[i] = '\0';
			}
			else {
				this->login[i] = ' ';
			}
			//for password
			if (i < passwordInput.length()) {
				this->password[i] = passwordInput[i];
			}
			else if (i == passwordInput.length()) {
				this->password[i] = '\0';
			}
			else {
				this->password[i] = ' ';
			}
			//for email
			if (i < emailInput.length()) {
				this->email[i] = emailInput[i];
			}
			else if (i == emailInput.length()) {
				this->email[i] = '\0';
			}
			else {
				this->email[i] = ' ';
			}

		}
	}
	void getData() {
		cout << "\t\t\t\t\tLogin : ";
		for (int i = 0; i < 50; i++) {
			if (login[i] == '\0')
				break;
			cout << login[i];
		}
		//cout << "Password - ";
		//for (int i = 0; i < 50; i++) {
		//	if (password[i] == '\0')
		//		break;
		//	cout << password[i];
		//}
		//cout << "\n";
		cout << "\n\t\t\t\t\tEmail : ";
		for (int i = 0; i < 50; i++) {
			if (email[i] == '\0')
				break;
			cout << email[i];
		}
	}

	string getLogin() { 
		string tempString;
		for (int i = 0; i < 50; i++) {
			if (login[i] == '\0')
				break;
			tempString += login[i];
		}
		return tempString; 
	}
	string getPassword() { 
		string tempString;
		for (int i = 0; i < 50; i++) {
			if (password[i] == '\0')
				break;
			tempString += password[i];
		}
		return tempString;
	}
	string getEmail() { 
		string tempString;
		for (int i = 0; i < 50; i++) {
			if (email[i] == '\0')
				break;
			tempString += email[i];
		}
		return tempString;
	}

};
class Member : public User {  //Member class which extends User class
private:
	bool is_auth = false;
	double timeElapsed = 0;
	clock_t start = 0;
	clock_t end = 0;
public:
	void changeAuth(){
		if (this->is_auth)
			is_auth = false;
		else
			is_auth = true;
	}
	bool getAuth() { return is_auth; }

	void setStartTime(clock_t start) {
		this->start = start;
	}
	void setEndTime(clock_t end) {
		this->end = end;
	}
	clock_t getStartTime() {
		return start;
	}
	clock_t getEndTime() {
		return end;
	}

	void setElapsedTime() {
		this->timeElapsed = (double(end - start) / CLOCKS_PER_SEC);
	}
	double getElapsedTime() {
		return this->timeElapsed;
	}
};

class Device { //Abstract Device class
protected:
	char  id[50] = { ' ' };
public:
	Device() {}
	void setId(string inputId) {
		for (int i = 0; i < 50; i++) {
			if (i < inputId.length()) {
				this->id[i] = inputId[i];
			}
			else if (i == inputId.length()) {
				this->id[i] = '\0';
			}
			else {
				this->id[i] = ' ';
			}
		
		}


	}
	string getId() {
		string tempString;
		for (int i = 0; i < 50; i++) {
			if (id[i] == '\0')
				break;
			tempString += id[i];
		}
		return tempString;
	}
	
};
class Computer : public Device {  //Computer class whcih extends Device class
	private:
		char key[50] = { ' ' };
public:
	Computer() {}
	void setKey(string inputKey) {
		for (int i = 0; i < 50; i++) {
			if (i < inputKey.length()) {
				this->key[i] = inputKey[i];
			}
			else if (i == inputKey.length()) {
				this->key[i] = '\0';
			}
			else {
				this->key[i] = ' ';
			}

		}


	}
	void setData(string id, string key) {
		setId(id); setKey(key);
	}
	void getData() {
		cout << "\t\t\t\t\t\tID :";
		for (int i = 0; i < 50; i++) {
			if (id[i] == '\0')
				break;
			cout << id[i];
		}
		cout << "\n\t\t\t\t\t\tKey : ";
		for (int i = 0; i < 50; i++) {
			if (key[i] == '\0')
				break;
			cout << "*";
		}
	}
	string getKey() {
		string tempString;
		for (int i = 0; i < 50; i++) {
			if (key[i] == '\0')
				break;
			tempString += key[i];
		}
		return tempString;
	}
};


//FUNCTIONS with Computer objects

//registration
void registerCompSaveFile(Computer obj) { //saving into file
	fstream compFile;
	if (!compFile.is_open()) {
		compFile.open("Compdata.txt", ios::app | ios::binary);
	}
	compFile.write((char*)&obj, sizeof(obj));
	compFile.close();
	system("cls");
	cout << "\n\n\n\n\t\t\t\t\tSuccessfully registered!\n";
}
bool checkIdUniqnessFromFile(string id) { //check uniqness of id
	ifstream in;
	in.open("Compdata.txt", ios::binary);
	Computer temp_file;
	while (in.read((char*)&temp_file, sizeof(temp_file))) {
		if (temp_file.getId() == id) {
			color(12);
			cout << "\n\t\t\t\tThis ID already registered!\n";
			color();
			return false;
		}
	}
	return true;
}
Computer registerNewComputerPanel() { //registering computer
	Computer tempObj, tempObjFile;
	string id, key, confirmKey;
	while (_kbhit()) _getch();
	bool apprId = false, apprKey = false, unique_id = true, confirmKeyBool =  true;
	color(11);
	cout << "\n\t\t\t\t\t Computer registration\n";
	color();
	ifstream in("Compdata.txt", ios::binary);
	while (!apprId) {
		while (unique_id) {
			color();
			id = input(id, "\n\t\t\t\tComputer id : ");
			if (checkIdUniqnessFromFile(id)) {
				unique_id = false;
			}
		}
		if (id.length() <= 50  && id.length() >= 3) { 
			apprId = true;
		}
		if(!apprId) {
			color(12);
			cout << "\n\t\t\t\tNot good ID!\n\t\t\t\t Should be less than 50 chararcters\n\t\t\t\t More than 3 characters\n\t\t\t\t Try again!\n";
			unique_id = true;
		}	
	}
	while (!apprKey) {
		while (confirmKeyBool) {
			color();
			key = askPassword("\n\t\t\t\tKey : ");
			confirmKey = askPassword("\t\t\t\tConfirm key : ");
			if (confirmKey == key) {
				confirmKeyBool = false;
			}
			else {
				color(12);
				cout << "\n\t\t\t\tKeys did not match! Try again\n";
				continue;
			}
		}
		
		if (key.length() <= 50 && key.length() >= 3) {
			apprKey = true;
		}
		if (!apprKey) {
			color(12);
			cout << "\n\t\t\t\tNot good Key!\n\t\t\t\t Should be less than 50 chararcters\n\t\t\t\t More than 3 characters\n\t\t\t\t Try again!\n";
			confirmKeyBool = true;
		}
	}

	if (apprId && apprKey) {
		tempObj.setData(id, key);
		registerCompSaveFile(tempObj);
		pressEsc();
		return tempObj;
	}

}

//other functionalitis
void showComputers(bool space = true) { //show all data
	if (space) {
		color(11);
		cout << "\n\n\t\t\t\t\t\tAll Computers\n";
		color();
	}
	ifstream in;
	Computer tempObj;
	in.open("Compdata.txt", ios::binary);
	for (int i = 1; in.read((char*)&tempObj, sizeof(tempObj)); i++) {
		cout << "\n\t\t\t\t\t\tComputer #" << i << endl;
		tempObj.getData();
		cout << "\n";
	}
	in.close();
	if (space) {
		color(12);
		pressEsc();
	}
}
//deleting
void deleteComputer() {  //delete specific computer from file
	color(11);
	cout << "\n\n\t\t\t\t\t\tDelete Computer\n";
	color();
	Computer tempObj, deletingObj;
	ifstream inFile; ofstream outFile;

	inFile.open("Compdata.txt", ios::binary);
	outFile.open("temp", ios::app | ios::binary);
	bool flag = false;

	showComputers(false);
	int choice = 0;
	while (_kbhit()) _getch();
	input(choice, "\t\t\t\t\tChoice:", "\n\t\t\t\t\tEnter the number of the computer\n"); //asking for number of member

	for (int i = 1; inFile.read((char*)&tempObj, sizeof(tempObj)); i++) {
		if (i == choice) {
			deletingObj = tempObj;
			flag = true;
			continue;
		}
		outFile.write((char*)&tempObj, sizeof(tempObj));
	}
	string key; bool confirm = true; int attempts = 0;
	while (confirm) {
		key = input(key, "\n\t\t\t\tKey : ", "\n\t\t\t\tEnter computer's key to delete");
		if (attempts == 5) {
			color(12);
			cout << "\n\t\t\t\tMax attempts was reached!\n";
			pressEsc();
			color();
			break;
		}
		if (deletingObj.getKey() == key) {
			inFile.close(); outFile.close();
			remove("Compdata.txt");
			rename("temp", "Compdata.txt");
			confirm = false;
			if (flag) {
				system("cls");
				cout << "\n\t\t\t\t\tComputers after deletion:\n";
				showComputers(false);
				cout << "\n\t\t\t\t\tComputer successfully deleted!\n";
				pressEsc();
			}
			else {
				color(12);
				cout << "\t\t\t\tCould not find this position, try again" << endl << endl;
				color();
			}
		}
		else {
			cout << "\n\t\t\t\tIncorrect key! Try again(" << (5 - attempts) << " attempts left)\n";
			attempts += 1;
			continue;
		}
	}


}
void deleteObjectComp(string id) { //deleting by id of computer
	Computer tempObj;
	ifstream inFile; fstream outFile("temp", ios::app | ios::binary);;
	inFile.open("Compdata.txt", ios::binary);
	int choice = 0;
	for (int i = 1; inFile.read((char*)&tempObj, sizeof(tempObj)); i++) {
		if (tempObj.getId() == id) {

			continue;
		}
		outFile.write((char*)&tempObj, sizeof(tempObj));
	}
	inFile.close(); outFile.close();

	remove("Compdata.txt");
	rename("temp", "Userdata.txt");
}
//updating
bool checkUpdateComputer(Computer profileToUpdate) {  //reregistering member by using all validations handlers
	Computer tempObj, tempObjFile;
	string id, key, confirmKey;
	while (_kbhit()) _getch();
	bool apprId = false, apprKey = false, unique_id = true, confirmKeyBool = true, noNewId = false, noNewKey = false;
	color(11);
	cout << "\n\t\t\t\t\tUpdate computer data\n";
	color();
	ifstream in("Compdata.txt", ios::binary);
	while (!apprId) {
		while (unique_id) {
			color();
			id = input(id, "\n\t\t\t\tNew computer id ( Input 0 if don't want to update ) : ");
			if (id == "0") {
				id = profileToUpdate.getId();
				noNewId = true;
				break;
			}
			if (checkIdUniqnessFromFile(id)) {
				unique_id = false;
			}
		}
		if (noNewId) {
			apprId = true;
			break;
		}
		if (id.length() <= 50 && id.length() >= 3) {
			apprId = true;
		}
		if (!apprId) {
			color(12);
			cout << "\n\t\t\t\tNot good ID!\n\t\t\t\t Should be less than 50 chararcters\n\t\t\t\t More than 3 characters\n\t\t\t\t Try again!\n";
			unique_id = true;
		}
	}
	while (!apprKey) {
		while (confirmKeyBool) {
			color();
			key = askPassword("\n\t\t\t\tNew key ( Input 0 if don't want to update ) : ");
			if (key == "0") {
				key = profileToUpdate.getKey();
				noNewKey = true;
				break;
			}
			confirmKey = askPassword("\t\t\t\tConfirm key : ");
			if (confirmKey == key) {
				confirmKeyBool = false;
			}
			else {
				color(12);
				cout << "\n\t\t\t\tKeys did not match! Try again\n";
				continue;
			}
		}
		if (noNewKey) {
			apprKey = true;
			break;
		}
		if (key.length() <= 50 && key.length() >= 3) {
			apprKey = true;
		}
		if (!apprKey) {
			color(12);
			cout << "\n\t\t\t\tNot good Key!\n\t\t\t\t Should be less than 50 chararcters\n\t\t\t\t More than 3 characters\n\t\t\t\t Try again!\n";
			confirmKeyBool = true;
		}
	}

	if (apprId && apprKey) {
		tempObj.setData(id, key);
		registerCompSaveFile(tempObj);
		return true;
	}
} //function for updateMember()
void updateFoundComputer(Computer objectToUpdate) {
	bool confirm = true, confirmOld = true;
	string newPass, oldPass;
	int attempts = 0;
	deleteObjectComp(objectToUpdate.getId());


	while (confirmOld) {
		color();
		oldPass = askPassword("\n\t\t\t\tKey : ", "\n\t\t\t\tEnter current key to update");
		if (attempts == 5) {
			color(12);
			cout << "\n\t\t\t\tMax attempts was reached!\n";
			break;
		}
		if (oldPass == objectToUpdate.getKey()) {

			if (!checkUpdateComputer(objectToUpdate)) {
				color(12);
				cout << "\n\t\t\t\tERROR while updating try again\n";
			}
			else {
				color(2);
				cout << "\n\t\t\t\tSuccess!\n";
			}


			system("cls");
			color(11);
			cout << "\n\t\t\t\t\tComputers after update\n";
			color();
			showComputers(false);

			pressEsc();
			confirmOld = false;
			break;
		}
		else {
			color(12);
			cout << "\n\t\t\t\tIncorrect! Try again(" << (5 - attempts) << " attempts left)\n";
			attempts += 1;
			continue;
		}

	}
}
void updateComputer() {  //updating member by asking login and password

	color(11);
	cout << "\n\t\t\t\t\t  Update Computer\n";
	color();

	ifstream in;
	in.open("Compdata.txt", ios::binary);
	Computer tempObj, objectToUpdate;
	string id;

	cin.clear();
	while (_kbhit()) _getch();

	id = input(id, "\n\t\t\t\tId: ", "\n\t\t\t\tEnter ID of computer to update");
	bool success = false;
	for (int i = 1; in.read((char*)&tempObj, sizeof(tempObj)); i++) {
		if (tempObj.getId() == id) {
			objectToUpdate = tempObj;
			success = true;
			break;
		}
	}

	in.close();

	if (success) {
		updateFoundComputer(objectToUpdate);
	}
	else {
		color(12);
		cout << "\n\t\t\t\tCould not find such computer\n";
	}
}
//searching
void searchComputer() {  //searching and doing something with found object
	color(11);
	cout << "\n\n\t\t\t\t\t  Search Computer\n";
	color();
	cin.clear();
	string searchId = ""; char choice = 'q';
	searchId = input(searchId, "\n\t\t\t\tId :", "\n\n\t\t\t\tPlease, enter the id of computer to search among others\n");
	ifstream inFile; Computer temp, found; bool flag = true;
	inFile.open("Compdata.txt", ios::binary);

	while (inFile.read((char*)&temp, sizeof(temp))) {
		if (searchId == temp.getId()) {
			found = temp;
			flag = false;
		}
	}
	inFile.close();
	if (flag) {
		color(12);
		cout << "\n\t\t\t\tUnfortunately, there is no such as computer\n";
		pressEsc();
	}
	else {

		while (choice != 'E') {
			system("cls");
			color(2);
			cout << "\n\t\t\t\t\tFound!\n";
			color(15);
			cout << "\n\t\t\t\tEnter (U) to update record\n";
			cout << "\t\t\t\tEnter (I) to inspect record\n";
			cout << "\t\t\t\tEnter (D) to delete record\n";
			cout << "\t\t\t\tEnter (E) to exit\n";
			choice = input(choice, "\t\t\t\tChoice: ");
			switch (choice) {
			case 'I': {
				cout << "\n";
				found.getData();
				pressEsc();
				break;
			}
			case 'D': {
				deleteObjectComp(searchId);
				cout << "\n\t\t\t\tDeleted!";
				Sleep(2000);
				choice = 'E';
				break;
			}
			case 'U': {
				updateFoundComputer(found);
				break;
			}
			case 'E': {
				break;
			}
			default: {
				cout << "\n\t\t\t\tTry again!";
				break;
			}
			}

		}
	}
}



//FUNCTIONS with Member objects


//registration
void registerMemberSaveFile(Member user) { //saving new member to the txt file
	fstream userFile;
	if (!userFile.is_open()){
		userFile.open("Userdata.txt", ios::app| ios::binary);
	}
	userFile.write((char*)&user, sizeof(user));
	userFile.close();
}
bool checkLoginUniqnessFromFile(string item) { //checking uniqness of login
	ifstream in;
	in.open("Userdata.txt", ios::binary);
	Member temp_file;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	while (in.read((char*)&temp_file, sizeof(temp_file))) {
		if (temp_file.getLogin() == item) {
			cout << "\t\t\t\tThis account already registered!";
			return false;
		}
	}
	return true;
}
Member registerNewMemberPanel() {  //registering new member using all validation handlers

	Member temp_obj, for_file;
	string password, confirmPassword, email, login;
	bool appr_login = false, appr_password = false, appr_email = false, unique_login = true, confirmPass = true;
	color(11);
	cout << "\n\n\t\t\t\t\t Registration\n";
	while (_kbhit()) _getch();
	while (!appr_login) {
		while (unique_login) {
			color();
			login = input(login, "\n\t\t\t\tLogin : ");
			if (checkLoginUniqnessFromFile(login)) {
				unique_login = false;
			}
		}
		if (login.length() <= 20 && login.length() >= 3) {
			appr_login = true;
			continue;
		}
		if (!appr_login) {
			color(12);
			cout << "\n\t\t\t\tNot good login!\n\t\t\t\t Should be less than 20 chararcters\n\t\t\t\t More than 3 characters\n\t\t\t\t Try again!\n";
			unique_login = true;
			continue;
		}

	}
	while (!appr_password) {
		while (confirmPass) {
			color(15);
			password = askPassword("\t\t\t\tPassword : ");
			confirmPassword = askPassword("\t\t\t\tConfirm password : ");
			if (confirmPassword == password) {
				confirmPass = false;
			}
			else {
				color(12);
				cout << "\n\n\t\t\t\tPasswords did not match! Try again\n";

				continue;
			}
		}


		if (password.length() <= 14 && password.length() >= 6) {
			appr_password = true;
			continue;
		}
		if (!appr_password) {
			color(12);
			cout << "\n\n\t\t\t\tNot good password!\n\t\t\t\t Should be less than 14 chararcters\n\t\t\t\t More than 6 characters\n\t\t\t\t Try again!\n";
			appr_password = false;
			confirmPass = true;
			continue;
		}
	}

	
	while (!appr_email) {
		color();
		email = input(email, "\n\n\t\t\t\tEmail : ");
		if ((email.find("@") != std::string::npos) && (email.find(".") != std::string::npos)) {
			if (email.length() <= 30 && email.length() >= 6) {
				appr_email = true;
				continue;
			}
		}
		if (!appr_email) {
			color(12);
			cout << "\n\n\t\t\t\tNot good email!\n\t\t\t\tShould be less than 30 chararcters\n\t\t\t\tMore than 6 characters\n\t\t\t\tSould contain '@' and '.'\n\t\t\t\t Try again!\n";
			continue;
		}
	}
	if (appr_email && appr_login && appr_password) {
		temp_obj.setData(login, password, email);
		registerMemberSaveFile(temp_obj);
		system("cls");
		cout << "\n\n\n\n\n\n\n\n\t\t\t\t\tSuccessfully registered!\n";
		pressEsc();
		return temp_obj;
	}
	
}

//other functionality

void showMembers(bool space = true) {  //displaying all members from the file
	if (space) {
		color(11);
		cout << "\n\n\t\t\t\t\t  All Members\n";
		color();
	}
	ifstream in;
	Member tempObj;
	in.open("Userdata.txt", ios::binary);
	for (int i = 1; in.read((char*)&tempObj, sizeof(tempObj)); i++) {
		cout << "\n\t\t\t\t\t  Member #" << i << endl;
		tempObj.getData();
		cout << "\n";
	}
	in.close();
	if (space) {
		color(12);
		pressEsc();
	}

}
//deleting
void deleteObject(string login) {  //deleting member by its login
	Member tempObj;
	ifstream inFile; fstream outFile("temp", ios::app | ios::binary);;
	inFile.open("Userdata.txt", ios::binary);
	int choice = 0;
	for (int i = 1; inFile.read((char*)&tempObj, sizeof(tempObj)); i++) {
		if (tempObj.getLogin() == login) {

			continue;
		}
		outFile.write((char*)&tempObj, sizeof(tempObj));
	}
	inFile.close(); outFile.close();

	remove("Userdata.txt");
	rename("temp", "Userdata.txt");
}
void deleteMember() {  //deleting object by asking the number of the object
	Member tempObj;
	color(11);
	cout << "\n\t\t\t\t\t  Delete Member\n";
	color();

	ifstream inFile("Userdata.txt", ios::binary);; fstream outFile("temp123.txt", ios::app | ios::binary);;
	showMembers(false);
	bool flag = false; int choice = 0;

	while (_kbhit()) _getch();
	
	cout << "\n\t\tEnter the number of the member : ";
	checkValidation(choice);
	for (int i = 1; inFile.read((char*)&tempObj, sizeof(tempObj)); i++) {
		if (i == choice) {
			flag = true;
			continue;
		}
		outFile.write((char*)&tempObj, sizeof(tempObj));
	}
	inFile.close(); outFile.close();

	remove("Userdata.txt");
	rename("temp123.txt", "Userdata.txt");
	if (flag) {
		color(2);
		cout << "\n\t\tMember successfully deleted!\n";
	}
	else if (!flag) {
		color(12);
		cout << "\n\t\tCould not find this position, try again" << endl << endl;
	}
	pressEsc();
}
//updating member ( changing everything of a member(login ,password, email) and resaving )
bool checkUpdateMember(Member profileToUpdate) {  //reregistering member by using all validations handlers
	string newLogin, newEmail, newPassword, confirmPassword;
	bool appr_login = false, appr_password = false, appr_email = false, unique_login = true, confirmPass = true, noNewLogin = false, noNewPass = false;
	color(11);
	cout << "\n\t\t\t\t\tUpdate profile\n";
	color();
	while (!appr_login) {
		color();
		while (unique_login) {
			newLogin = input(newLogin, "\n\t\t\t\tNew login( Input 0 if do not want to update ) : ");
			if (newLogin == "0") {
				newLogin = profileToUpdate.getLogin();
				noNewLogin = true;
				break;
			}
			if (checkLoginUniqnessFromFile(newLogin)) {
				unique_login = false;
			}
		}
		if (noNewLogin) {
			appr_login = true;
			break;
		}
		if (newLogin.length() <= 20 && newLogin.length() >= 3) {
			appr_login = true;
			continue;
		}
		if (!appr_login) {
			color(12);
			cout << "\n\t\t\t\tNot good login!\n\t\t\t Should be less than 20 chararcters\n\t\t\t\t More than 3 characters\n\t\t\t\t Try again!\n";
			unique_login = true;
			continue;
		}

	}
	while (!appr_password) {
		color();
		while (confirmPass) {
			color();
			newPassword = askPassword("\n\t\t\t\tNew password( Input 0 if don't want to update ) : ");
			if (newPassword == "0") {
				newPassword = profileToUpdate.getPassword();
				noNewPass = true;
				break;
			}
			confirmPassword = askPassword("\t\t\t\tConfirm password : ");
			if (confirmPassword == newPassword) {
				confirmPass = false;
			}
			else {
				color(12);
				cout << "\n\t\t\t\tPasswords did not match! Try again\n";
				continue;
			}
		}
		if (noNewPass) {
			appr_password = true;
			break;
		}
		if (newPassword.length() <= 14 && newPassword.length() >= 6) {
			appr_password = true;
			continue;
		}
		if (!appr_password) {
			color(12);
			cout << "\n\t\t\t\tNot good password!\n\t\t\t\t Should be less than 14 chararcters\n\t\t\t\t More than 6 characters\n\t\t\t\t Try again!\n";
			confirmPass = true;
			continue;
		}
	}
	while (!appr_email) {
		color();
		newEmail = input(newEmail, "\n\n\t\t\t\tNew email( Input 0 if don't want to update ) : ");
		if (newEmail == "0") {
			newEmail = profileToUpdate.getEmail();
			appr_email = true;
			continue;
		}
		if ((newEmail.find("@") != std::string::npos) && (newEmail.find(".") != std::string::npos)) {
			if (newEmail.length() <= 30 && newEmail.length() >= 6) {
				appr_email = true;
				continue;
			}
		}
		if (!appr_email) {
			color(12);
			cout << "\n\t\t\t\tNot good email!\n\t\t\t\tShould be less than 30 chararcters\n\t\t\t\tMore than 6 characters\n\t\t\t\tSould contain '@' and '.'\n\t\t\t\t Try again!\n";
			continue;
		}
	}
	if (appr_login && appr_email && appr_password) {
		if (profileToUpdate.getAuth()) {
			profileToUpdate.changeAuth();
		}
		profileToUpdate.setData(newLogin, newPassword, newEmail);
		registerMemberSaveFile(profileToUpdate);
		return true;
	}
} //function for updateMember()
void updateFoundMember(Member objectToUpdate, bool show = true) { //updates found member (abstract function)
	bool confirm = true, confirmOld = true;
	string newPass, oldPass;
	int attempts = 0;
	deleteObject(objectToUpdate.getLogin());


	while (confirmOld) {
		color();
		oldPass = askPassword("\n\t\t\t\tPassword : ", "\n\t\t\t\tEnter current password to update");
		if (attempts == 5) {
			color(12);
			cout << "\n\t\t\t\tMax attempts was reached!\n";
			break;
		}
		if (oldPass == objectToUpdate.getPassword()) {

			if (!checkUpdateMember(objectToUpdate)) {
				color(12);
				cout << "\n\t\t\t\tERROR while updating try again\n";
			}
			else {
				color(2);
				cout << "\n\t\t\t\tSuccess!\n";
			}

			if (show) {
			system("cls");
			color(11);
			cout << "\n\t\t\t\t\tMembers after update\n";
			color();
			
				showMembers(false);
			}
				

			pressEsc();
			confirmOld = false;
			break;
		}
		else {
			color(12);
			cout << "\n\t\t\t\tIncorrect! Try again(" << (5 - attempts) << " attempts left)\n";
			attempts += 1;
			continue;
		}

	}

}
void updateMember() {  //updating member by asking login and password

	color(11);
	cout << "\n\t\t\t\t\t  Update Member\n";
	color();

	ifstream in;
	in.open("Userdata.txt", ios::binary);
	Member tempObj, objectToUpdate;
	string login; int objectNumber;

	cin.clear();
	while (_kbhit()) _getch();

	login = input(login, "\n\t\t\t\tLogin: ", "\n\t\t\t\tEnter Login of member to update");
	bool success = false;
	for (int i = 1; in.read((char*)&tempObj, sizeof(tempObj)); i++ ) {
		if (tempObj.getLogin() == login) {
			objectToUpdate = tempObj;
			objectNumber = i;
			success = true;
			break;
		}
	}

	in.close();

	if (success) {
		updateFoundMember(objectToUpdate);
	}
	else {
		color(12);
		cout << "\n\t\t\t\tCould not find such member\n";
	}
}
//searching
void searchMember() {  //searching member and doing some actions with found member
	color(11);
	cout << "\n\n\t\t\t\t\t  Search Member\n";
	color();
	cin.clear();
	string searchLogin; char choice = 'q';
	while (_kbhit()) _getch();
	searchLogin = input(searchLogin, "\n\t\t\t\tLogin :", "\n\n\t\t\t\tPlease, enter the login to search among others\n");
	ifstream inFile; Member temp, found; bool flag = true;
	inFile.open("Userdata.txt", ios::binary);

	while (inFile.read((char*)&temp, sizeof(temp))) {
		if (searchLogin == temp.getLogin()) {
			flag = false;
			found = temp;
			break;
		}
	}
	inFile.close();
	if (flag) {
		color(12);
		cout << "\n\t\t\t\tUnfortunately, there is no such as member\n";
		pressEsc();
	}
	else {

		while (choice != 'E') {
			system("cls");
			color(2);
			cout << "\n\t\t\t\t\tFound!\n";
			color(15);
			cout << "\n\t\t\t\tEnter (U) to update record\n";
			cout << "\t\t\t\tEnter (I) to inspect record\n";
			cout << "\t\t\t\tEnter (D) to delete record\n";
			cout << "\t\t\t\tEnter (E) to exit\n";
			choice = input(choice, "\t\t\t\tChoice: ");
			switch (choice) {
			case 'I': {
				cout << "\n";
				found.getData();
				pressEsc();
				break;
			}
			case 'D': {
				deleteObject(searchLogin);
				cout << "\n\t\t\t\tDeleted!";
				Sleep(2000);
				choice = 'E';
				break;
			}
			case 'U': {
				updateFoundMember(found);
				break;
			}
			case 'E': {
				break;
			}
			default: {
				cout << "\n\t\t\t\tTry again!";
				break;
			}
			}

		}
	}
}

//LOGGING / CHARGING
Member onlineMember; //GLOBAL member object for manipulation with all online object
//log in/out panels
Member logIn(Member objInput) {  //log in of member
	ifstream user_data;
	Member users; bool flag = false;
	user_data.open("Userdata.txt", ios::binary);
	while (user_data.read((char*)&users, sizeof(users))) {
		if (objInput.getLogin() == users.getLogin() && objInput.getPassword() == users.getPassword()) {
			users.changeAuth();
			users.setStartTime(clock());
			flag = true;
			return users;
		}
	}
	if (!flag) {
		return objInput;
	}
	
	//while (user_data) {

	//}
}
void logOut() { //exits the cafe and sets elapsed time
	if (onlineMember.getAuth()) {
		onlineMember.changeAuth();
	}	
	onlineMember.setEndTime(clock());
	onlineMember.setElapsedTime();
	color(12);
	cout << "\n\n\n\n\t\t\t\t\tCOME BACK SOON " << onlineMember.getLogin() << "\n";
	color(0);
	
}
bool loginAdminPanel() {   //admin log in
	string temp_login = "", temp_pass = "";
	Member temp_user;
	int attempts = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "\n\n\n\n\t\t\t\t\tAdmin Log-in\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	while (true) {
		if (attempts == 3) {
			return false;
		}
		while (_kbhit()) _getch();;
		temp_login = input(temp_login, "\n\t\t\t\t\tLogin : ");
		temp_pass = askPassword("\t\t\t\t\tPassword : ");
		if (temp_login == "admin" && temp_pass == "admin") {
			return true;
		}
			
		attempts += 1;
	}
	

}
Member loginMemberPanel() {   //admin log in
	string temp_login = "", temp_pass = "";
	Member temp_user;
	int attempts = 0;
	color(12);
	cout << "\n\n\n\n\t\t\t\t\t   Member Log-in\n";
	color(7);
	cout << "\t\t(Ask Administrator to register you if you are not registered yet)\n";
	cout << "\t\t\t\t(Enter 0 if you are not registered)\n";
	color();
	while (true) {
		
		if (attempts == 3) {
			color(12);
			cout << "\n\n\t\t\t\t\tMax attemps reached\n";
			return  logIn(temp_user);
		}
		while (_kbhit()) _getch();
		temp_login = input(temp_login, "\n\n\t\t\t\t\tLogin : ");
		if (temp_login == "0") {
			break;
		}
		temp_pass = askPassword("\t\t\t\t\tPassword : ");
		temp_user.setData(temp_login, temp_pass, "");
		if (logIn(temp_user).getAuth()) {
			return logIn(temp_user);
		}
		attempts += 1;
		
	}
	

}
//charging
void takeCharges(Member objectInput) {//taking charges by logging out
	color(12);
	cout << "\n\n\t\t\t\t\tTaking charges\n";
	color();
	while (_kbhit()) _getch();
	char inputStr = input(inputStr, "\n\t\t\t\tChoice : ", "\n\t\t\t\tYou have to log out to take charges (Y)es or (N)o");
	switch (inputStr) {
	case 'Y': {
		cout << "\n\t\t\t\t\tYou logged out!\n";
		logOut();
		double elapsedTime = onlineMember.getElapsedTime();
		double shouldPay = (elapsedTime / 3600 * 2);
		color(2);
		cout << "\n\t\t\t\tYou were online : " << elapsedTime / 60 << " minutes\n";
		cout << "\n\t\t\t\tYou should pay : " << shouldPay << "$ ( 2$ for 1 hour)\n";
		color();
		pressEsc();
		break;
	}
	case 'N': {
		Booking();
		break;
	}
	default:
	{
		color(12);
		cout << "\n\t\t\t\tIncorrect input!\n";
		break;
	}
	}
}
void showCharges(Member objectInput) {//taking charges by logging out
	color(12);
	cout << "\n\n\t\t\t\t\tShowing charges\n";
	color();
	clock_t TEMP_TIME_END = clock();
	clock_t TEMP_TIME_START = objectInput.getStartTime();
	double timeElapsed = (double(TEMP_TIME_END - TEMP_TIME_START) / CLOCKS_PER_SEC);
	double shouldPay = (timeElapsed / 3600 * 2);
	cout << "\n\t\t\t\tYou are online : " << timeElapsed / 60 << " minutes\n";
	cout << "\n\t\t\t\tYou should pay : " << shouldPay << "$  (2 $ for 1 hour)\n";
	pressEsc();	
}

//functions for specific member
void showProfile() {
	color(11);
	cout << "\n\n\n\t\t\t\t\tYour profile - " << onlineMember.getLogin() << "\n\n";
	color();
	onlineMember.getData();
	pressEsc();
}
void UpdateProfile() {
	color(11);
	cout << "\n\n\n\t\t\t\t\t  Update profile";
	color(12);
	cout << "\n\t\t\t\t(Please, do NOT LEAVE while updating)";
	cout << "\n\t\t\t(Your current profile was deleted from database but your data is safe) \n\n";
	color();
	updateFoundMember(onlineMember, false);
}

 

//MENUS

//main menu
void mainMenu() { 
	Sleep(200);
	int pointer = 0;
	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout << "\n\n\n\n\n";
		display_text_no_ping(menu_headers[0], 12);
		for (int i = 0; i < 3; i++) {
			if (i == pointer)
			{
				display_text_no_ping(Main_menu[i], 2);
			}
			else if (i == pointer - 1 || pointer + 1)
			{
				display_text_no_ping(Main_menu[i], 15);
			}

			else if (i == pointer - 2 || pointer + 2)
			{
				display_text_no_ping(Main_menu[i], 15);
			}
		}
		while (true) {
			if (GetAsyncKeyState(VK_UP) != 0) 
			{
				pointer -= 1; 
				if (pointer == -1)
				{
					pointer = 2;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer += 1;
				if (pointer == 1)
				{
					pointer = 1;
				}
				if (pointer == 3)
				{
					pointer = 0;
				}
				break;
			}
			else if ((GetAsyncKeyState(VK_ESCAPE) != 0))
			{
				exit(1);
				Sleep(150);
			}
			else if (GetAsyncKeyState(VK_SPACE) != 0)
			{
				switch (pointer)
				{
				case 0:
				{
					system("cls");
					if (loginAdminPanel()) {
						adminMenuPanel();
					}
					else {
						mainMenu();
					}
					
				}
				break;
				case 1:
				{
					system("cls");
					cafeManagement();
					Sleep(2000);
					adminMenuPanel();
				}
				break;
				case 2:
				{
					exit(1);
				}
				break;
				}

			}

		}
		Sleep(150);
	}
}
//for admin
void adminMenuPanel()
{
		Sleep(200);
		int pointer = 0;
		while (true)
		{
			system("cls");

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << "\n\n\n\n\n";
			display_text_no_ping(menu_headers[1], 12);
			for (int i = 0; i < 3; ++i)
			{
				if (i == pointer)
				{

					display_text_no_ping(admin_menu[i], 2);
				}
				else if (i == pointer - 1 || pointer + 1)
				{
					display_text_no_ping(admin_menu[i], 15);
				}

				else if (i == pointer - 2 || pointer + 2)
				{
					display_text_no_ping(admin_menu[i], 15);
				}

			}
			while (true && GetConsoleWindow() == GetForegroundWindow())
			{
				if (GetAsyncKeyState(VK_UP) != 0) // åñëè ââåðõ íå false òèïà åñëè òû íàæàë íà íåãî òî ...
				{
					pointer -= 1; // òî ïîèíòåð ïîëó÷èòüñÿ -1 òèïà íåòó èíäåêñà -1 ïîýòîìó
					if (pointer == -1)
					{
						pointer = 2;
					}
					break;
				}
				else if (GetAsyncKeyState(VK_DOWN) != 0)
				{
					pointer += 1;
					if (pointer == 1) //êàê ñþäà äîáàâèòü òðåòóþ ïðîâåðêó ëîãèêó àãà çäåñü òîëüêî 1 è 0 íàì íóæíî åùå 2
					{
						pointer = 1;
					}
					if (pointer == 3)
					{
						pointer = 0;
					}
					break;
				}
				else if ((GetAsyncKeyState(VK_ESCAPE) != 0))
				{
					mainMenu();
					Sleep(150);
				}
				else if (GetAsyncKeyState(VK_SPACE) != 0)
				{
					switch (pointer)
					{
					case 0:
					{
						system("cls");
						Sleep(200);
						memberEntryPanel();
						break;
					}
					case 1:
					{
						system("cls");
						computerEntryPanel();
						break;
					}
					case 2:
					{
						mainMenu();
						break;
					}
					}
					break;

				}

			}

			Sleep(150);
		}
	
}
void memberEntryPanel() {
	system("cls");
	Sleep(150);
	int pointer1 = 0;
	while (true) {
		system("cls");
		color(12);
		cout << "\n\n\n\n\n";
		display_text_no_ping(menu_headers[2], 12);

		for (int i = 0; i < 6; ++i)
		{
			if (i == pointer1)
			{
				display_text_no_ping(member_menu[i], 2);
			}
			else if (i == pointer1 - 1 || pointer1 + 1)
			{
				display_text_no_ping(member_menu[i], 15);
			}
			else if (i == pointer1 - 2 || pointer1 + 2)
			{
				display_text_no_ping(member_menu[i], 15);
			}
			else if (i == pointer1 - 3 || pointer1 + 3)
			{
				display_text_no_ping(member_menu[i], 15);
			}
			else if (i == pointer1 - 4 || pointer1 + 4)
			{
				display_text_no_ping(member_menu[i], 15);
			}
			else if (i == pointer1 - 5 || pointer1 + 5)
			{
				display_text_no_ping(member_menu[i], 15);
			}
		}

		while (true && GetConsoleWindow() == GetForegroundWindow()) {
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer1 -= 1;
				if (pointer1 == -1)
				{
					pointer1 = 5;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer1 += 1;
				if (pointer1 == 1)
				{
					pointer1 = 1;
				}
				if (pointer1 == 6)
				{
					pointer1 = 0;
				}
				break;
			}
			else if ((GetAsyncKeyState(VK_ESCAPE) != 0))
			{
				adminMenuPanel();
				Sleep(150);
			}
			else if (GetAsyncKeyState(VK_SPACE) != 0)
			{
				switch (pointer1)
				{

				case 0: {
					system("cls");
					registerNewMemberPanel();
					Sleep(1500);
					memberEntryPanel();



					break;
				}

				case 1:
				{
					system("cls");
					showMembers();
					Sleep(1500);
					memberEntryPanel();
					break;

				}

				case 2:
				{
					system("cls");
					deleteMember();
					Sleep(1500);
					memberEntryPanel();
					break;

				}

				case 3:
				{
					system("cls");
					searchMember();
					Sleep(1500);

					memberEntryPanel();
					break;
				}

				case 4: {
					system("cls");
					updateMember();
					Sleep(1500);

					memberEntryPanel();
					break;
				}
					  break;
				case 5: {
					adminMenuPanel();
					break;
				}
				}

			}

		}
		Sleep(150);
	}


}
void computerEntryPanel() {
	Sleep(150);
	int pointer1 = 0;
	while (true) {
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout << "\n\n\n\n\n";
		display_text_no_ping(menu_headers[3], 12);

		for (int i = 0; i < 6; ++i)
		{
			if (i == pointer1)
			{
				display_text_no_ping(computer_menu[i], 2);
			}
			else if (i == pointer1 - 1 || pointer1 + 1)
			{
				display_text_no_ping(computer_menu[i], 15);
			}
			else if (i == pointer1 - 2 || pointer1 + 2)
			{
				display_text_no_ping(computer_menu[i], 15);
			}
			else if (i == pointer1 - 3 || pointer1 + 3)
			{
				display_text_no_ping(computer_menu[i], 15);
			}
			else if (i == pointer1 - 4 || pointer1 + 4)
			{
				display_text_no_ping(computer_menu[i], 15);
			}
			else if (i == pointer1 - 5 || pointer1 + 5)
			{
				display_text_no_ping(computer_menu[i], 15);
			}
		}

		while (true) {
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer1 -= 1;
				if (pointer1 == -1)
				{
					pointer1 = 5;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer1 += 1;
				if (pointer1 == 1)
				{
					pointer1 = 1;
				}
				if (pointer1 == 6)
				{
					pointer1 = 0;
				}
				break;
			}
			else if ((GetAsyncKeyState(VK_ESCAPE) != 0))
			{

				Sleep(150);
			}
			else if (GetAsyncKeyState(VK_SPACE) != 0)
			{
				switch (pointer1)
				{

				case 0: {
					system("cls");
					registerNewComputerPanel();
					Sleep(2000);
					computerEntryPanel();
					break;
				}

				case 1:
				{
					system("cls");
					showComputers();
					Sleep(2000);
					computerEntryPanel();
					break;

				}

				case 2:
				{
					system("cls");
					deleteComputer();
					Sleep(2000);
					computerEntryPanel();
					break;
				}

				case 3:
				{
					system("cls");
					searchComputer();
					Sleep(2000);
					computerEntryPanel();
					;					break;
				}

				case 4: {
					system("cls");
					updateComputer();
					Sleep(2000);
					computerEntryPanel();
					break;
				}
				case 5: {
					adminMenuPanel();
					break;
				}
					  break;
				}

			}

		}
		Sleep(150);
	}


}
//for members
void cafeManagement() {
	Sleep(200);
	int pointer = 0;
	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout << "\n\n\n\n\n";
		display_text_no_ping(menu_headers[4], 12);
		for (int i = 0; i < 3; i++) {
			if (i == pointer)
			{
				display_text_no_ping(cafe_management[i], 2);
			}
			else if (i == pointer - 1 || pointer + 1)
			{
				display_text_no_ping(cafe_management[i], 15);
			}

			else if (i == pointer - 2 || pointer + 2)
			{
				display_text_no_ping(cafe_management[i], 15);
			}
		}
		while (true) {
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 2;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer += 1;
				if (pointer == 1)
				{
					pointer = 1;
				}
				if (pointer == 3)
				{
					pointer = 0;
				}
				break;
			}
			else if ((GetAsyncKeyState(VK_ESCAPE) != 0))
			{
				exit(1);
				Sleep(150);
			}
			else if (GetAsyncKeyState(VK_SPACE) != 0)
			{
				switch (pointer)
				{
				case 0:
				{
					system("cls");
					Booking();
					Sleep(2000);
					cafeManagement();
					break;
				}
				break;
				case 1:
				{
					system("cls");
					if (onlineMember.getAuth()) {//if user logged in
						Charges();
					}
					else { //display that user not logged in yet 
						color(12);
						cout << "\n\n\n\t\t\t\tYou are not logged in yet!\n";
						color();
					}
					Sleep(2000);
					cafeManagement();
					break;
				}
				break;
				case 2:
				{
					mainMenu();
					break;
				}
				break;
				}

			}

		}
		Sleep(150);
	}
}
void Booking() {
	Sleep(200);
	int pointer = 0;
	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout << "\n\n\n\n\n";
		display_text_no_ping(menu_headers[5], 12);
		for (int i = 0; i < 3; i++) {
			if (i == pointer)
			{
				display_text_no_ping(booking[i], 2);
			}
			else if (i == pointer - 1 || pointer + 1)
			{
				display_text_no_ping(booking[i], 15);
			}

			else if (i == pointer - 2 || pointer + 2)
			{
				display_text_no_ping(booking[i], 15);
			}
		}
		while (true) {
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 2;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer += 1;
				if (pointer == 1)
				{
					pointer = 1;
				}
				if (pointer == 3)
				{
					pointer = 0;
				}
				break;
			}
			else if ((GetAsyncKeyState(VK_ESCAPE) != 0))
			{
				cafeManagement();
				Sleep(150);
			}
			else if (GetAsyncKeyState(VK_SPACE) != 0)
			{
				switch (pointer)
				{
				case 0:
				{
					system("cls");
					if (onlineMember.getAuth()) { //if user logged in and return to log-in again
						system("cls");
						specificMemberMenu();
						
					}
					else {
						onlineMember = loginMemberPanel(); //logging-in user
						if (onlineMember.getAuth()) {
							system("cls");
							specificMemberMenu();
						}
						else {
							color(12);
							cout << "\n\n\n\n\t\t\t\tIncorrect login or password try again!";
							color();
						}
					}
					
					Sleep(2000);
					Booking();
					break;
				}
				break;
				case 1:
				{
					system("cls");
					if(onlineMember.getAuth()){//if user logged in then log out
						logOut();
						cout << "\n\t\t\t\t\tYou logged out!\n";
						double elapsedTime = onlineMember.getElapsedTime();
						double shouldPay = (elapsedTime / 3600 * 2);
						color(2);
						cout << "\n\t\t\t\tYou were online : " << elapsedTime / 60 << " minutes\n";
						cout << "\n\t\t\t\tYou should pay : " << shouldPay << "$ ( 2$ for 1 hour)\n";
						color();
						pressEsc();
					}
					else { //display that user not logged in yet 
						color(12);
						cout << "\n\n\n\t\t\t\t\tYou are not logged in yet!\n";
						color();
					}
					Sleep(2000);
					Booking();
					break;
				}
				break;
				case 2:
				{
					cafeManagement();
					break;
				}
				break;
				}

			}

		}
		Sleep(150);
	}
}
void Charges() {
	Sleep(200);
	int pointer = 0;
	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout << "\n\n\n\n\n";
		display_text_no_ping(menu_headers[6], 12);
		for (int i = 0; i < 3; i++) {
			if (i == pointer)
			{
				display_text_no_ping(charges[i], 2);
			}
			else if (i == pointer - 1 || pointer + 1)
			{
				display_text_no_ping(charges[i], 15);
			}

			else if (i == pointer - 2 || pointer + 2)
			{
				display_text_no_ping(charges[i], 15);
			}
		}
		while (true) {
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 2;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer += 1;
				if (pointer == 1)
				{
					pointer = 1;
				}
				if (pointer == 3)
				{
					pointer = 0;
				}
				break;
			}
			else if ((GetAsyncKeyState(VK_ESCAPE) != 0))
			{
				cafeManagement();
				Sleep(150);
			}
			else if (GetAsyncKeyState(VK_SPACE) != 0)
			{
				switch (pointer)
				{
				case 0:
				{
					system("cls");
					takeCharges(onlineMember);
					Sleep(2000);
					Booking(); 
					break; 
				}
				break;
				case 1:
				{
					system("cls");
					showCharges(onlineMember);
					Sleep(2000);
					Charges();
					break;
				}
				break;
				case 2:
				{
					cafeManagement();
					break;
				}
				break;
				}

			}

		}
		Sleep(150);
	}
}

void specificMemberMenu() {
	Sleep(200);
	int pointer = 0;
	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout << "\n\n\n\n\n";
		string menu = "\t Hello " + onlineMember.getLogin();
		display_text_no_ping(menu, 12);
		for (int i = 0; i < 3; i++) {
			if (i == pointer)
			{
				display_text_no_ping(specific_member_menu[i], 2);
			}
			else if (i == pointer - 1 || pointer + 1)
			{
				display_text_no_ping(specific_member_menu[i], 15);
			}

			else if (i == pointer - 2 || pointer + 2)
			{
				display_text_no_ping(specific_member_menu[i], 15);
			}
		}
		while (true) {
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 2;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer += 1;
				if (pointer == 1)
				{
					pointer = 1;
				}
				if (pointer == 3)
				{
					pointer = 0;
				}
				break;
			}
			else if ((GetAsyncKeyState(VK_ESCAPE) != 0))
			{
				Booking();
				Sleep(150);
			}
			else if (GetAsyncKeyState(VK_SPACE) != 0)
			{
				switch (pointer)
				{
				case 0:
				{
					system("cls");
					showProfile();
					Sleep(2000);
					specificMemberMenu();
					break;
				}
				break;
				case 1:
				{
					system("cls");
					UpdateProfile();
					Sleep(2000);
					specificMemberMenu();
					break;
				}
				break;
				case 2:
				{
					Booking();
					break;
				}
				break;
				}

			}

		}
		Sleep(150);
	}
}





int main()
{
	mainMenu();
	system("pause");
	return 0;
}
