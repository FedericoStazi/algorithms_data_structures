#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

template <class data>
class matrix{

private:

    int height, width;
    pair<int,int> size;
    vector<data> cells;

public:

    matrix(int h, int w) : height (h), width (w) {
        size = make_pair(height, width);
        cells = vector<data>(height*width);
    }

    matrix(pair<int,int> s) : matrix(s.first, s.second) {}

    void set(int i, int j, data v){
        cells[i*size.second + j] = v;
    }

    data get(const int i, const int j) const {
        return cells[i*size.second + j];
    }

    matrix<data> identity (int k){

        matrix<data> res(k, k);

        for(int i=0; i<k; i++)
            res.set(i, i, 1);

        return res;

    }

    matrix<data> operator + (matrix<data> const& term){

        assert(size == term.size);
        matrix<data> res(size);
        cout<<res.size.first<<" "<<res.size.second<<endl;


        for(int i=0; i<size.first; i++)
            for(int j=0; j<size.second; j++)
                res.set(i,j, get(i,j) + term.get(i,j));

        return res;

    }

    matrix<data> operator * (matrix<data> const& term){

    	assert(size.second==term.size.first);

    	matrix<data> res(size.first, term.size.second);

    	for(int i=0; i<res.size.first; i++)
            for(int j=0; j<res.size.second; j++)
                for(int k=0; k<size.second; k++)
    				res.set(i,j, res.get(i,j) + get(i,k)*term.get(k,j));

    	return res;
    }

    matrix<data> pow (long long int k){

        assert(size.first == size.second);
        assert(k >= 0);

        if(k == 0)
            return identity(size.first);
        else{
            return ( (k%2) ? *this : identity(size.first) ) * ( (*this) * (*this) ).pow(k/2);
        }

    }

    void print(){

    	for(int i=0; i<size.first; i++){
    		for(int j=0; j<size.second; j++)
    			cout<<get(i,j)<<" ";
    		cout<<endl;
    	}
    }

};
