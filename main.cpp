#include<iostream>
#include<algorithm>
#include<map>
#include"station.h"
#include"route.h"
#include"graphics.h"
#include"transfer.h"
using namespace std;

map<string,Station*> stationNames;
vector<Transfer*> nodesTransfer;
vector<Route*> routes;

void test();
void router();
void setRoute();
void setStations();
void deleteAll();
void setStations(int nStations);
void preSteps();

int main() {
	test();
	deleteAll();
	return 0;
}

void test(){
	router();
	preSteps();
}

void preSteps() {
	cout<<"Mostrar Rutas: "<<endl;
	for(Transfer* node:nodesTransfer){
		node->showRoutes();
	}
}

void router() {
	int nRoutes;
	cout<<"Numero de Rutas: ";
	cin>>nRoutes;
	cout<<endl;
	for(int i=0;i<nRoutes;i++){
		setRoute();
		cout<<endl;
		routes[i]->status();
		cout<<endl;
	}
	cout<<"Nodos Transbordo: "<<endl;
	for(int i=0;i<nodesTransfer.size();i++)
		nodesTransfer[i]->status();
}

void deleteAll() {
	/*LIBERAR MEMORIA*/
	for(Route* node:routes)
		delete node;
	for(Transfer* node:nodesTransfer)
		delete node;
}

void setRoute() {
	int nStations,price;
	string name;
	/*OBTENER DATOS DE LA RUTA*/
	fflush(stdin);
	cout<<"Datos de Ruta <NOMBRE PRECIO ESTACIONES>: ";
	cin>>name>>price>>nStations;
	cout<<endl;
	/*CREAR NUEVA RUTA*/
	Route* routePtr = new Route(name,price);
	routes.push_back(routePtr);
	setStations(nStations);
}

void setStations(int nStations) {
	vector<Station*> stations;
	vector<int> times;
	string name;
	int temp,ac;
	int idRoute = routes.size()-1;
	Route* routePtr = routes[idRoute];
	/*LECTURA DE ESTACIONES*/
	for(int i=0;i<nStations;i++) {
		fflush(stdin);
		cout<<"Nombre de estacion: ";
		getline(cin,name);		
		if(stationNames.find(name) == stationNames.end()) //Nueva estacion
			stationNames[name] = new Station(name,idRoute);
		else if(!stationNames[name]->isTransfer()) { //Estacion existente
			Transfer* transPtr = new Transfer(stationNames[name]);
			cout<<name<<": is a Transfer"<<endl;
			nodesTransfer.push_back(transPtr);
			transPtr->addRoute(stationNames[name]->setTransfer());
			transPtr->addRoute(idRoute);
		} else {
			int index;
			Transfer* transPtr;
			for(index=0; index<nodesTransfer.size();index++)
				if(nodesTransfer[index]->station == stationNames[name]){
					transPtr = nodesTransfer[index];
					break;
				}
			transPtr->addRoute(idRoute);
		}
		stations.push_back(stationNames[name]);
	}
	routePtr->setStations(stations);
	
	ac = 0;
	br();
	cout<<"Tiempos de Viaje"<<endl;
	for(int i=0;i+1<nStations;i++){
		cout<<stations[i]->getName()<<" -> "<<stations[i+1]->getName()<<": ";
		times.push_back(ac);
		cin>>temp;
		ac += temp;
	}
	routePtr->setTimes(times);
}