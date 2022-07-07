#include<iostream>
#include<algorithm>
#include<map>
#include<cstring>
#include"station.h"
#include"route.h"
#include"graphics.h"
#include"transfer.h"
#include"shortpath.h"
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
	if(!nodesTransfer.empty())
		preSteps();
}

void preSteps() {
	//get Distances...
	int firstId,secondId;
	vector<Station*> stationId;
	vector<int> time;
	int n = nodesTransfer.size();
	/*INICIALIZAR VARIABLES*/
	int** distances = new int*[n];
	int** paths = new int*[n];
	for(int j=0;j<n;j++) {
		distances[j] = new int[n];
		paths[j] = new int[n];
		for(int i=0;i<n;i++){
			paths[j][i] = i;
			if(j != i)
				distances[j][i] = INF;
			else
				distances[j][i] = 0;
		}
	}
	/*PRE-INICIAR VALORES*/
	for(Route* routePtr:routes){
		stationId.resize(0);
		time.resize(0);
		routePtr->getTimes(&stationId,&time);
		for(int i=0;i+1<stationId.size();i++){
			for(int j=0;j<nodesTransfer.size();j++){
				if(nodesTransfer[j]->station == stationId[i])
					firstId = j;
				if(nodesTransfer[j]->station == stationId[i+1])
					secondId = j;
			}
			distances[firstId][secondId] = time[i];
			distances[secondId][firstId] = time[i];
		}
	}
	fastesPath(n,distances,paths);
	//Calcular distancia de estacion x a nodos principales
	string name;
	Station *stPtr,*stPtr1,*stPtr2;
	fflush(stdin);
	cout<<"Estacion de Salida: ";
	getline(cin,name);
	stPtr1 = stationNames[name];
	/*for(int i=0;i<nodesTransfer.size();i++)
		if(stPtr == nodesTransfer[i]->station)
			firstId = i;*/

	cout<<"Estacion de Llegada: ";
	getline(cin,name);
	stPtr2 = stationNames[name];
	/*for(int i=0;i<nodesTransfer.size();i++)
		if(stPtr == nodesTransfer[i]->station)
			secondId = i;*/
	/*
		Calcular mejor opcion:
		LeftTransfer + toLeft
		RigthTransfer + toRight
	*/
	int routeId;
	int leftDepartTrans,leftArriveTrans,rightDepartTrans,rightArriveTrans;
	int leftDepart,rightDepart,leftArrive,rightArrive;
	Station *leftTrans,*rightTrans;
	//stPtr = nodesTransfer[firstId]->station;
	routeId = stPtr1->getRoute();
	routes[routeId]->findDistances(stPtr,&leftDepart,&rightDepart,&leftTrans,&rightTrans);

	//DEPARTS
	if(leftTrans==NULL)
		leftDepartTrans = -1;
	if(rightTrans==NULL)
		rightDepartTrans = -1;
	for(int i=0;i<nodesTransfer.size();i++)
		if(leftTrans == nodesTransfer[i]->station)
			leftDepartTrans = i;
		else if(rightTrans == nodesTransfer[i]->station)
			rightDepartTrans = i;

	//stPtr = nodesTransfer[secondId]->station;
	routeId = stPtr2->getRoute();
	routes[routeId]->findDistances(stPtr,&leftArrive,&rightArrive,&leftTrans,&rightTrans);

	//ARRIVALS
	if(leftTrans==NULL)
		leftArriveTrans = -1;
	if(rightTrans==NULL)
		rightArriveTrans = -1;
	for(int i=0;i<nodesTransfer.size();i++)
		if(leftTrans == nodesTransfer[i]->station)
			leftArriveTrans = i;
		else if(rightTrans == nodesTransfer[i]->station)
			rightArriveTrans = i;

	/*CALCULOS PREVIOS A RESPUESTA*/
	int minDistance,d,t;
	string terminator;
	minDistance = INF;
	if(leftDepartTrans!=-1 && leftArriveTrans!=-1){
		d = distances[leftDepartTrans][leftArriveTrans];
		t = d+leftDepart+leftArrive;
		minDistance = min(minDistance, t);
		name = nodesTransfer[leftDepartTrans]->station->getName();
		terminator = nodesTransfer[rightArriveTrans]->station->getName();
	}
	if(leftDepartTrans!=-1 && rightArriveTrans!=-1){
		d = distances[leftDepartTrans][rightArriveTrans];
		t = d+leftDepart+rightArrive;
		minDistance = min(minDistance, t);
		name = nodesTransfer[leftDepartTrans]->station->getName();
		terminator = nodesTransfer[rightArriveTrans]->station->getName();
	}
	if( rightDepartTrans!=-1 && leftArriveTrans!=-1){
		d = distances[rightDepartTrans][leftArriveTrans];
		t = d+rightDepart+leftArrive;
		minDistance = min(minDistance, t);
		name = nodesTransfer[rightDepartTrans]->station->getName();
		terminator = nodesTransfer[leftArriveTrans]->station->getName();
	}
	if( rightDepartTrans!=-1 && rightArriveTrans!=-1){
		d = distances[rightDepartTrans][rightArriveTrans];
		t = d+rightDepart+rightArrive;
		minDistance = min(minDistance, t);
		name = nodesTransfer[rightDepartTrans]->station->getName();
		terminator = nodesTransfer[rightArriveTrans]->station->getName();
	}

	cout<<endl;
	cout<<"Tiempo Minimo: "<<minDistance<<endl;
	/*RUTA OPTIMA*/
	cout<<"Ruta Optima: "<<stPtr1->getName()<<" -> ";
	while(firstId != secondId){
		name = nodesTransfer[firstId]->station->getName();
		cout<<name<<" -> ";
		firstId = paths[firstId][secondId];
	}
	name = nodesTransfer[firstId]->station->getName();
	cout<<name<<" -> "<<stPtr2->getName()<<endl;

	/*FREE MEMORY USED*/
	for(int i=0;i<n;i++){
		delete distances[i];
		delete paths[i];
	}
	delete [] distances;
	delete [] paths;
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
	cout<<"Mostrar Rutas: "<<endl;
	for(Transfer* node:nodesTransfer){
		node->showRoutes();
	}
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
	/*OBTENER DATOS DE LA RUTA*/
	fflush(stdin);
	cout<<"Datos de Ruta <PRECIO N_DE_ESTACIONES>: ";
	cin>>price>>nStations;
	cout<<endl;
	/*CREAR NUEVA RUTA*/
	Route* routePtr = new Route(price);
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
	times.push_back(ac);
	routePtr->setTimes(times);
}