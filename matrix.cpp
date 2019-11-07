#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

vector<int> mult(vector<int> A, pii a, vector<int> B, pii b){
	
	assert(a.second==b.first);

	vector<int> V(a.first*b.second);

	for(int i=0;i<a.first;i++)
		for(int k=0;k<a.second;k++) // <-- placing this for here makes the program faster (~50%)
			for(int j=0;j<b.second;j++)
				V[b.second*i+j]+=A[a.second*i+k]*B[b.second*k+j];

	return V;
}

vector<int> pot(vector<int> A, pii a, int k){

	if(k==1)
		return A;

	vector<int> V;
	V=pot(A, a, k/2);

	V=mult(V, a, V, a);

	if(k%2)
		return mult(V, a, A, a);
	else
		return V;
}

void stampa(vector<int> A, pii a){

	for(int i=0;i<a.first;i++){
		for(int j=0;j<a.second;j++)
			cout<<A[i*a.second+j]<<" ";
		cout<<endl;
	}
}


int main(){

	//Moltiplicazione

	pii x,y;

	cin>>x.first>>x.second;
	vector<int> X(x.first*x.second);

	for(int i=0;i<x.first;i++)
		for(int j=0;j<x.second;j++)
			cin>>X[i*x.second+j];

	cin>>y.first>>y.second;
	vector<int> Y(y.first*y.second);

	for(int i=0;i<y.first;i++)
		for(int j=0;j<y.second;j++)
			cin>>Y[i*y.second+j];

	stampa(mult(X,x,Y,y),{x.first,y.second});

	//Fibonacci

	int k;
	cin>>k;

	pii x={2,2};
	vector<int> X(4);
	X[0]=0;
	X[1]=X[2]=X[3]=1;

	pii y={2,1};
	vector<int> Y(2);
	Y[0]=0;
	Y[1]=1;

	for(int i=1;i<k+1;i++)
		cout<<mult(pot(X, x, i), x, Y, y)[0]<<endl;

}