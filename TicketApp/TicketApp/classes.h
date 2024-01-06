#pragma once
#include <iostream>
#include <string.h>
#include<cstdlib>

using namespace std;

//DISCLAIMER: The main.cpp file will include the application (sorry for naming like this, realised too late how to actually manage the files)

enum class eventType { FOOTBALL = 1, MOVIE = 2, THEATRE = 3, OTHER = 4 };		
enum class category { TIP1 = 1, TIP2 = 2, VIPORBOX = 3, DISABILITIES = 4 };	
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
	static char* randomCodeGenerator() {
		char code[11] = { "1234567890" };
		char* generatedCode=new char[5];
		for (int i = 0; i < 5; i++) {
			generatedCode[i] = code[rand()%10];
		}
		generatedCode[5] = NULL;
		return generatedCode;
	}
};

class Location {

	string name = "";
	int* catPrices; //list of prices for each event
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

	void setPrices(const int* prices) {
		delete[] this->catPrices;
		if (accessForDis == true) {
			this->catPrices = new int[4];
			memcpy(this->catPrices, prices, sizeof(int) * 4);
		}
		else {
			this->catPrices = new int[3];
			memcpy(this->catPrices, prices, sizeof(int) * 3);
		}	
	}

	int* getPrices() {
		int* copy;
		if (accessForDis == true) {
			copy = new int[4];
			for (int i = 0; i < 4; i++) {
				copy[i] = this->catPrices[i];
			}
		}
		else {
			copy = new int[3];
			for (int i = 0; i < 3; i++) {
				copy[i] = this->catPrices[i];
			}
		}
		return copy;
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

	Location(const Location& loc) {
		this->name = loc.name;
		this->CAPACITY = loc.CAPACITY;
		this->setPrices(loc.catPrices);
		this->accessForDis = loc.accessForDis;
	}

	~Location() {
		delete[] this->catPrices;
	}

	int& operator[](int index) {	//assigns another price for a specific ticket
		if (index < 0 || index>4) {
			throw exception("Invalid ticket type.");
		}
		return this->catPrices[index];
	}

	void operator=(const Location& loc) {
		if (&loc == this) {
			return;
		}
		delete[] this->catPrices;
		this->setPrices(loc.catPrices);
	}

	friend void operator<<(ostream& console, Location& loc);
	friend void operator>>(istream& console, Location& loc);
};

void operator<<(ostream& console, Location& loc) {

	console << endl << "Location name: " << loc.name;
	console << endl << "The prices of the tickets: ";
	console << loc.getPrices();
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

class Event {
	eventType event;
	char* name = nullptr;
	int date[3] = { 1,1, 2023 };	//date[0] - day, date[1] - month, date[2] - year
	string details = "";

	//for phase 2
	Location loc;

	const int MIN_LENGTH = 4;
	static int NO_EVENTS;	

public:

	string getEvent() {
		switch (event) {
		case eventType::FOOTBALL:
			return "FOOTBALL";
		case eventType::MOVIE:
			return "MOVIE";
		case eventType::THEATRE:
			return "THEATRE";
		case eventType::OTHER:
			return "OTHER";
		default:
			throw exception("Invalid input. Try again.");
		}
	}
	
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
		this->event = eventType::OTHER;
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

	Event(const Event& ev) {
		this->event = ev.event;
		this->setName(ev.name);
		for (int i = 0; i < 2; i++) {
			this->date[i] = ev.date[i];
		}
		this->details = ev.details;
		this->loc = ev.loc;
	}

	~Event() {
		delete[] this->name;
		Event::NO_EVENTS-=1;
	}

	void operator=(const Event& ev) {
		if (&ev == this) {
			return;
		}
		delete[] this->name;
		this->setName(ev.name);
	}

	Event operator++(int) {
		Event copy = *this;
		this->date[2] += 1;
		return copy;
	}

	Event operator++() {
		this->date[2] += 1;
		return *this;
	}

	friend void operator<<(ostream& console, Event& ev);
	friend void operator>>(istream& console, Event& ev);
};

void operator<<(ostream& console, Event& ev) {
	console << endl << "Name of the event" << ev.getName();
	console << endl << "The event is located at a/an: " << ev.getEvent();
	console << endl << "The event date is:";
	ev.printDate();
	console << endl << "Details about the event: ";
	console << endl << ev.details;
	console << endl << "More details about the event(regarding the location): ";
	//console << endl << ev.loc;
}

void operator>>(istream& console, Event& ev) {
	cout << endl << "Insert a name for the event:";
	char buffer[2000];
	console.getline(buffer, 2000);
	console.clear();
	ev.setName(buffer);
	cout << endl << "Insert the type of event you want to attend: ";
	int event;
	console >> event;
	ev.setEvent(event);
	cout << endl << "Insert date: ";
	for (int i = 0; i < 3; i++) {
		console >> ev.date[i];
	}
	cout << endl << "Insert details: ";
	console >> ev.details;
	cout << endl << "Get a location for the event: ";
	//console >> ev.loc;
}



class Room {
	int noRow;
	int noSeat;
	int maxRows=10;
	int maxSeats=10;//will be modified in phase 2
	bool isFull;
public:

	void setRow(int row) {
		if (row < 0 || row>10)
			throw exception("Error. Invalid row.");
		this->noRow = row;
	}

	void setSeat(int seat) {
		if (seat < 0 || seat>10)
			throw exception("Error. Invalid row.");
		this->noSeat = seat;
	}

	bool operator!(){
		return this->isFull == true;
	}

	friend void operator<<(ostream& console, Room& room);
	friend void operator>>(istream& console, Room& room);
};

 void operator<<(ostream& console, Room& room) {
	 console << "Rows available: ";
	 console << room.maxRows;
	 console << "Maximum seats per row: ";
	 console << room.maxSeats;
}
 void operator>>(istream& console, Room& room) {
	cout << "Select the row and seat you want:";
	cout << "Row number (0-10): ";
	console >> room.noRow;
	cout << "Seat number (0-10): ";
	console >> room.noRow;

}


class Ticket {
	unsigned int id;
	string nameOfBuyer;
	bool isValid;
	const int MIN_LENGTH = 4;
	category tickCat;

	//to be used for phase 2 i guess
	Room room;
	Event ev;
	Location loc;
	
public:

	void chechVal() {
		if (this->isValid) {
			cout << "The ticket is valid.";
		}
		else cout << "The ticket is unavailable";
	}

	void tickIsValid() {
		this->isValid = true;
	}

	void tickIsNotValid() {
		this->isValid = false;
	}

	void setName(string name) {
		if (name.length() < this->MIN_LENGTH) {
			throw exception("Invalid buyer name.");
		}
		this->nameOfBuyer = name;
	}

	string getCategory() {
		switch (this->tickCat) {
		case category::TIP1:
			return "TIP1";
		case category::TIP2:
			return "TIP2";
		case category::VIPORBOX:
			return "VIP/BOX";
		default:
			return "DISABILITIES";
		}
	}

	void setCategory(int input) {
		switch (input) {
		case 1:
			this->tickCat = category::TIP1;
			break;
		case 2:
			this->tickCat=category::TIP2;
			break;
		case 3:
			this->tickCat=category::VIPORBOX;
			break;
		default:
			this->tickCat=category::DISABILITIES;
			break;
		}
	}

	Ticket() {
		//since the id will be randomly generated, i will use rand() in phase 2. until then, I initialize with a default value
		this->id = 300;
		this->nameOfBuyer = "Unknown";
		this->tickCat = category::TIP1;
		this->tickIsValid();
	}

	Ticket(int id, string name, category cat) {
		this->id = id;
		this->setName(name);
		this->tickIsValid();
		this->tickCat = cat;
	}

	//phase 2
	~Ticket() {
	ev.~Event();
		this->tickIsNotValid();
	}


	friend void operator<<(ostream& console, Ticket& t);
	friend void operator>>(istream& console, Ticket& t);
};

void operator<<(ostream& console, Ticket& t) {
	console << endl << "Ticket id is: " << t.id;
	console << endl << "The name of the buyer: " << t.nameOfBuyer;
	console << endl << "The ticket type: " << t.getCategory();
	console << endl << "Ticket status: " << t.isValid;
};
void operator>>(istream& console, Ticket& t) {
	cout << "Enter name: ";
	console >> t.nameOfBuyer;
	cout << "Select which ticket you want: ";
	int input;
	console >> input;
	t.setCategory(input);
};