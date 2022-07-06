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
	cout<<"Mostrar rutas: "<<endl;
	for(Transfer* node:nodesTransfer){
		node->showRoutes();
	}
}

void router() {
	int nRoutes;
	cout<<"Numero de Rutas: ";
	cin>>nRoutes;
	for(int i=0;i<nRoutes;i++){
		setRoute();
		routes[i]->status();
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
	//cout<<"Datos de ruta <NOMBRE PRECIO ESTACIONES>: ";
	cout<<"Nombre de ruta: ";
	getline(cin,name);
	cout<<"Precio del boleto: $";
	cin>>price;
	cout<<"Numero de estaciones: ";
	cin>>nStations;
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
	ac = 0;
	for(int i=0;i<nStations;i++) {
		fflush(stdin);
		cout<<"Nombre de estacion: ";
		getline(cin,name);
		times.push_back(ac);
		if(i+1 < nStations){
			cout<<"Tiempo para siguiente estacion: ";
			cin>>temp;
			ac += temp;
		}
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
	routePtr->setTimes(times);
}