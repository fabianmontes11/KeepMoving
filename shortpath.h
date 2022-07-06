#ifndef FLOYD_WARSHALL
#define FLOYD_WARSHALL

#include<iostream>
#include<cstring>
using namespace std;

#include<iostream>
using namespace std;
#define INF 1000

void fastesPath(int nodes,int distances[10][10]) {
	int paths[10][10];
	int sum;
	for(int j=0;j<nodes;j++)
		for(int i=0;i<nodes;i++)
			paths[j][i] = i;
		
	for(int k=0;k<nodes;k++)
		for(int j=0;j<nodes;j++){
			if(j == k)
				continue;
			for(int i=0;i<nodes;i++)
				if(i != k) {
					sum = distances[j][k] + distances[k][i];
					if(sum < distances[j][i]){
						distances[j][i] = sum;
						paths[j][i] = k;
					}
				}
		}
	cout<<"Matriz de distancias: "<<endl;
	for(int i=0;i<nodes;i++){
		for(int j=0;j<nodes;j++)
			cout<<distances[i][j]<<' ';
		cout<<endl;
	}
	cout<<"Matriz de recorridos: "<<endl;
	for(int i=0;i<nodes;i++){
		for(int j=0;j<nodes;j++)
			cout<<paths[i][j]<<' ';
		cout<<endl;
	}
}

#endif //FLOYD_WARSHALL