// 11385 씽크스몰
// https://gratus907.com/93

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

using base = complex<double>;
const double PI = acos(-1);

void fft(vector<base> &a, bool invert = false) {
    ll n = a.size();
    for (ll i = 1, j = 0; i < n; i++) {
        ll bit = n >> 1;
        for (; j >= bit; bit >>= 1)
            j -= bit;
        j += bit;
        if (i < j) {
            swap(a[i], a[j]);
        }
    }
    vector<base> root(n / 2);
    double ang = 2 * PI / n * (invert ? -1 : 1);
    for (ll i = 0; i < n / 2; i++) {
        root[i] = base(cos(ang * i), sin(ang * i));
    }
    for (ll idx = 2; idx <= n; idx <<= 1) {
        ll step = n / idx;
        for (ll i = 0; i < n; i += idx) {
            for (ll j = 0; j < idx / 2; j++) {
                base u = a[i + j], v = a[i + j + idx / 2] * root[step * j];
                a[i + j] = u + v;
                a[i + j+ idx / 2] = u - v;
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
    vector <base> fa_big, fb_big;
    vector <base> fa_small, fb_small;
    ll cut_val = sqrt(1e6);
    ll n = 1;
    while (n < max(a.size(), b.size())) {
        n <<= 1;
    }
    fa_big.resize(n);
    fa_small.resize(n);
    fb_big.resize(n);
    fb_small.resize(n);
    for (int i = 0; i < a.size(); i++) {
        fa_big[i] = a[i] / cut_val;
        fa_small[i] = a[i] % cut_val;
    }
    for (int i = 0; i < b.size(); i++) {
        fb_big[i] = b[i] / cut_val;
        fb_small[i] = b[i] % cut_val;
    }
    fft(fa_big,false);
    fft(fb_big,false);
    fft(fa_small, false);
    fft(fb_small, false);
    vector<base> fa_big_2(fa_big.begin(), fa_big.end());
    vector<base> fa_small_2(fa_small.begin(), fa_small.end());
    for (int i = 0; i < n; i++) {
        fa_big_2[i] *= fb_big[i];
        fa_big[i] *= fb_small[i];
        fa_small[i] *= fb_small[i];
        fa_small_2[i] *= fb_big[i];
    }
    fft(fa_small,true);
    fft(fa_small_2, true);
    fft(fa_big, true);
    fft(fa_big_2, true);
    res.resize(n);
    for (int i = 0; i < n; i++) {
        ll ss = round(fa_small[i].real());
        ll sb = round(fa_small_2[i].real());
        ll bs = round(fa_big[i].real());
        ll bb = round(fa_big_2[i].real());
        res[i] = ss;
        res[i] += (sb + bs) * cut_val;
        res[i] += bb * cut_val * cut_val;
    }
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n, m; cin >> n >> m;
    vector<ll> f(2 * (n + 1) + 1);
    vector<ll> g(2 * (m + 1) + 1);
    vector<ll> res;
    for (int i = 0; i <= n; i++) {
        cin >> f[i];
    }
    for (int i = 0; i <= m; i++) {
        cin >> g[i];
    }
    multiply(f, g, res);

    ll t = 0;
    for (int i = 0; i < res.size(); i++) {
        t ^= res[i];
    }
    cout << t << '\n';

    return 0;
}
