#ifndef ROUTE
#define ROUTE

#include<iostream>
#include<vector>
#include"station.h"
using namespace std;

class Route {
	string name;
	vector<Station*> stations;
	vector<int> times;
	int price;
	//tiempo
public:
	Route(string name,int price);
	~Route();
	void setStations(vector<Station*> st);
	void setTimes(vector<int> time);
	void status();
	int getTime(int a,int b);
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

/*SETTERS Y GETTERS*/
int Route::getTime(int a,int b) {
	return abs(times[b] - times[a]);
}
void Route::setStations(vector<Station*> st) {
	stations = st;
}
void Route::setTimes(vector<int> time) {
	times = time;
}
#endif //ROUTE