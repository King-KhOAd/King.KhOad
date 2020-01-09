/*
Author: Khalif Adegeye 
Creation Date: 11/20/19
Update Date: 12/4/19
Purpose: Project #2 for CIS 150. The following is a airplane seat reservation
service where the code reads in a document containing plane information and
creates a menu for the user to interact with. The menu can display reservations,
create reservations, and cancel reservations. The Document being read in  can have any number
of rows and columns but must follow the pattern:
1 A B C D E...
2 A B C D E...
3 ...
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void seatIn(string&, ifstream&, vector<vector<char>>&);
void menuMain();
void resDisplay(vector<vector<char>>& Vseat);
void resAdd(vector<vector<char>>& Vseat);
void resDel(vector<vector<char>>& Vseat);

int main() {
	int input;
	string fileName;
	vector <vector<char>> Vseat;
	ifstream ifs;
	ofstream ofs;

	seatIn(fileName, ifs, Vseat);
	do {
		menuMain();
		cin >> input;
		switch (input) {
		case 1:
			resDisplay(Vseat);
			break;
		case 2:
			resAdd(Vseat);
			break;
		case 3:
			resDel(Vseat);
			break;
		case 4:
			break;
		default:
			cout << "Error: Invalid Input!" << endl;
			system("pause");
		}
	} while (input != 4);


	cout << "Exiting... Goodbye!" << endl;
	system("pause");
	return (0);
}

/*
Author: Khalif Adegeye
Creation Date: 11/20/19
Update Date: 12/4/19
Purpose: Prompts user for the file name then pulls the data in the given file into a double vector
*/

void seatIn(string& fileName, ifstream& ifs, vector<vector<char>>& Vseat) {
	int rowNum;
	string seat;

	cout << "To Begin, Please Enter the Seating Filename: ";
	cin >> fileName;
	ifs.open(fileName);

	if (!ifs.is_open()) { //Checks if file is working as intended
		cerr << "Error Opening File!" << endl;

	}
	while (!ifs.eof()) {
		ifs >> rowNum;
		getline(ifs, seat);
		vector<char> Vrow;
			for (int i = 0; i < seat.length(); i++) {
				if (!isspace(seat.at(i))) {
					Vrow.push_back(seat.at(i)); //Pushes chars into the internal vector
				}
			}
			Vseat.push_back(Vrow); //Pushes the internal vector into the external vector
			
	}
	ifs.close();
}

/*
Author: Khalif Adegeye
Creation Date: 11/20/19
Update Date: 12/4/19
Purpose: Displays the main menu text
*/
void menuMain() {
	cout << "------------------------------------------------------" << endl << "	Adegeyian Airplane Seat Reservation v_01" << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "Welcome. Please choose what you would like to do." << endl << endl;
	cout << "1. Show Current Seat Reservation" << endl << "2. Add New Reservation" << endl << "3. Delete a Reservation" << endl << "4. Quit" << endl << endl;
}


/*
Author: Khalif Adegeye
Creation Date: 11/20/19
Update Date: 12/4/19
Purpose: Displays the info in the vectors gathered from the file
*/
void resDisplay(vector<vector<char>>& Vseat) {
	for (int i = 0; i < Vseat.size(); i++) { // Finding the internal vector (ABCD, then ABCD, then ABCD
		cout << i+1;	// Displaying the row number
		for (int j = 0; j < Vseat.at(i).size(); j++) { // Saying for the Vector vector at i, whats the string vector contained within
			cout << " " << Vseat.at(i).at(j); // Displaying the 'A' 'B' 'C' & 'D'
		}
		cout << endl;
	}
}


/*
Author: Khalif Adegeye
Creation Date: 11/20/19
Update Date: 12/4/19
Purpose: Adds reservations to the vectors' memory
*/
void resAdd(vector<vector<char>>& Vseat) {
	int resRow, i, k;
	bool checkRowAdd, checkSeatAdd;
	char resSeat;

	cout << "In which row is the desired reservation? (Only numerical values): ";
	cin >> resRow;
	cout << endl << "Which seat is it? (Capital Letters Only): ";
	cin >> resSeat;

	for (i = 0; i < Vseat.size(); i++) {
		if (i + 1 == resRow) { // If the row number equals the entered row, the entry was found & we can stop checking so stop looping
			checkRowAdd = true;
			break;
		}
		checkRowAdd = false; // If the loop is never broken, the entry was invalid, thus entryChecker is false
	}

	for (k = 0; k < Vseat.at(i).size(); k++) { // Same principle as the first loop, only in the internal vector
		if (resSeat == Vseat.at(i).at(k)) {
			checkSeatAdd = true;
			break;
		}
		checkSeatAdd = false;
	}

		
	

	if (checkSeatAdd == false || checkRowAdd == false) {
		cerr << "Invalid Seat!" << endl;
	}
	else if (Vseat.at(i).at(k) == ('X')) {
		cout << "Seat is already reserved!" << endl;

	}
	else {
		Vseat.at(i).at(k) = 'X';
		cout << "Seat successfully reserved!" << endl;
	}


}
/*
Author: Khalif Adegeye
Creation Date: 11/20/19
Update Date: 12/4/19
Purpose: Deletes previous reservations stored in the vector
*/
void resDel(vector<vector<char>>& Vseat) {
	int resRow, l, n;
	bool checkRowDel, checkSeatDel;
	char resSeat;

	cout << "In which row is the reservation to be deleted? (Only numerical values): ";
	cin >> resRow;
	cout << endl << "Which seat is it? (Capital Letters Only): ";
	cin >> resSeat;


	if (Vseat.at(resRow - 1).at(resSeat - 65) == 'X'  ) { // Checks if the user seat is actually reserved already
		Vseat.at(resRow - 1).at(resSeat - 65) = resSeat; // If it is reserved, changes the reservation character back to the letter & displays message
		cout << "Reservation successfully deleted!" << endl;
	}
	else if (Vseat.at(resRow - 1).at(resSeat - 65) != 'X') { // if the seat isn't already reserved, tells the user.
		cout << "Seat isn't reserved!" << endl;
	}
}