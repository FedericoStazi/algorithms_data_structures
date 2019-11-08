#include <iostream>
#include <assert.h>
using namespace std;

template<
    class data_type,
    class update_type,
    data_type upd_fn (update_type, long long int, long long int),
    data_type join (data_type, data_type, long long int, long long int),
    data_type identity,
    update_type lazy_join (update_type, update_type, long long int, long long int),
    update_type lazy_identity
>
class segment_tree{

private:

    data_type data;
    update_type lazy_data;
    bool lazy_flag;

    long long int range_begin, range_end, size;
    segment_tree *left, *right;

public:

    template<class iter>
    segment_tree(iter begin_it, iter end_it, long long int offset = 0){

        range_begin = offset;
        range_end = offset + (end_it - begin_it);
        size = end_it - begin_it;

        lazy_flag = false;
        lazy_data = lazy_identity;

        if(size == 1){
            data = *begin_it;
            left = right = NULL;
        }
        else{
            left = new segment_tree<data_type, update_type, upd_fn, join, identity, lazy_join, lazy_identity> (begin_it, begin_it + (size+1)/2, offset);
            right = new segment_tree<data_type, update_type, upd_fn, join, identity, lazy_join, lazy_identity> (begin_it + (size+1)/2, end_it,   offset + (size+1)/2);
            data = join(left->data, right->data, range_begin, range_end);
        }
    }

    void propagate(){

        if(!lazy_flag)
            return;

        data = upd_fn(lazy_data, range_begin, range_end);
        if(left){
            left->lazy_flag = true;
            left->lazy_data = lazy_join(left->lazy_data, lazy_data, range_begin, range_end);
        }
        if(right){
            right->lazy_flag = true;
            right->lazy_data = lazy_join(right->lazy_data, lazy_data, range_begin, range_end);
        }

        lazy_data = lazy_identity;
        lazy_flag = false;

    }

    data_type query(long long int query_begin, long long int query_end){

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

    data_type query(long long int query_begin){
        return query(query_begin, query_begin+1);
    }

    void update(long long int query_begin, long long int query_end, update_type query_data){

        propagate();

        if(range_end <= query_begin || query_end <= range_begin){
            return;
        }
        else if(query_begin <= range_begin && range_end <= query_end){
            lazy_data = query_data;
            lazy_flag = true;
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

    void update(long long int query_begin, data_type query_data){
        update(query_begin, query_begin+1, query_data);
    }

    void DEBUG_PRINT(long long int x = 0){
        for(long long int i=0; i<x; i++)
            cout<<"\t";
        cout<<data<<" "<<lazy_data<<" "<<range_begin<<" "<<range_end<<"\n";
        if(left) left->DEBUG_PRINT(x+1);
        if(right) right->DEBUG_PRINT(x+1);
    }

};
