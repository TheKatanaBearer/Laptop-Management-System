#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<exception>
using namespace std;

struct laptop {
	int serialNo;
	char brand[20];
	char model[20];
	int price;
	int pieces;


	laptop() {
		serialNo = 0;
		brand[0] = '\0';
		model[0] = '\0';

		price = 0;
		pieces = 0;



	}
};

void display_menu();

static void clearFile() {
	ofstream myfile("laptop.bin", ios::binary | ios::trunc);
	if (!myfile.is_open()) {
		cout << "Error: Could not open the file to clear its contents." << endl;
	}
	else {
		cout << "The file has been successfully cleared." << endl << endl;
	}
	myfile.close();
}
static void addRecord() {

	clearFile();

	laptop l;
	laptop sno;

	cout << "-> enter the serial no of the laptop(intgers only) " << endl;

	cin >> sno.serialNo;

	int c;
	int sr;
	while (1) {
		sr = sno.serialNo;
		c = 0;
		while (sr != 0) {
			sr /= 10;
			c++;
		}

		if (c <= 6) {
			break;
		}

		else {
			cout << "-> the serial number that u have entered is invalid (it cannot go above 6 digits) " << endl << endl;
			cout << "-> enter the serial number again " << endl;
			cin >> sno.serialNo;

		}
	}



	//adding validation for this

	ifstream ifile("laptop.bin", ios::binary);


	bool store = false;

	while (ifile.read((char*)(&l), sizeof(laptop))) {
		;
		if (l.serialNo == sno.serialNo) {
			store = true;
			break;

		}
	}

	if (store) {
		cout << "-> The serial number already exists ! " << endl;
		exit(0);

	}

	l.serialNo = sno.serialNo;







	cout << "-> enter the brand of the laptop " << endl;
	cin.ignore();
	cin.getline(l.brand, 20);

	cout << "-> enter the model of the brand " << endl;
	cin.getline(l.model, 20);

	cout << "-> enter the price of the laptop(intgers only) " << endl;
	cin >> l.price;

	while (1) {

		while (l.price < 0) {

			cout << "-> why are u inputting a negative number...input again ? " << endl;
			cin >> l.price;
		}
		int price = l.price;
		int count = 0;

		if (price == 0) {
			break;
		}


		while (price != 0) {
			price /= 10;
			count++;
		}

		if (count <= 6) {
			break;
		}

		else {
			cout << "-> the price that u have entered is invalid (it cannot go above 6 digits) " << endl;
			cout << "-> enter the price again " << endl;
			cin >> l.price;
		}

	}


	cout << "-> Enter the number of machines (it cannot exceed 1000) " << endl;
	cin >> l.pieces;



	while (l.pieces < 0) {
		cout << "-> why are u inputting a negative number...input again  " << endl;
		cin >> l.pieces;
	}

	while (l.pieces > 1000) {
		cout << "-> why are you inputing an unrealistic number(it should be till 1000)..input again " << endl;
		cin >> l.pieces;
	}




	ofstream myfile("laptop.bin", ios::binary | ios::app);

	if (!myfile.is_open()) {
		cout << "-> the file didnt open " << endl;

	}

	myfile.write((char*)&l, sizeof(laptop));
	cout << "-> the record has been added successfully " << endl;

	ifile.close();
	myfile.close();


}

static void updateRecord() {
	int search;

	cout << "-> enter the serial number of the record that you want to search " << endl;
	cin >> search;



	int c;
	int sr;


	while (1) {
		sr = search;
		c = 0;
		while (sr != 0) {
			sr /= 10;
			c++;
		}

		if (c <= 6) {
			break;
		}

		else {
			cout << "-> the serial number that u have entered is invalid (it cannot go above 6 digits) " << endl << endl;
			cout << "-> enter the serial number again " << endl;
			cin >> search;

		}
	}











	fstream ifile("laptop.bin", ios::binary | ios::in | ios::out);

	laptop l;

	bool store = false;
	int record_size = sizeof(laptop);
	int start = 0;

	while (ifile.read((char*)&l, sizeof(laptop))) {

		if (l.serialNo == search) {



			store = true;
			cout << "-> THE RECORD HAS BEEN FOUND...GO AHEAD AND UPDATE IT " << endl;

			cout << "-> Enter the new brand " << endl;
			cin.ignore();

			cin.getline(l.brand, 20);

			cout << "-> Enter the new model " << endl;
			cin.getline(l.model, 20);

			cout << "-> Enter the new price of the laptop " << endl;
			cin >> l.price;
			while (1) {

				while (l.price < 0) {

					cout << "-> why are u inputting a negative number...input again ? " << endl;
					cin >> l.price;
				}
				int price = l.price;
				int count = 0;

				if (price == 0) {
					break;
				}


				while (price != 0) {
					price /= 10;
					count++;
				}

				if (count <= 6) {
					break;
				}

				else {
					cout << "-> the price that u have entered is invalid (it cannot go above 6 digits) " << endl;
					cout << "-> enter the price again " << endl;
					cin >> l.price;
				}

			}


			cout << "-> Enter the new number of pieces of the system " << endl;
			cin >> l.pieces;

			while (l.pieces < 0) {
				cout << "-> why are u inputting a negative number...input again  " << endl;
				cin >> l.pieces;
			}

			while (l.pieces > 1000) {
				cout << "-> why are you inputing an unrealistic number(it should be till 1000)..input again " << endl;
				cin >> l.pieces;
			}

			ifile.seekp(start);
			ifile.write((char*)&l, sizeof(laptop));

			cout << "-> the record has been updated " << endl;
			break;
		}

		start = start + record_size;


	}
	if (!store) {
		cout << "-> the record was not found...do u want to continue searching(click s or S) or go to menu again(click Y or y for menu)? " << endl;
		char ch;
		cin >> ch;

		while (ch != 'Y' && ch != 'y' && ch != 'S' && ch != 's') {
			cout << "-> you entered an invalid character..enter again! " << endl;
			cin >> ch;

		}

		if (ch == 'Y' || ch == 'y') {
			display_menu();

		}

		else if (ch == 'S' || ch == 's') {
			updateRecord();

		}

	}

	ifile.close();


}

static void deleteRecord() {
	int search;
	cout << "-> Enter the serial number of the record that you want to delete " << endl;
	cin >> search;


	//ADDING VALIDATION TO THE SEARCH OPTION
	int c;
	int sr;




	while (search < 0) {
		cout << "-> why are u inputting a negative number...input again  " << endl;
		cin >> search;
	}

	while (1) {
		sr = search;
		c = 0;
		while (sr != 0) {
			sr /= 10;
			c++;
		}

		if (c <= 6) {
			break;
		}

		else {
			cout << "-> the serial number that u have entered is invalid (it cannot go above 6 digits) " << endl << endl;
			cout << "-> enter the serial number again " << endl;
			cin >> search;

		}
	}

	laptop l;

	ifstream ifile("laptop.bin", ios::binary);
	ofstream ofile("temp.bin", ios::binary);

	if (!ofile) {
		cout << "the temporary file didnt open " << endl;
	}

	bool flag = false;
	while (ifile.read((char*)&l, sizeof(laptop))) {

		if (l.serialNo == search) {
			cout << "->THE SERIAL NUMBER HAS BEEN FOUND! " << endl;
			flag = true;

		}

		else {

			ofile.write((char*)&l, sizeof(laptop));



		}

	}

	if (!flag) {
		cout << "The serial number wasnt found ! " << endl;
		display_menu();
	}




	ifile.close();
	ofile.close();

	remove("laptop.bin");
	rename("temp.bin", "laptop.bin");


	cout << "->The record was deleted successfully " << endl;




}

static void displayRecords() {
	ifstream ifile("laptop.bin", ios::binary);

	laptop l;

	cout << "-> these are all the records that are present " << endl;
	cout << "----------------------------------------------------" << endl;

	while (ifile.read((char*)&l, sizeof(laptop))) {

		cout << "              #The serial number is " << l.serialNo << endl;
		cout << "              #The brand is " << l.brand << endl;
		cout << "              #The model is " << l.model << endl;
		cout << "              #The price is " << l.price << endl;
		cout << "              #The number of pieces are " << l.pieces << endl;
		cout << "---------------------------------------------------" << endl;

	}
}

static void importCSV() {


	// There are issues in this sir

	ifstream cfile("laptops.csv");

	if (!cfile) {
		cout << "The csv file couldn't open " << endl;
		display_menu();
		return;
	}

	ofstream ofile("laptop.bin", ios::binary | ios::app);

	if (!ofile) {
		cout << "The binary file didn't open " << endl;
		display_menu();
		return;
	}

	laptop l;
	string line;
	int i;
	string serial_;
	string model_;
	string brand_;
	string price_;
	string pieces_;

	while (getline(cfile, line)) {
		i = 0;
		serial_ = "";
		model_ = "";
		brand_ = "";
		price_ = "";
		pieces_ = "";


		while (i < line.length() && line[i] != ',') {
			serial_ = serial_ + line[i];
			i++;
		}



		l.serialNo = stoi(serial_);
		i++;

		while (i < line.length() && line[i] != ',') {
			brand_ = brand_ + line[i];
			i++;
		}



		int k = 0;
		for (int j = 0; brand_[j] != '\0'; j++, k++) {
			l.brand[k] = brand_[j];
		}
		l.brand[++k] = '\0';

		i++;


		while (i < line.length() && line[i] != ',') {
			model_ = model_ + line[i];
			i++;
		}



		k = 0;
		for (int j = 0; model_[j] != '\0'; j++, k++) {
			l.model[k] = model_[j];
		}

		l.model[++k] = '\0';

		i++;


		while (i < line.length() && line[i] != ',') {
			price_ = price_ + line[i];
			i++;
		}



		l.price = stoi(price_);
		i++;


		while (i < line.length() && line[i] != ',') {
			pieces_ = pieces_ + line[i];
			i++;
		}



		l.pieces = stoi(pieces_);

		ofile.write((char*)&l, sizeof(laptop));
	}

	cout << "The record has been successfully imported from the csv file " << endl;


	cfile.close();
	ofile.close();
}










static void exportCSV() {

	ifstream ifile("laptop.bin", ios::binary);

	ofstream cfile("laptops2.csv");

	if (!cfile) {
		cout << "the csv file didnt open " << endl;
	}

	laptop l;

	while (ifile.read((char*)&l, sizeof(laptop))) {
		cfile << l.serialNo << "," << l.brand << "," << l.model << "," << l.price << "," << l.pieces << endl;

	}

	cout << "-> the data has been successfully exported " << endl;

	ifile.close();
	cfile.close();



}

static void showHelp() {
	cout << "->THIS IS THE HELP SECTION " << endl;
	cout << "--------------------------------------" << endl;
	cout << "->This code is very user friendly and easy to understand but if you still have any confusion then we can explain " << endl;
	cout << "->Basically this code is divided into a menu system where upon pressing specific buttons we get specific functionality that relates to filing " << endl;
	cout << "->The file is instantiated automatically the moment that you add your first record...later on all are the modifications to that file " << endl;
	cout << "->This code is created by me 'Hamza Khan Tariq 04072313050 3rd semester' " << endl;
}


void display_menu() {
	char ch;
	do {
		cout << "---------------------------------------------" << endl;
		cout << "** to add record              [1] " << endl;
		cout << "** to update a record         [2] " << endl;
		cout << "** to delete a record         [3] " << endl;
		cout << "** to display all the records [4]" << endl;
		cout << "** to import from csv         [5]" << endl;
		cout << "** to export csv              [6]" << endl;
		cout << "** to show help desk          [7] " << endl;
		cout << "-----------------------------------------------" << endl;
		int n;
		cin >> n;
		switch (n) {
		case 1:
			addRecord();
			break;

		case 2:
			updateRecord();
			break;

		case 3:
			deleteRecord();
			break;

		case 4:
			displayRecords();
			break;
		case 5:
			importCSV();
			break;
		case 6:
			exportCSV();
			break;
		case 7:
			showHelp();
			break;

		default:
			cout << "-> you pressed the wrong option...it doesnt exist " << endl;
		}
		cout << "--------------------------------------------------------------------------" << endl;
		cout << "-> do you want the menu to appear again?....click Y | y if 'yes' and any button to terminate the program  " << endl;
		cin >> ch;
		if (ch != 'Y' && ch != 'y') {
			break;
		}
	} while (ch == 'Y' || ch == 'y');

}




int main() {

	cout << "--------------WELCOME TO THE MENU------------------" << endl;

	display_menu();


}