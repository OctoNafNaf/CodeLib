#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

template <class T>
T gcdxor(T a, T b) {
    while (a) a^=b^=a^=b%=a; return b;
}

template <class T>
T gcd(T a, T b) {
    while (b > 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}

template <class T>
T gcdrec(T a, T b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main() {
    int a, b;
    cin >> a >> b;
    cout << gcd(a, b) << endl
         << gcdxor(a, b) << endl
         << gcdrec(a, b) << endl;
    return 0;
}
