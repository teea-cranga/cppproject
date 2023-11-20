#include <iostream>
#include <string.h>

using namespace std;

//PHASE 1
enum eventType { FOOTBALL = 1, MOVIE = 2, THEATRE = 3, OTHERS = 4 };	//makes it easier to select options(at least for now)
enum category { TIP1 = 1, TIP2 = 2, VIPORBOX = 3 };				//default for every type of event, i think it is obsolete, but i will keep this for now

class Util {															//works only for chars tbh. 
public:																	//maybe i will add some function that does the same for the **seats from Location class
	static char* copyString(const char* source) {
		if (source == nullptr) {
			return nullptr;
		}
		char* value = new char[strlen(source) + 1];
		strcpy_s(value, strlen(source) + 1, source);
		return value;
	}
};

class Event {
	eventType event = FOOTBALL;
	char* name=nullptr;
	int date[3] = { 1,1, 2023 };	//date[0] - day, date[1] - month, date[2] - year
	string details="";
	static int NO_EVENTS;
	const int MIN_LENGTH = 4;
public:
	void setName(const char* nume) {
		this->name = Util::copyString(nume);
	}

	char* getName() {
		if (strlen(this->name) < MIN_LENGTH)
			throw exception("Invalid event name.");
		char* copy = Util::copyString(this->name);
		return copy;
	}

	eventType getEvent(int input) {
		if (input < 1 || input > 4)
			throw exception("Invalid number. Please enter another number.");
		return (eventType)input;
	}

	Event() {
		NO_EVENTS++;
	}

	~Event() {
		delete[] this->name;
		NO_EVENTS--;
	}

	
};



class Location {

	int noCategories = 3;
	int* seats;	//an array which will either have 0(available) or 1 (taken)
	int noSeats;
	category cat;
	int catPrices[3]; //list of prices for each event
	static int CAPACITY;
public:

};

class Ticket {
	unsigned long id;
	int price;
	category tickCat=TIP1;
	bool isValid;
	char* nameOfBuyer=nullptr;
	const int MIN_LENGTH = 4;
	static int NO_TICKETS;
public:
	char* getName(const char* nameOfBuyer) {
		if (strlen(this->nameOfBuyer) < MIN_LENGTH)
			throw exception("Invalid buyer name.");
		char* copy = Util::copyString(this->nameOfBuyer);
		return copy;
	}

	void setName() {
		this->nameOfBuyer = Util::copyString(this->nameOfBuyer);
	}

	Ticket() : price(300),isValid(true) {
		NO_TICKETS++;
	}
};

int main() {
 
	cout << "\t\t\t\t-----WELCOME-----\n";
	cout << "Please select which event you want to attend to:\n";
	cout << "Available options(please select the number corresponding to the event): \n 1. Footbal event \n 2. Movies\n 3. Theatre \n 4. Others(you will specify what type of event you'd like)\n";
	int eventOption, ticketOption;
	cin >> eventOption;
 
	Event ev1;

	cout << "Please enter a location:";

	Location loc1;

	cout << "Please select which ticket you would like to buy:";
	cout << "1. type 1\n 2. type 2\n 3. VIP/BOX\n";

  cin>>ticketOption;
	Ticket tick1;

	return 0;
}
