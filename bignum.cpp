#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef long double ld;

const int psize = 100;
const int xflen = 100;
const int xfpt = 20;
const int xfbase = 10;

struct xreal {
    int p[xflen], hi;

    xreal() {
        for (int i = 0; i < xflen; i++)
            p[i] = 0;
        p[xfpt] = 1;
        hi = xfpt;
    }

    void mul(int v) {
        int m = 0;
        for (int i = 0; i < xflen; i++) {
            p[i] = p[i] * v + m;
            m = p[i] / xfbase;
            p[i] %= xfbase;
        }
    }

    void div(int v) {
        int m = 0;
        for (int i = xflen - 1; i >= 0; i--) {
            m = m * xfbase + p[i];
            p[i] = m / v;
            m %= v;
        }
    }

    void out(int sgn) {
        int i = xflen - 1;
        while (i > xfpt && p[i] == 0)
            i--;
        for (; i >= xfpt; i--)
            cout << p[i];
        cout << '.';
        for (; i >= 0 && sgn > 0; i--) {
            cout << p[i];
            sgn--;
        }
    }
};

struct prnum {
    ll p[psize], d[psize];
    int pk;

    prnum() {
        clear();
    }

    prnum(ll x) {
        clear();
        pk = 0;
        for (ll i = 2; i * i <= x; i++)
            if (x % i == 0) {
                while (x % i == 0) {
                    x /= i;
                    p[pk]++;
                }
                d[pk] = i;
                pk++;
            }
        if (x > 1) {
            p[pk] = 1;
            d[pk] = x;
            pk++;
        }
    }

    void clear() {
        for (ll i = 0; i < psize; i++)
            p[i] = 0;
        for (ll i = 0; i < psize; i++)
            d[i] = 0;
        pk = 0;
    }

    prnum lcmif(prnum r, bool lc) {
        prnum res;
        int i = 0, j = 0;
        while (i < pk || j < r.pk) {
            int mp, dn;
            if (j == r.pk || (i != pk && d[i] < r.d[j])) {
                mp = (lc ? max(0LL, p[i]) : min(0LL, p[i]));
                dn = d[i];
                i++;
            } else if(i == pk || (j != r.pk && d[i] > r.d[j])) {
                mp = (lc ? max(0LL, r.p[j]) : min(0LL, r.p[j]));
                dn = r.d[j];
                j++;
            } else {
                mp = (lc ? max(p[i], r.p[j]) : min(p[i], r.p[j]));
                dn = d[i];
                i++; j++;
            }
            if (mp != 0) {
                res.p[res.pk] = mp;
                res.d[res.pk] = dn;
                res.pk++;
            }
        }
        return res;
    }

    prnum divif(prnum r, bool dv) {
        prnum res;
        int i = 0, j = 0;
        while (i < pk || j < r.pk)
            if (j == r.pk || (i != pk && d[i] < r.d[j])) {
                res.p[res.pk] = p[i];
                res.d[res.pk] = d[i];
                i++; res.pk++;
            } else if(i == pk || (j != r.pk && d[i] > r.d[j])) {
                res.p[res.pk] = (dv ? -r.p[j] : r.p[j]);
                res.d[res.pk] = r.d[j];
                j++; res.pk++;
            } else {
                int px = p[i] + (dv ? -r.p[j] : r.p[j]);
                if (px != 0) {
                    res.p[res.pk] = p[i] + (dv ? -r.p[j] : r.p[j]);
                    res.d[res.pk] = d[i];
                    res.pk++;
                }
                i++; j++;
            }
        return res;
    }

    prnum operator * (prnum p) {
        return divif(p, false);
    }

    prnum operator / (prnum p) {
        return divif(p, true);
    }
    
    prnum gcd(prnum b) {
        return lcmif(b, false);
    }
    
    prnum lcm(prnum b) {
        return lcmif(b, true);
    }

    ld val() {
        ld v = 1.0;
        for (int i = 0; i < pk; i++)
            for (int j = 0; j < p[i]; j++)
                v *= d[i];
        return v;
    }

    xreal xval() {
        xreal x;
        for (int i = 0; i < pk; i++) {
            for (int j = 0; j < p[i]; j++)
                x.mul(d[i]);
            for (int j = -1; j >= p[i]; j--)
                x.div(d[i]);
        }
        return x;
    }
};

int main() {
    int a, b;
    cin >> a >> b;
    prnum s(a), t(b);
    cout << s.gcd(t).val() << ' ' << s.lcm(t).val();
    return 0;
}
