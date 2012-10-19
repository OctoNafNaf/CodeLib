#include <iostream>
using namespace std;

template <class K, class V>
class node;

template <class K, class V>
class map_index;

template <class K, class V>
class map;

template <class K, class V>
class node {
public:
    node *l, *r;
    bool red;
    K key;
    V val;

    node() :
        red(true) {
        l = r = NULL;
    }

    node(K k, V v) :
        red(true), key(k), val(v) {
        l = r = NULL;
    }
};

template <class K, class V>
class map_index {
public:
    map<K, V> *mp;
    K index;

    map_index(map<K, V> *m, K i) :
        mp(m), index(i) {}

    V operator = (V v) {
        mp->insert(index, v);
        return v;
    }

    operator V () {
        node<K, V> *n = mp->find(index);
        return (n == NULL ? V() : n->val);
    }
};

template <class K, class V>
class map {
    typedef node<K, V> knode;

    knode *root;

    bool red(knode *x) {
        return (x == NULL ? false : x->red);
    }

    void rotRight(knode *&x) {
        knode *y = x->l;
        x->l = y->r;
        y->r = x;
        x = y;
    }

    void rotLeft(knode *&x) {
        knode *y = x->r;
        x->r = y->l;
        y->l = x;
        x = y;
    }

    void insert(knode *&t, knode *x, bool d) {
        if (t == NULL) {
            t = x;
            return;
        }
        if (red(t->l) && red(t->r)) {
            t->red = true;
            t->l->red = t->r->red = false;
        }
        if (x->key == t->key)
            t->val = x->val;
        else if (x->key < t->key) {
            insert(t->l, x, false);
            if (red(t) && red(t->l) && d)
                rotRight(t);
            if (red(t->l) && red(t->l->l)) {
                rotRight(t);
                t->red = false;
                t->r->red = true;
            }
        } else {
            insert(t->r, x, true);
            if (red(t) && red(t->r) && !d)
                rotLeft(t);
            if (red(t->r) && red(t->r->r)) {
                rotLeft(t);
                t->red = false;
                t->l->red = true;
            }
        }
    }

    knode* find(knode *t, K k) {
        if (t != NULL) {
            if (k == t->key)
                return t;
            else if (k < t->key)
                return find(t->l, k);
            else
                return find(t->r, k);
        }
        return NULL;
    }

public:

    map() :
        root(NULL) {}

    knode* find(K k) {
        return find(root, k);
    }

    void insert(K k, V v) {
        insert(root, new knode(k, v), false);
        root->red = false;
    }

    map_index<K, V> operator [] (K i) {
        return map_index<K, V>(this, i);
    }
};

int main() {
    map<string, int> m;
    m["abc"] = 345;
    m["def"] = 121;
    m["ghi"] = 756;
    cout << m["def"];
    return 0;
}
