#include "segment_tree.cpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int sum(int a, int b, long long int x, long long int y){
    return a+b;
}

int set(int k, long long int x, long long int y){
    return (y-x)*k;
}

int lazy_set(int a, int k, long long int x, long long int y){
    return k;
}

int small_rand(){
    return rand()%100;
}

template <class iter>
int slow_query(iter a, iter b){
    return accumulate(a,b,0);
}

template <class iter>
int slow_update(iter a, iter b, int x){
    fill(a,b,x);
}

void test(bool slow_operations, int vector_size, int queries_number){

    vector<int> a(vector_size, 0);
    generate(a.begin(), a.end(), small_rand);
    segment_tree<int, int, set, sum, 0, lazy_set, 0> tree(a.begin(), a.end());

    while(queries_number--){

        if(rand()%2){

            int x = rand()%vector_size;
            int y = x + rand()%(vector_size-x) + 1;

            if(slow_operations)
                assert(slow_query(a.begin()+x, a.begin()+y) == tree.query(x,y));
            else
                tree.query(x,y);
        }
        else{

            int v = small_rand();
            int x = rand()%vector_size;
            int y = x + rand()%(vector_size-x) + 1;

            if(slow_operations)
                slow_update(a.begin()+x, a.begin()+y, v);
            tree.update(x, y, v);
        }
    }
}



int main(){

    int x = clock();
    test(false, 1000000, 1000000);
    cout<<((float)(clock()-x)/CLOCKS_PER_SEC);

}
