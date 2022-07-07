#ifndef FLOYD_WARSHALL
#define FLOYD_WARSHALL

#include<iostream>
#include<cstring>
using namespace std;

#include<iostream>
using namespace std;
#define INF 1000

void fastesPath(int nodes,int** distances,int** paths) {
	int sum;
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
}

#endif //FLOYD_WARSHALL