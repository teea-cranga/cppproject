#include<iostream>
#include"classes.h"
using namespace std;

int Event::NO_EVENTS = 0;

int main() {

	cout << "\t\t\t\t-----!!TICKET APP!!-----\n";
	cout << "Please select which event you want to attend to:\n";
	cout << "Available options(please select the number corresponding to the event): \n 1. Footbal event \n 2. Movies\n 3. Theatre \n 4. Others(you will specify what type of event you'd like)\n";
	cout << "------------------------------------" << endl;
	
	Event ev1;

	cout << "Please enter a location:";


	Location loc1;

	cout << "Please select which ticket you would like to buy:";
	cout << "1. type 1\n 2. type 2\n 3. VIP/BOX\n";

	Ticket tick1;

	return 0;
}