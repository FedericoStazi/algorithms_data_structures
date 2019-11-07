#include <bits/stdc++.h>
using namespace std;

struct item {
    int key, prior, cnt;
    item * l, * r;
    item() {}
    item (int key, int prior) : key(key), prior(prior), l(NULL), r(NULL) { }
};
typedef item * pitem;

int cnt(pitem t){
	return t ? t->cnt : 0;
}

void upd_cnt(pitem t){
	if(t)
		t->cnt=cnt(t->l)+cnt(t->r)+1;
}

void split (pitem t, int key, pitem & l, pitem & r) {
    if (!t)
        l = r = NULL;
    else if (key < t->key)
        split (t->l, key, l, t->l),  r = t;
    else
        split (t->r, key, t->r, r),  l = t;
    upd_cnt(t);
}   

void insert (pitem & t, pitem it) {
    if (!t)
        t = it;
    else if (it->prior > t->prior)
        split (t, it->key, it->l, it->r),  t = it;
    else
        insert (it->key < t->key ? t->l : t->r, it);
    upd_cnt(t);
}

void merge (pitem & t, pitem l, pitem r) {
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge (l->r, l->r, r),  t = l;
    else
        merge (r->l, l, r->l),  t = r;
    upd_cnt(t);
}

void erase (pitem & t, int key) {
    if(!t)
        return;
    if (t->key == key)
        merge (t, t->l, t->r);
    else
        erase (key < t->key ? t->l : t->r, key);
    upd_cnt(t);
}

bool find(pitem t, int key){
	if(!t)
		return false;
	else if (t->key==key)
		return true;
	else
		return find(t->key > key ? t->l : t->r, key);
}

pitem T=NULL;
int a;

int main(){

    cin>>a;
	if(!find(T,a));
		insert(T,new item(a,rand()));
	erase(T,a);
	find(T,a);

}