#include<iostream>
#include<map>
#include"station.h"
#include"route.h"
#include"graphics.h"
using namespace std;

map<string,Station*> stationNames;
vector<Station*> nodesTransfer;
vector<Route*> routes;

void test();
void routine();
void setRoute();
void setStations();
void deleteAll();
vector<Station*> setStations(int nStations,int idRoute);

int main() {
	test();
	deleteAll();
	return 0;
}

void test(){
	routine();
}

void routine() {
	int nRoutes;
	cout<<"Numero de Rutas: ";
	cin>>nRoutes;
	for(int i=0;i<nRoutes;i++){
		setRoute();
		routes[i]->status();
	}
	cout<<"Nodos Transbordo: "<<endl;
	for(int i=0;i<nRoutes;i++)
		nodesTransfer[i]->status();
}

void deleteAll() {
	/*LIBERAR MEMORIA*/
	for(Route* node:routes)
		delete node;
	for(Station* node:nodesTransfer)
		delete node;
}

void setRoute() {
	int nStations,price;
	string name;
	/*OBTENER DATOS DE LA RUTA*/
	cout<<"Nombre de ruta: ";
	getline(cin,name);
	cout<<"Precio del boleto: $";
	cin>>price;
	cout<<"Numero de estaciones: ";
	cin>>nStations;
	cout<<endl;
	/*CREAR NUEVA RUTA*/
	Route* routePtr = new Route(name,price);
	routePtr->setStations(setStations(nStations,routes.size()));
	routes.push_back(routePtr);
}

vector<Station*> setStations(int nStations,int idRoute) {
	vector<Station*> stations;
	string name;
	/*LECTURA DE ESTACIONES*/
	for(int i=0;i<nStations;i++) {
		fflush(stdin);
		cout<<"Nombre de estacion: ";
		getline(cin,name);
		if(stationNames.find(name) == stationNames.end()) //Nueva estacion
			stationNames[name] = new Station(name,idRoute);
		else { //Estacion existente
			cout<<name<<": is a Transfer"<<endl;
			nodesTransfer.push_back(stationNames[name]);
			stationNames[name]->setTransfer();
		}
		stations.push_back(stationNames[name]);
	}
	return stations;	
}