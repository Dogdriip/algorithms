#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1e9+7;
const ll K = 1001;

// (0-indexed)
// a[i] = a_i, c[i] = c_i
// a_{i+k} = c_i*a_i + c_{i+1}*a_{i+1} + ... + c_{i+k-1}*a_{i+k-1}
ll c[K], a[K];

// C(N, *) -> C(N+1, *)
void nxt(ll k, ll c0[K], ll c1[K]) {
    c1[0] = (c0[k - 1] * c[0]) % MOD;
    for (int i = 1; i < k; i++) {
        c1[i] = (c0[i - 1] + c0[k - 1] * c[i]) % MOD;
    }
}

// C(N, *) -> C(2N, *)
void dbl(ll k, ll c0[K], ll c1[K]) {
    ll cs[K][K];
    for (int i = 0; i < k; i++) {
        cs[0][i] = c0[i];
    }
    for (int i = 0; i < k - 1; i++) {
        nxt(k, cs[i], cs[i + 1]);
    }
    for (int i = 0; i < k; i++) {
        c1[i] = 0;
        for (int j = 0; j < k; j++) {
            c1[i] += cs[0][j] * cs[j][i];
            c1[i] %= MOD;
        }
    }
}

// calculate a_m
ll solve(ll m, ll k) {
    if (m == 0) {
        return a[0];
    }

    ll c0[K], c1[K];
    for (int i = 0; i < k; i++) {
        c0[i] = 0;
    }
    c0[1] = 1;

    // C(0, *) -> C(m, *) in O(k^2log(m))
    int p = 62;
    while (((m >> --p) & 1) == 0);  // most significant 1 bit
    while (p-- > 0) {
        dbl(k, c0, c0);
        if ((m >> p) & 1) {
            nxt(k, c0, c1);
            for (int j = 0; j < k; j++) {
                c0[j] = c1[j];
            }
        }
    }

    // get result, a_m
    ll res = 0;
    for (int i = 0; i < k; i++) {
        res += (c0[i] * a[i]) % MOD;
        res %= MOD;
    }
    return res;
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    // k : 점화식이 몇 개의 이전 항으로 구성되어 있는가
    // n : 몇번째 항 구해야 하는가
    int k, n; cin >> k >> n;
 
    // c[], a[] 문제에 따라 적절히 구성
    // 이건 https://atcoder.jp/contests/tdpc/tasks/tdpc_fibonacci 문제의 예시
    for (int i = 0; i < k; i++) {
        c[i] = 1;
    }
    for (int i = 0; i < k; i++) {
        a[i] = 1;
    }
 
    // zero-based index 주의
    cout << solve(n - 1, k) << '\n';

    return 0;
}
