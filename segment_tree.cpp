#include <iostream>
using namespace std;

template<
    class data_type,
    class update_type,
    data_type upd_fn (update_type, int, int),
    data_type join (data_type, data_type, int, int),
    data_type identity,
    update_type lazy_join (update_type, update_type, int, int),
    update_type lazy_identity
>
class segment_tree{

private:

    data_type data;
    update_type lazy_data;
    int range_begin, range_end, size;
    segment_tree *left, *right;

public:

    template<class iter>
    segment_tree(iter begin_it, iter end_it, iter tree_begin_it = NULL){

        if(!tree_begin_it)
            tree_begin_it = begin_it;

        range_begin = begin_it - tree_begin_it;
        range_end = end_it - tree_begin_it;
        size = end_it - begin_it;

        if(size == 1){
            data = *begin_it;
            lazy_data = lazy_identity;
            left = right = NULL;
        }
        else{
            left = new segment_tree<data_type, update_type, upd_fn, join, identity, lazy_join, lazy_identity> (begin_it, begin_it + (size+1)/2, tree_begin_it);
            right = new segment_tree<data_type, update_type, upd_fn, join, identity, lazy_join, lazy_identity> (begin_it + (size+1)/2, end_it, tree_begin_it);
            data = join(left->data, right->data, range_begin, range_end);
        }

    }

    void propagate(){

        data = upd_fn(lazy_data, range_begin, range_end);
        if(left)
            left->lazy_data = lazy_join(left->lazy_data, lazy_data, range_begin, range_end);
        if(right)
            right->lazy_data = lazy_join(right->lazy_data, lazy_data, range_begin, range_end);
        lazy_data = lazy_identity;
    }

    data_type query(int query_begin, int query_end){

        propagate();

        if(range_end <= query_begin || query_end <= range_begin){
            return identity;
        }
        else if(query_begin <= range_begin && range_end <= query_end){
            return data;
        }
        else{
            return join(
                left ? left->query(query_begin, query_end) : identity,
                right ? right->query(query_begin, query_end): identity,
                range_begin, range_end
            );
        }
    }

    void update(int query_begin, int query_end, update_type query_data){

        propagate();

        if(range_end <= query_begin || query_end <= range_begin){
            return;
        }
        else if(query_begin <= range_begin && range_end <= query_end){
            lazy_data = query_data;
            propagate();
        }
        else{
            if(left)
                left->update(query_begin, query_end, query_data);
            if(right)
                right->update(query_begin, query_end, query_data);
            data = join(
                left ? left->data : identity,
                right ? right->data : identity,
                range_begin, range_end
            );
        }
    }

    void update(int query_begin, data_type query_data){
        update(query_begin, query_begin+1, query_data);
    }
};

int sum(int a, int b, int x, int y){
    return a+b;
}

int set(int k, int x, int y){
    return (y-x)*k;
}

int main(){

    int a[] = {1, 2, 3};
    segment_tree<int, int, set, sum, 0, sum, 0> tree(a, a+3);

    for(int i=0; i<3; i++) cout<<tree.query(i,i+1)<<" "; cout<<endl;

    tree.update(2, 5);

    for(int i=0; i<3; i++) cout<<tree.query(i,i+1)<<" "; cout<<endl;
}
