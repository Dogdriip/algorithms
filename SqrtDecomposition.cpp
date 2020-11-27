// 2042 구간 합 구하기
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll arr[1000001];
ll bucket[1001];  // bucket은 2차원 배열이 될 수도, vector<int>가 될 수도
int sz;

ll query(int l, int r) {
    ll res = 0;

    while (l % sz != 0 && l <= r) {
        // bucket에 딱 안 떨어지는 구간 == 중간부터 시작하는 것들
        // l++ 시키면서 버킷 왼쪽으로 남은거 일일히 a 배열로 처리
        res += arr[l++];
    }
    while ((r + 1) % sz != 0 && l <= r) {
        // r-- 시키면서 마찬가지로 a 배열 써서 처리
        res += arr[r--];
    }
    while (l <= r) {
        int bk = l / sz;

        // bucket에 들어있는 값을 이용해서 처리
        // l은 sz만큼 증가시켜주면 된다
        res += bucket[l / sz];
        l += sz;
    }
    
    return res;
}

void update(int i, int val) {
    int bk = i / sz;

    // a[i], bucket[i / sz]값 갱신
    bucket[i / sz] -= arr[i];
    bucket[i / sz] += val;
    arr[i] = val;

    // i번째 원소 들어있는 bucket을 아예 갱신해야 할 때는 bucket[bk]와 a[j] 이용
    // for (int j = bk * sz; j < min(bk * sz + sz, n); j++) {
    //         
    // }
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n, m, k; cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    sz = sqrt(n);
    for (int i = 0; i < n; i++) {
        // i: 0~n => bucket[i / sz] 갱신
        bucket[i / sz] += arr[i];
    }

    // 필요시 bucket[i]도 처리
    // 필요할 때가 있다
    // for (int i = 0; i <= sz; i++) {
    //          
    // }
    
    int q = m + k;
    while (q--) {
        ll a, b, c; cin >> a >> b >> c;
        if (a == 1) {
            update(b - 1, c);
        } else {
            cout << query(b - 1, c - 1) << '\n';
        }
    }
    
    return 0;
}
