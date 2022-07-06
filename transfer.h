#ifndef TRANSFER
#define TRANSFER

#include"station.h"
//As polimorphism or class with pointer?
class Transfer {
	vector<int> routes;
	vector<int> distances;
public:
	Station* station;
	Transfer(Station* s);
	~Transfer();
	void status();
	void addRoute(int id);
	void showRoutes();
	vector<int> getRoutes();
};

vector<int> Transfer::getRoutes(){
	return routes;
}
Transfer::Transfer(Station* s) {
	station = s;
}
Transfer::~Transfer() {
	delete station;
}
void Transfer::showRoutes() {
	for(int i:routes)
		cout<<i<<' ';
	cout<<endl;
}
void Transfer::status() {
	station->status();
}
void Transfer::addRoute(int id) {
	routes.push_back(id);
}
#endif //TRANSFER