#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

template <class T> T GCD(T a, T b) {
    while (a) a^=b^=a^=b%=a; return b;
}

int gcd(int a, int b) {
    while (b > 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    int a, b;
    cin >> a >> b;
    cout << gcd(a, b) << endl << GCD(a, b);
    return 0;
}
