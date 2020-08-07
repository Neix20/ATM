#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<cctype>
#include<ctime>
#include<cstdlib>
#include<conio.h>//Must remove
using namespace std;

struct person {
	string accountNumber, PIN;
	string name;
	double balance;
};

struct rTime {
	string date, time;
	int day, month, year, hour, minute, second;
};

struct transaction {
	person cus;
	rTime rec;
	double amount;
	string status, tName, tAccNum;
};

person customer[1000];
int numOfCustomer;
int numOfTransactionRecord(0);
transaction transCus[3000];

int homepage();
void print(person, ostream&);
bool readfile(string);
void printFile(string);
bool login(int&);
void menu(int);
void checkBalance(int);
bool depositAmount(int);
bool withdrawAmount(int);
bool transferAmount(int);
void printTransaction(int, int, double, ostream&);
bool readTransaction();
void printTransactionDetails(transaction, ostream&);

void centerText(string);
void centerText2(string);
void drawLine();
void PIN_checker(string&);
bool digit_validator(string&);
void calculate_date(rTime&);
void printTime(rTime, ostream&);
void split_string(string, string [], int, char);
void printTimeInLine(ostream&);

int main() {
	homepage();
	system("pause");
	return 0;
}

int homepage() {
	int choice, index;
	string choice2;

	if (!readfile("accounts.txt"))
		cout << "File does not exist!" << endl;

	do {
		system("cls");
		printTimeInLine(cout);
		drawLine();
		cout << endl;
		centerText("Souls Bank Inc.");
		cout << endl;
		drawLine();
		cout << endl;
		centerText("Menu:");
		centerText("1. Login");
		centerText("2. Exit program");
		cout << endl;
		cout << "Enter your choice >> ";
		while (!digit_validator(choice2)) { cout << setw(20) << " " << ">> "; }

		choice = stoi(choice2);

		switch (choice) {
		case 1:
			if (login(index))
				menu(index);
			printFile("accounts.txt");
			cin.ignore();
			cin.get();
			system("cls");
			break;
		}
	} while (choice != 2);
	system("cls");
	printTimeInLine(cout);
	drawLine();
	cout << endl;
	centerText("THANK YOU FOR USING OUR SERVICES");
	centerText("HAVE A NICE DAY");
	cout << endl;
	drawLine();
	cout << endl;
	return 0;
}

void print(person p, ostream& out) {
	out << "\nName: " << p.name
		<< "\nAccount Number: " << p.accountNumber
		<< "\nPIN: " << p.PIN
		<< "\nBalance: RM "<<setprecision(2) << fixed << p.balance << endl;
}

bool readfile(string filename) {
	string trash, name;
	int i(0);
	ifstream infile(filename);
	if (infile) {
		while (!infile.eof()) {
			infile >> trash;
			getline(infile, name);
			customer[i].name = name.substr(1);
			infile >> trash >> trash >> customer[i].accountNumber
				>> trash >> customer[i].PIN
				>> trash >> trash >> customer[i].balance;
			i++;
			if (infile.eof())
				break;
		}
		infile.close();
		numOfCustomer = i;
		return true;
	}
	else
		return false;
}

void printFile(string textfile) {
	ofstream outfile(textfile);
	for (int i = 0; i < numOfCustomer; i++)
		print(customer[i], outfile);
	outfile.close();
}

bool login(int& index) {
	system("cls");
	string accountNumber, PIN;
	bool flag(false);

	printTimeInLine(cout);
	centerText("LOGIN");
	drawLine();

	do {
		cout << endl;
		centerText2("Account Number : ");
		while (!digit_validator(accountNumber)) { cout << setw(50) << ">> "; }
		cout << endl;
		centerText2("PIN : ");
		PIN_checker(PIN);

		for (int i = 0; i < numOfCustomer; i++)
			if (customer[i].accountNumber == accountNumber && customer[i].PIN == PIN) {
				flag = true;
				index = i;
				break;
			}

		if (!flag) {
			cout << endl;
			drawLine();
			centerText("Account Number or PIN number does not exists");
			centerText("Please try again.");
			drawLine();
		}
	} while (!flag);

	return true;
}

void menu(int index) {
	int choice;
	string choice2;

	numOfTransactionRecord = 0;
	if (readTransaction()) {
		transCus[numOfTransactionRecord - 1] = transCus[numOfTransactionRecord];
		numOfTransactionRecord--;
	}
	else
		cout << "File does not exist";

	do {
		system("cls");
		printTimeInLine(cout);
		cout << endl;
		drawLine();
		centerText("Welcome, " + customer[index].name);
		drawLine();

		cout << "\nMenu"
			<< "\n1.Check Balance"
			<< "\n2.Deposit Amount"
			<< "\n3.Withdraw Amount"
			<< "\n4.Transfer Amount"
			<< "\n5.Transaction History"
			<< "\n6.User Details"
			<< "\n7.Exit"
			<< endl << endl
			<< "Enter your choice >> ";
		while (!digit_validator(choice2)) { cout << setw(20) << " " << ">> "; }

		choice = stoi(choice2);

		system("cls");
		switch (choice) {
		case 1:
			printTimeInLine(cout);
			centerText("CHECK BALANCE");
			drawLine();

			cout << endl;
			checkBalance(index);
			cout << endl << endl;
			drawLine();
			centerText("TRANSACTION HAS ENDED");
			drawLine();

			cin.ignore();
			cin.get();
			system("cls");
			break;
		case 2:
			printTimeInLine(cout);
			centerText("DEPOSIT AMOUNT");
			drawLine();
			if (depositAmount(index))
				centerText("THE AMOUNT HAS BEEN SUCCESSFULLY DEPOSITED");
			else {
				cout << endl;
				centerText("TRANSACTION HAS ENDED");
			}

			cin.ignore();
			cin.get();
			system("cls");
			break;
		case 3:
			printTimeInLine(cout);
			centerText("WITHDRAW AMOUNT");
			drawLine();
			if (!withdrawAmount(index)) {
				cout << endl;
				centerText("INSUFFICIENT FUNDS AVAILABLE");
			}

			cin.ignore();
			cin.get();
			system("cls");
			break;
		case 4:
			printTimeInLine(cout);
			centerText("TRANSFER AMOUNT");
			drawLine();
			if (transferAmount(index)) {
				cout << endl;
				centerText("TRANSACTION COMPLETED SUCCESSFULLY");
			}
			else {
				cout << endl;
				centerText("TRANSACTION HAS ENDED");
			}

			cin.ignore();
			cin.get();
			system("cls");
			break;
		case 5:
			numOfTransactionRecord = 0;
			if (readTransaction()) {
				transCus[numOfTransactionRecord - 1] = transCus[numOfTransactionRecord];
				numOfTransactionRecord--;
			}
			else
				cout << "File does not exist";

			printTimeInLine(cout);
			centerText("TRANSACTION HISTORY");
			drawLine();

			cout << "\nTransefered: " << endl;
			for (int i = 0; i < numOfTransactionRecord; i++)
				if (transCus[i].cus.name == customer[index].name)
					if (transCus[i].status == "GIVE")
						printTransactionDetails(transCus[i], cout);
					
			cout << "\nReceived: " << endl;
			for (int i = 0; i < numOfTransactionRecord; i++)
				if (transCus[i].cus.name == customer[index].name)
					if (transCus[i].status == "RECEIVED")
						printTransactionDetails(transCus[i], cout);

			cout << endl << endl;
			drawLine();
			centerText("TRANSACTION HAS ENDED");
			drawLine();

			cin.ignore();
			cin.get();
			system("cls");
			break;
		case 6:
			printTimeInLine(cout);
			centerText("USER DETAILS");
			drawLine();

			print(customer[index], cout);

			cout << endl << endl;
			drawLine();
			centerText("TRANSACTION HAS ENDED");
			drawLine();

			cin.ignore();
			cin.get();
			system("cls");
			break;
		}
	} while (choice != 7);
	printTimeInLine(cout);
	drawLine();
	cout << endl;
	centerText("You will be sent back to the homepage shortly.");
	cout << endl;
	drawLine();
	cout << endl;
}

void checkBalance(int index) {
	centerText("CURRENT REMAINING BALANCE: ");
	cout << endl << setw(50) << "RM " << setprecision(2) << fixed << customer[index].balance << endl;
}

bool depositAmount(int index) {
	double deposit;
	bool flag = false;
	string choice2;
	int choice;

	do {
		cout << endl;
		centerText("PLEASE ENTER AMOUNT TO DEPOSIT:");
		cout << endl << setw(50) << "RM ";
		cin >> deposit;
		cout << endl;

		if (deposit > 0)
			flag = true;

		if (!flag) {
			centerText("ERROR! NEGATIVE AMOUNT CANNOT BE DEPOSITED");
			cout << endl;
			centerText("WOULD YOU LIKE TO CONTINUE THE TRANSACTION?");
			centerText("(ENTER 1-YES OR 2-NO)");
			cout << setw(50) << ">> ";
			while (!digit_validator(choice2)) { cout << setw(50) << ">> "; }

			choice = stoi(choice2);

			if (choice == 2)
				return false;
		}

	} while (!flag);

	customer[index].balance += deposit;
	return true;
}

bool withdrawAmount(int index) {
	double withdraw;
	int choice;
	string choice2;
	bool flag = true;

	if (customer[index].balance == 0)
		return false;

	do {
		flag = true;
		cout << endl;
		centerText("PLEASE ENTER AMOUNT TO BE WITHDRAWN:");
		cout << endl << setw(50) << "RM ";
		cin >> withdraw;
		cout << endl;
		
		if (customer[index].balance < withdraw)
			flag = false;

		if (!flag) {
			centerText("ERROR! INSUFFICIENT FUNDS");
			cout << endl;
			centerText("WOULD YOU LIKE TO CONTINUE THE TRANSACTION?");
			centerText("(ENTER 1-YES OR 2-NO)");
			cout << setw(50) << ">> ";
			while (!digit_validator(choice2)) { cout << setw(50) << ">> "; }

			choice = stoi(choice2);

			if (choice == 2) {
				cout << endl;
				centerText("TRANSACTION HAS ENDED");
				break;
			}
		}
	} while (!flag);

	if (flag) {
		centerText("THE AMOUNT HAS BEEN WITHDRAWN SUCCESSFULLY");
		customer[index].balance -= withdraw;
	}

	return true;
}

bool transferAmount(int index) {
	double amount;
	string transfereeAcc, choice2;
	int tIndex, choice, choice3;
	bool flag = false, flag2 = false;

	if (customer[index].balance == 0) {
		cout << endl;
		centerText("ERROR! INSUFFICIENT FUNDS AVAILABLE");
		return false;
	}

	do{
	do {
		cout << endl;
		centerText("PLEASE ENTER TRANSFEREE ACCOUNT NUMBER:");
		cout << setw(50) << " ";
		while (!digit_validator(transfereeAcc)) { cout << setw(50) << " "; }

		for (int i = 0; i < numOfCustomer; i++)
			if (customer[i].accountNumber == transfereeAcc) {
				flag = true;
				tIndex = i;
				break;
			}

		if (transfereeAcc == customer[index].accountNumber) {
			centerText("YOU CANNOT TRANSFER TO OWNSELF");
			flag = false;
		}

		if (!flag) {
			centerText("ERROR! INVALID ACCOUNT NUMBER");
			cout << endl;
			centerText("WOULD YOU LIKE TO CONTINUE THE TRANSACTION?");
			centerText("(ENTER 1-YES OR 2-NO)");
			cout << setw(50) << ">> ";
			while (!digit_validator(choice2)) { cout << setw(50) << ">> "; }

			choice = stoi(choice2);

			if (choice == 2)
				return false;
		}
	} while (!flag);

	do {
		flag = true;
		cout << endl;
		centerText("PLEASE ENTER AMOUNT TO TRANSFER:");
		cout << endl << setw(50) << "RM ";
		cin >> amount;
		cout << endl;

		if (customer[index].balance < amount)
			flag = false;

		if (!flag) {
			centerText("ERROR! INSUFFICIENT FUNDS");
			cout << endl;
			centerText("WOULD YOU LIKE TO CONTINUE THE TRANSACTION?");
			centerText("(ENTER 1-YES OR 2-NO)");
			cout << setw(50) << ">> ";
			while (!digit_validator(choice2)) { cout << setw(50) << ">> "; }

			choice = stoi(choice2);

			if (choice == 2)
				return false;
		}
	} while (!flag);

	flag2 = false;
		centerText("YOU ARE ABOUT TO TRANSFER TO:");
		cout << endl;
		centerText("Name: " + customer[tIndex].name);
		centerText("Account Number: " + customer[tIndex].accountNumber);
		centerText("Amount: RM" + to_string(amount));
		cout << endl;
		centerText("ARE YOU SURE?");
		centerText("ENTER 1-YES OR 2-NO");
		cout << setw(50) << ">> ";
		while (!digit_validator(choice2)) { cout << setw(50) << ">> "; }

		choice3 = stoi(choice2);

		if (choice3 == 1)
			break;
	} while (!flag2);

	calculate_date(transCus[numOfTransactionRecord].rec);
	transCus[numOfTransactionRecord].cus = customer[index];
	numOfTransactionRecord++;

	calculate_date(transCus[numOfTransactionRecord].rec);//Make into a function
	transCus[numOfTransactionRecord].cus = customer[tIndex];
	numOfTransactionRecord++;

	cout << "\nReceipt: ";
	printTransaction(index, tIndex, amount, cout);

	cout << endl << setw(100) << " ";
	printTime(transCus[numOfTransactionRecord - 1].rec, cout);

	customer[index].balance -= amount;
	customer[tIndex].balance += amount;

	ofstream outfile("transaction_history.txt", ios::app);
	printTransaction(index, tIndex, amount, outfile);
	outfile.close();

	return true;
}

void printTransactionDetails(transaction tc,ostream& out) {
	out << "\nName: " << tc.cus.name
		<< "\nAccount Number: " << tc.cus.accountNumber
		<< "\nAmount: RM " << tc.amount
		<< "\nTime: " << tc.rec.time << " " << tc.rec.date
		<< "\nStatus: " << tc.status;
	if (tc.status == "GIVE")
		out << "\nTransferee: " << tc.tName
		<< "\nTransferee Account Number: " << tc.tAccNum << endl;
	else
		out << "\nTransferor: " << tc.tName
		<< "\nTransferor Account Number: " << tc.tAccNum << endl;
}

void printTransaction(int index, int tIndex,double amount,ostream& out) {
	out << "\nTransaction " << numOfTransactionRecord - 1
		<< "\nName: " << customer[index].name
		<< "\nAccount Number: " << customer[index].accountNumber
		<< "\nAmount: RM " << setprecision(2) << fixed << amount
		<< "\nTime: ";
	printTime(transCus[numOfTransactionRecord - 2].rec, out);
	out << "Status: GIVE"
		<< "\nTransferee: " << customer[tIndex].name
		<< "\nTransferee Account Number: " << customer[tIndex].accountNumber << endl;

	out << "\nTransaction " << numOfTransactionRecord
		<< "\nName: " << customer[tIndex].name
		<< "\nAccount Number: " << customer[tIndex].accountNumber
		<< "\nAmount: RM " << setprecision(2) << fixed << amount
		<< "\nTime: ";
	printTime(transCus[numOfTransactionRecord - 1].rec, out);
	out << "Status: RECEIVED"
		<< "\nTransferor: " << customer[index].name
		<< "\nTransferor Account Number: " << customer[index].accountNumber << endl;
}

bool readTransaction() {
	string trash, name;
	ifstream infile("transaction_history.txt");
	if (infile) {
		while (!infile.eof()) {
			infile >> trash >> trash
				>> trash;
			getline(infile, name);
			transCus[numOfTransactionRecord].cus.name = name.substr(1);
			infile >> trash >> trash >> transCus[numOfTransactionRecord].cus.accountNumber
				>> trash >> trash >> transCus[numOfTransactionRecord].amount
				>> trash >> transCus[numOfTransactionRecord].rec.time >> transCus[numOfTransactionRecord].rec.date
				>> trash >> transCus[numOfTransactionRecord].status
				>> trash;
			getline(infile, name);
			transCus[numOfTransactionRecord].tName = name.substr(1);
			infile >> trash >> trash >> trash >> transCus[numOfTransactionRecord].tAccNum;
			numOfTransactionRecord++;
			if (infile.eof())
				break;
		}
		infile.close();
		return true;
	}
	else
		return false;
	return true;
}

void centerText(string s) {
	int l = s.length();
	int empty = 60 - (int)(l / 2);
	cout << setw(empty) << " " << s << endl;
}

void centerText2(string s) {
	int l = s.length();
	int empty = 45 - (int)(l / 2);
	cout << setw(empty) << " " << s;
}

void drawLine() {
	cout << "========================================================================================================================" << endl;
}

void PIN_checker(string& x) {
	char password[1000];
	char a;
	int pswdPtr(0);
	int i = 0;
	while (i == 0) {
		a = _getch();
		if (isdigit(a)) {
			password[pswdPtr++] = a;
			cout << "*";
		}
		if (a == '\b' && pswdPtr > 0) {
			pswdPtr--;
			cout << "\b \b";
		}
		if (a == '\r') {
			password[pswdPtr] = '\0';
			break;
		}
	}
	x = password;
}

bool digit_validator(string& x) {
	cin >> x;
	for (int i = 0; i < x.length(); i++)
		if (!isdigit(x[i]) && !isspace(x[i]))
			return false;
	return true;
}

void calculate_date(rTime& t) {
	int m[13]= { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
	int totalseconds = time(0);
	int currentSecond = totalseconds % 60;
	int totalminutes = totalseconds / 60;
	int currentMinute = totalminutes % 60;
	int totalhours = totalminutes / 60 + 8;
	int currentHour = totalhours % 24;
	int totalDays = totalhours / 24;

	int currentYear(0), currentMonth(0), currentDay, leapYears(0);
	
	while (totalDays >= 365) {
		totalDays -= 365;
		currentYear++;
	}
	
	leapYears = currentYear / 4;

	while (m[currentMonth] < totalDays) { currentMonth++; }

	currentDay = totalDays - m[currentMonth - 1] - leapYears;
	currentYear += 1970;

	t.day = currentDay;
	t.month = currentMonth;
	t.year = currentYear;
	t.hour = currentHour;
	t.minute = currentMinute;
	t.second = currentSecond;
}

void printTime(rTime t,ostream& out) {
	if (t.hour < 10)//convert this into a function
		out << "0" << t.hour << ":";
	else
		out << t.hour << ":";

	if (t.minute < 10)
		out << "0" << t.minute << ":";
	else
		out << t.minute << ":";

	if (t.second < 10)
		out << "0" << t.second << " ";
	else
		out << t.second << " ";

	out << t.day << "/"
		<< t.month << "/"
		<< t.year << endl;
}

void split_string(string str, string a[], int num, char s) {
	int numOfLoop(0), x(0), start(-1);
	int* occurence = new int[num];
	string split;

	for (int i = 0; i < str.length(); i++)//This function stores the position of '/' into occurence array.
		if (str[i] == s)
			occurence[numOfLoop++] = i;

	occurence[numOfLoop] = str.length();

	while (x <= numOfLoop) {//This functions creates a string based from the start position to the position of '/'
		split = str.substr(start + 1, occurence[x] - start - 1);
		a[x++] = split;
		start = occurence[x - 1];
	}
}

void printTimeInLine(ostream& out){
	rTime ct;
	calculate_date(ct);
	cout << setw(100) << " ";
	printTime(ct, out);
}