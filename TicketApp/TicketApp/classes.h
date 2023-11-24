#pragma once
#include <iostream>
#include <string.h>

using namespace std;

enum eventType { FOOTBALL = 1, MOVIE = 2, THEATRE = 3, OTHER = 4 };		//makes it easier to select options(at least for now)
enum category { TIP1 = 1, TIP2 = 2, VIPORBOX = 3, DISABILITIES = 4 };	//default for every type of event, i think it is obsolete, but i will keep this for now

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
};

class Location {

	string name = "";
	int catPrices[4]; //list of prices for each event
	int CAPACITY;		//to be made static

public:
	Location() {
		for (int i = 0; i < 4; i++) {
			this->catPrices[i] = 0;
		}
		this->CAPACITY = 100;
		this->name = "None";
	}

	int& operator[](int index) {	//assigns another price for a specific ticket
		if (index < 0 || index>4) {
			throw exception("Invalid ticket type.");
		}
		return this->catPrices[index];
	}
};

class Event {
	eventType event;
	char* name = nullptr;
	int date[3] = { 1,1, 2023 };	//date[0] - day, date[1] - month, date[2] - year
	string details = "";
	Location loc;

	const int MIN_LENGTH = 4;
	int NO_EVENTS;	//will change it to static
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

	void setEvent(int input) {		//not an actual getter, damn
		if (input < 1 || input > 4)
			throw exception("Invalid number. Please enter another number.");
		this->event = (eventType)input;
	}

	Event():details("None") {
		this->event = OTHER;
		this->setName("Unknown");
		NO_EVENTS+=1;
	}

	~Event() {
		delete[] this->name;
		NO_EVENTS-=1;
	}
};

class Room {
	int** roomSeats=nullptr;	//matrix which stores if a seat is taken(1) or not(0)
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
	int NO_TICKETS;

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
		NO_TICKETS+=1;
		this->setName("John Doe");
		this->tickIsvalid();
	}
};
