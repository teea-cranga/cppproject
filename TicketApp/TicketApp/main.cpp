#include<iostream>
#include"classes.h"
using namespace std;

int Event::NO_EVENTS = 0;

//WIP !!MAIN APP!!  
//will contain things for phase 2
//so far has some concepts

int main() {

	cout << "\t\t\t\t-----!!TICKET APP!!-----\n";
	cout << endl << "Available options: ";
	cout << endl << "1.Add event";
	cout << endl << "2.See locations";
	cout << endl << "3.Check validity";
	cout << endl << "------------------------------------\n";
	int choice, OK = 1;
	while (OK) {
		cin >> choice;
		OK = 0;
		switch (choice) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			cout << "Invalid number. Try again.";
			OK = 1;
			break;
		}
	}
	return 0;
}