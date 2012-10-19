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

ll binpowmod(int a, int x, ll mod) {
    ll r = 1, p = a;
    while (x > 0) {
        if (x & 1)
            r = (r * p) % mod;
        x >>= 1;
        p = (p * p) % mod;
    }
    return r % mod;
}

int main() {
    int a, b;
    cin >> a >> b;
    cout << binpow(a, b) << endl;
    cout << binpowmod(a, b, (int)(1e9) + 7);
    return 0;
}
