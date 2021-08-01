// 1067 이동
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

using base = complex<double>;
const double PI = acos(-1);

void fft(vector<base> &a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j >= bit; bit >>= 1)
            j -= bit;
        j += bit;
        if (i < j) {
            swap(a[i], a[j]);
        }
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        base wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            base w(1);
            for (int j = 0; j < len / 2; j++) {
                base u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (int i = 0; i < n; i++) {
            a[i] /= n;
        }
    }
}

template <class T>
void multiply(const vector<T> &a, const vector<T> &b, vector<T> &res) {
    vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < max(a.size(), b.size())) {
        n <<= 1;
    }
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }
    fft(fa, true);
    res.resize(n);
    for (int i = 0; i < n; i++) {
        res[i] = T(fa[i].real() + (fa[i].real() > 0 ? 0.5 : -0.5));
    }
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;
    vector<ll> a(n * 2), b(n), res((n * 2) + n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        a[n + i] = a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    reverse(b.begin(), b.end());
    multiply(a, b, res);

    ll mx = 0;
    for (int i = 0; i < res.size(); i++) {
        mx = max(mx, res[i]);
    }
    cout << mx << '\n';

    return 0;
}
