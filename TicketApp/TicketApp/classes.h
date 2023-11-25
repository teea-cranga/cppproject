#pragma once
#include <iostream>
#include <string.h>

using namespace std;

enum eventType { FOOTBALL = 1, MOVIE = 2, THEATRE = 3, OTHER = 4 };		//makes it easier to select options(at least for now)
enum category { TIP1 = 1, TIP2 = 2, VIPORBOX = 3, DISABILITIES = 4 };	//default for every type of event, i think it is obsolete, but i will keep this for now
enum months { JANUARY=1, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER };

class Util {															
public:																	
	static char* copyString(const char* source) {
		if (source == nullptr) {
			return nullptr;
		}
		char* value = new char[strlen(source) + 1];
		strcpy_s(value, strlen(source) + 1, source);
		return value;
	}
	static bool dateValidity(int day, int month, int year) {
		if (day < 0)
			throw exception("Invalid data.");
		switch (month) {
		case (1,3,5,7,8,10,12):
			if (day > 31)
				throw exception("Invalid date.");
			break;
		case(4, 6, 9, 11):
			if (day > 30)
				throw exception("Invalid date.");
			break;
		case 2:
			if (year % 4 == 0) {
				if(day>29)
					throw exception("Invalid date.");
			}
			else {
				if (day > 28) {
					throw exception("Invalid date.");
				}
			}
		}
		return true;
	}
};

class Location {

	string name = "";
	int catPrices[4]; //list of prices for each event
	int CAPACITY;	
	bool accessForDis;	//if the place has seats for people with disabilities

public:
	

	void noAccess() {
		this->accessForDis = false;
	}

	void setName(string name) {
		if (name.length() == NULL)
			throw exception("Not a valid name.");
		this->name = name;
	}

	void setPrices(const int prices[4]) {
		for (int i = 0; i < 4; i++) {
			if (prices[i] <= 0) {
				throw exception("This price is invalid. Try again with other values.");
			}
			else {
				
				this->catPrices[i] = prices[i];
			}
		}
		if (accessForDis == false) {
			this->catPrices[3] = 0;
		}
	}

	Location() {
		for (int i = 0; i < 4; i++) {
			this->catPrices[i] = 200;
		}
		this->CAPACITY = 100;
		this->name = "None";
		noAccess();
	}

	Location(string name, const int* prices, int cap, bool hasDis):CAPACITY(cap),accessForDis(hasDis) {
		this->setName(name);
		this->setPrices(prices);
	}

	int& operator[](int index) {	//assigns another price for a specific ticket
		if (index < 0 || index>4) {
			throw exception("Invalid ticket type.");
		}
		return this->catPrices[index];
	}

	Location operator*(int value) {
		for (int i = 0; i < 4; i++) {
			this->catPrices[i] *= value;
		}
	}

	friend void operator<<(ostream& console, Location& loc);
	friend void operator>>(istream& console, Location& loc);
};

void operator<<(ostream& console, Location& loc) {

	console << endl << "Location name: " << loc.name;
	console << endl << "The prices of the tickets: ";
	for (int i = 0; i < 4; i++) {
		if (i == 3 && loc.catPrices[3] == 0) {
			console << endl << "WARNING: this place doesn't have seats for people with disabilities.";
		}
		else
			console << endl << loc.catPrices[i] << " " << (category)i;

	}
	console << endl << "Capacity of the location: " << loc.CAPACITY << "seats.";
}

void operator>>(istream& console, Location& loc) {
	cout << endl << "Please set the data you want: ";
	cout << endl << "Name of the location is: ";
	console >> loc.name;
	cout << endl << "The prices are: ";
	for (int i = 0; i < 4; i++) {
		console >> loc.catPrices[i];
	}
	cout << endl << "The capacity of the room is: ";
	console >> loc.CAPACITY;
	cout << endl << "Does the location have facilities for people with disabilities?(bool)";
	console >> loc.accessForDis;
}

//missing:
//two operators(one MUST be =)
//copy constructor
class Event {
	eventType event;
	char* name = nullptr;
	int date[3] = { 1,1, 2023 };	//date[0] - day, date[1] - month, date[2] - year
	string details = "";
	Location loc;

	const int MIN_LENGTH = 4;
	static int NO_EVENTS;	

public:
	
	void printMonth() {
		cout << (months)this->date[1];
	}

	void printDate() {
		cout << this->date[0]<< " ";
		printMonth();
		cout << " " << this->date[2];
	}

	void setEvent(int input) {		
		if (input < 1 || input > 4)
			throw exception("Invalid number. Please enter another number.");
		this->event = (eventType)input;
	}

	void setName(const char* nume) {
		if (nume == NULL)
			throw exception("Invalid name.");
		this->name = Util::copyString(nume);
	}

	void setDate(int date[3]) {
		if (Util::dateValidity(date[0],date[1],date[2])) {
			for (int i = 0; i < 3; i++) {
				this->date[i] = date[i];
			}
		}
	}

	char* getName() {
		if (strlen(this->name) < MIN_LENGTH)
			throw exception("Invalid event name.");
		char* copy = Util::copyString(this->name);
		return copy;
	}

	static int getNoEvents() {
		return Event::NO_EVENTS;
	}

	Event():details("None") {
		this->event = OTHER;
		this->setName("Unknown");
		Event::NO_EVENTS+=1;
		this->date[0] = 1;
		this->date[1] = 1;
		this->date[2] = 2001;
	}

	Event(eventType ev, const char* name, int date[3]) {
		this->event = ev;
		this->setName(name);
		for (int i = 0; i < 2; i++) {
			this->date[i] = date[i];
		}
	}

	~Event() {
		delete[] this->name;
		Event::NO_EVENTS-=1;
	}

	friend void operator<<(ostream& console, Event& ev);
	friend void operator>>(istream& console, Event& ev);
};

void operator<<(ostream& console, Event& ev) {
	console << endl << "Name of the event" << ev.getName();
	console << endl << "The event is located at a/an: " << ev.event;
	console << endl << "The event date is:";
	ev.printDate();
	console << endl << "Details about the event: ";
	console << endl << ev.details;
	console << endl << "More details about the event(regarding the location): ";
	console << endl << ev.loc;
}

void operator>>(istream& console, Event& ev) {
	cout << endl << "Insert a name for the event:";
	char buffer[2000];
	console.getline(buffer, 2000); //if you need space in the string
	console.clear();
	ev.setName(buffer);
	cout << endl << "Insert the type of event you want to attend: ";
	//console >> ev.event;
	cout << endl << "Insert date: ";
	for (int i = 0; i < 3; i++) {
		console >> ev.date[i];
	}
	cout << endl << "Insert details: ";
	console >> ev.details;
	cout << endl << "Get a location for the event: ";
	console >> ev.loc;
}

class Room {
	char** roomSeats=nullptr;	//matrix which stores the state of a seat (- is taken, * for disabilities, / type 1, \ type 2, | vip)
	int noSeats;
	int noRows;
	category cat;
public:

	void setSeats(int noSeat) {
		this->noSeats = noSeat;
	}

	void setRows(int noRow) {
		this->noRows = noRow;
	}
	
	Room() {
		this->cat = TIP1;
		this->noRows = 10;
		this->noSeats = 10;
	}

	Room(int noRows, int noSeats, category cat) {
		this->setRows(noRows);
		this->setSeats(noSeats);
		this->cat = cat;
	}
};

class Ticket {
	unsigned long id=0;
	int price;
	category tickCat = TIP1;
	bool isValid;
	char* nameOfBuyer = nullptr;
	const int MIN_LENGTH = 4;
	Room room;
	Event ev;
	Location loc;
	
public:

	char* getName() {
		if (strlen(this->nameOfBuyer) < MIN_LENGTH)
			throw exception("Invalid buyer name.");
		char* copy = Util::copyString(this->nameOfBuyer);
		return copy;
	}

	void setName(const char* nameOfBuyer) {
		this->nameOfBuyer = Util::copyString(this->nameOfBuyer);
	}

	category setCategory(int input) {
		if (input < 1 || input>4) {
			throw exception("Invalid category type. Please try again.");
		}
		this->tickCat = (category)input;
	}

	void tickIsvalid() {
		this->isValid = true;
	}

	void tickIsNotValid() {
		this->isValid = false;
	}

	Ticket() : price(300), isValid(true) {
		this->setName("John Doe");
		this->tickIsvalid();
	}
};
