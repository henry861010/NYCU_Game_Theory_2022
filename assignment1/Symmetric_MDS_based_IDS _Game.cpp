#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

struct ans{
	int move_count;
	int number;
};

void ws(int n,double p,int k,vector<vector<int>> &arr){
	//builde ring lattice
	for(int i{0};i<n;i++){
		//cout<<"test2"<<endl;
		for(int l{0};l<(k+1);l++){
			int j=((int)(n+l+i-ceil(k/2)))%n;
			//cout<<"test i-"<<i<<" j-"<<j<<endl;
			if(i!=j){
				if((double)rand()/(RAND_MAX+1.0)<p){
					int new_{i};
					while(new_==i or new_==j){  //new_==j equal to origin
						new_=rand()%n;
					}
					arr[i][new_]=1;
					arr[new_][i]=1;
				}
				else{
					arr[i][j]=1;
					arr[j][i]=1;
				}
			}
			else{
				arr[i][j]=0;
			}
		}
	}
}

int utility(vector<vector<int>> & arr,vector<bool> &strategy,int i,int choose,int n){
    const int b{1};
    const int a{2};
    const int r{1+a*n};
    //r>na  a>b>0 a>1
    
    if(choose==0) return 0; //if "choose" return 0
    
    int w{0};
    for(int j{0};j<n;j++){
		if(j!=i) w=w+r*strategy[j]*1*arr[i][j];
	}
    
    int G{0};
	for(int j{0};j<n;j++){
        int v{0};
        for(int k{0};k<n;k++){
            v=v+strategy[k]*arr[i][j];
        }
        if(v==1) G=G+a;
	}
	return G-b-w;
}

ans ids(int n,vector<vector<int>> & arr){
	vector<bool> strategy(n,0);
	int move_count{0};
	vector<bool> if_ne(n,false);
	int ne{0};
	
	//randomize initial game state
	for(int j{0};j<n;j++){
		strategy[j]=rand()%2;  
	}
	//find NE
	while(ne<n){
		int i=rand()%n;
		bool recent_strategy{strategy[i]};
        //cout<<"test2 "<<"i:"<<i<<" utility(no):"<<utility(arr,strategy,i,0,n)<<" utility(yes):"<<utility(arr,strategy,i,1,n)<<"  ne:"<<ne<<endl;
		if(utility(arr,strategy,i,0,n)>utility(arr,strategy,i,1,n)){  //select "not choose" better than "choose"
			if(recent_strategy!=false){
				for(int j{0};j<n;j++){   //initialize if_ne
					if_ne[j]=false;
				}
				ne=1;   //(true->false)entire condition change re
				if_ne[i]=true;
				move_count++; 
				strategy[i]=false;
			}
			else if(!if_ne[i]){ //avoid last i equal to this time i
				ne++;
				if_ne[i]=true; 
			}
		}
		else{  //select "choose" better than "not choose"
			if(recent_strategy!=true){
				for(int j{0};j<n;j++){   //initialize if_ne
					if_ne[j]=false;
				}
				ne=1;   //(true->false)entire condition change re
				if_ne[i]=true;
				move_count++; 
				strategy[i]=true;
			}
			else if(!if_ne[i]){ //avoid last i equal to this time i
				ne++;
				if_ne[i]=true;
			}
		}
	}
	
	
	//vertify that the game state is a valid solution
	for(int i{0};i<n;i++){
		for(int j{0};j<n;j++){
			if(arr[i][j] and strategy[i] and strategy[j]){
				cout<<"false"<<endl;
			}
		}
	}
	
	//calculate number in mis
	int number{0};
	for(int i{0};i<n;i++){
		if(strategy[i]) number++;
	}
	return ans{move_count,number};
}

int main(){
	int n{30};
	int k{4};
	int number{0};
	int move{0};
    srand( time(NULL) );
    /*
    for(int i{0};i<n;i++){
        for(int j{0};j<n;j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
    ans aa=mis(n,arr);
    */
	
	for(double p{0};p<1.0;p=p+0.2){
		for(int b{0};b<100;b++){
			vector<vector<int>> arr(n,vector<int>(n,0));
			ws(n,p,k,arr);
			ans aa=mis(n,arr);
			number=number+aa.number;
			move=move+aa.move_count;
			//cout<<"p:"<<p<<"~"<<b<<"move:"<<aa.move_count<<" mis:"<<aa.number<<endl;
		}
	}
	cout<<"move_count:"<<move/100<<"  cadinality:"<<number/100;

	system("pause");
	return 0;
}