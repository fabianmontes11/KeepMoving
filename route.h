#ifndef ROUTE
#define ROUTE

#include<iostream>
#include<vector>
#include"station.h"
using namespace std;

class Route {
	string name;
	vector<Station*> stations;
	int price;
	//tiempo
public:
	Route(string name,int price);
	~Route();
	void setStations(vector<Station*> v);
	void status();
};

Route::Route(string name,int price) {
	this->name = name;
	this->price = price;
}

void Route::status() {
	cout<<"Ruta: "<<name<<endl;
	for(Station* st:stations)
		st->status();
}

Route::~Route() {
	for(Station* s:stations)
		if(!s->isTransfer())
			delete s;
}

void Route::setStations(vector<Station*> v) {
	stations = v;
}

#endif //ROUTE