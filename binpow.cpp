#include <iostream>
using namespace std;

typedef long long ll;

ll binpow(int a, int x) {
    ll r = 1, p = a;
    while (x > 0) {
        if (x & 1)
            r *= p;
        x >>= 1;
        p *= p;
    }
    return r;
}

int main() {
    int a, b;
    cin >> a >> b;
    cout << binpow(a, b);
    return 0;
}
