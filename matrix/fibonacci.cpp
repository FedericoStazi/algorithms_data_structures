#include "matrix.cpp"
using namespace std;

long long int int_fibonacci(long long int k){
    matrix<long long int> a(2,2);
    a.set(0,1,1), a.set(1,0,1), a.set(1,1,1);
    return a.pow(k).get(1,1);
}

long double double_fibonacci(long long int k){
    matrix<long double> a(2,2);
    a.set(0,1,1), a.set(1,0,1), a.set(1,1,1);
    return a.pow(k).get(1,1);
}

int main(){

    //first fibonacci numbers
    for(int i=0; i<20; i++)
        cout<<int_fibonacci(i)<<" ";
    cout<<endl;

    //really big fibonacci number (incorrect because of integer overflow)
    cout<<int_fibonacci(1e18)<<endl;

    //biggest fibonacci number using long doubles
    cout<<double_fibonacci(23600)<<endl;

}
