#ifndef STATION
#define STATION

#include<iostream>
#include<vector>
using namespace std;

class Station {
	string name;
	int route;
public:
	Station(string name,int route);
	void status();
	bool isTransfer();
	int setTransfer();
	string getName();
};

Station::Station(string name,int route){
	this->name = name;
	this->route = route;
}

bool Station::isTransfer() {
	return route == -1;
}

int Station::setTransfer() {
	int tmp = route;
	route = -1;
	return tmp;
}

void Station::status() {
	cout<<name<<endl;
}
string Station::getName() {
	return name;
}

#endif //STATION