#ifndef ROUTE
#define ROUTE

#include<iostream>
#include<vector>
#include"station.h"
#include"transfer.h"
using namespace std;

class Route {
	vector<Station*> stations;
	vector<int> times;
	int price;
	//Mis transbordos
public:
	Route(int price);
	~Route();
	void setStations(vector<Station*> st);
	void setTimes(vector<int> time);
	void status();
	int getTime(int a,int b);
	void getTimes(vector<Station*>* stationId,vector<int>* retTime);
};

Route::Route(int price) {
	this->price = price;
}

void Route::status() {
	cout<<"Ruta "<<stations[0]->getName()<<'-'<<
	stations[stations.size()-1]->getName()<<" $"<<
	price<<endl;
	for(Station* st:stations)
		st->status();
}

Route::~Route() {
	for(Station* s:stations)
		if(!s->isTransfer())
			delete s;
}

/*SETTERS Y GETTERS*/
void Route::getTimes(vector<Station*>* stationId,vector<int>* retTime) {
	Station* stPtr;
	int prev = -1;
	for(int index=0; index<stations.size(); index++) {
		stPtr = stations[index];
		if(stPtr->isTransfer()) {
			if(prev != -1)
				retTime->push_back(getTime(prev,index));
			prev = index;
			stationId->push_back(stPtr);
		}
	}
}
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