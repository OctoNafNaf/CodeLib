#include <iostream>
using namespace std;

template <class T> class clindex;
template <class T> class clarray;

template <class T>
class clindex {
    clarray<T> *arr;
    size_t index;
    
public:
    clindex(clarray<T> *a, size_t i) :
        arr(a), index(i) {}
        
    operator T () {
        return arr->get(index);
    }
    
    T operator = (T v) {
        arr->set(index, v);
        return v;
    }
};

template <class T>
class clarray {
    T *data;
    int *t, time, cleartime;
    size_t sz;

public:
    clarray(size_t s) {
        sz = s;
        cleartime = time = 0;
        data = new T[sz];
        t = new int[sz];
        for (size_t i = 0; i < sz; i++)
            t[i] = 0;
    }
    
    void set(size_t i, T v) {
        data[i] = v;
        t[i] = ++ time;
    }
    
    T get(size_t i) {
        return (cleartime > t[i] ? T() : data[i]);
    }
    
    void clear() {
        cleartime = ++time;
    }
    
    size_t size() {
        return sz;
    }
    
    clindex<T> operator [] (size_t i) {
        return clindex<T>(this, i);
    }
};

int main() {
    clarray<int> a(12);
    a[5] = 134;
    for (int i = 0; i < 10; i++)
        cout << a[i] << ' ';
    cout << endl;
    a[0] = 100500;
    for (int i = 0; i < 10; i++)
        cout << a[i] << ' ';
    cout << endl;
    a[1] = 122333;
    for (int i = 0; i < 10; i++)
        cout << a[i] << ' ';
    cout << endl;
    a.clear();
    for (int i = 0; i < 10; i++)
        cout << a[i] << ' ';
    cout << endl;
    return 0;
}
