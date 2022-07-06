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
	void setTransfer();
};

Station::Station(string name,int route){
	this->name = name;
	this->route = route;
}

bool Station::isTransfer() {
	return route == -1;
}

void Station::setTransfer() {
	route = -1;
}

void Station::status() {
	cout<<name<<endl;
}

class Transfer {
	Station* station;
	vector<int> routes;
public:
	Transfer(){}
};

#endif //STATION