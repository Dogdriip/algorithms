#include <bits/stdc++.h>
using namespace std;

int a[1000001];
int bucket[1001];  // bucket은 2차원 배열이 될 수도, vector<int>가 될 수도
int sz;

int query(int l, int r) {
    int res = 0;

    while (l % sz != 0 && l <= r) {
        // bucket에 딱 안 떨어지는 구간 == 중간부터 시작하는 것들
        // l++ 시키면서 버킷 왼쪽으로 남은거 일일히 a 배열로 처리
    }
    while ((r + 1) % sz != 0 && l <= r) {
        // r-- 시키면서 마찬가지로 a 배열 써서 처리
    }
    while (l <= r) {
        int bk = l / sz;

        // bucket에 들어있는 값을 이용해서 처리
        // l은 sz만큼 증가시켜주면 된다
    }
    
    return res;
}

void update(int i, int v) {
    int bk = i / sz;

    // a[i], bucket[i / sz]값 갱신

    for (int j = bk * sz; j < min(bk * sz + sz, n); j++) {
        // i번째 원소 들어있는 bucket을 아예 갱신해야 할 때는 bucket[bk]와 a[j] 이용
    }
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sz = sqrt(n);

    for (int i = 0; i < n; i++) {
        // bucket[i / sz] 갱신
    }
    for (int i = 0; i <= sz; i++) {
        // 필요시 bucket[i]도 처리
    }
    
    while (m--) {
        // do something
    }
    
    return 0;
}