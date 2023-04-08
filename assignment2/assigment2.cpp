#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <climits>
using namespace std;

#define strategyN 2;


void fictious(vector<vector<vector<int>>> &matrix,vector<int> &belief1,vector<int> &belief2){   //matrix strategyofplayer1 strategyofplayer2 payyoffofeachplayer
	int counter{0};

	while(counter<10000){

		//player1 best respond
		int max1{INT_MIN};
		int bestrespond1{-1};
		for(int i{0};i<strategyN;i++){    
			int temp{0};
			for(int j{0};j<strategyN;j++){    
				temp=temp+belief1[j]*matrix[i][j][1];
			}
			if((temp>max1) or (temp=max1 and rand()%2)){
				max1=temp;
				bestrespond1=i;
			}
		}
		if(bestrepond1>-1) belief2[bestrespond1]++;

		//plater2 best respond
		int max2{INT_MIN};
		int bestrespond2{-1};
		for(int i{0};i<strategyN;i++){   
			int temp{0};
			for(int j{0};j<strategyN;j++){     
				strategypayoff1[i]=strategypayoff1[i]+belief2[j]*matrix[j][i][2];
			}
			if((temp>max2) or (temp=max1 and rand()%2)){
				max2=temp;
				int bestrespond2{i};
			}
		}
		if(bestrepond2>-1) belief1[bestrespond2]++;

		counter++;
	}
	cout<<"strategy of player1:"<<endl;
	cout<<"		strayegy1-"<<belief2[1]<<"  strayegy2-"<<belief2[2]<<endl;
	cout<<"strategy of player2:"<<endl;
	cout<<"		strayegy1-"<<belief1[1]<<"  strayegy2-"<<belief1[2]<<endl;
}


int main(){
	srand( time(NULL) );

	vector<vector<vector<int>>> matrix
	{
		{{-1,-1},{1,0}},
		{{0,1},{3,3}}
	};
	int happen{rand()%10};
	int random1 {rand()%happen};
	int random2 {rand()%happen};
	vector<int> belief1{happen-random1,random1};
	vector<int> belief2{happen-random2,random2};

	fictious(matrix,belief1,belief2);

	system("pause");
	return 0;
}