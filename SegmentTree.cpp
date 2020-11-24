// 2042 구간 합 구하기 
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class segTree {
public:
    vector<ll> tree;
    int size, start;
    // size := tree배열 전체 사이즈
    // start := 리프노드 스타트

    // constructor(n) := 리프노드 개수 n개짜리 Segment Tree 생성
    segTree(int n) {
        // 1-BASED INDEX
        start = 1; 

        // 트리 사이즈는 2^k꼴로 맞춰줘야 한다
        // 원소 개수 n보다 크거나 같은 2^k꼴 수
        while (n > start) start <<= 1;  
        size = 2 * start + 1;
        tree.resize(size, 0);
    }

    // construct() := 리프노드에 값이 모두 들어있을 때 O(N)으로 한번에 세그트리 구성
    // 값 받을 때마다 일일히 update() vs 리프노드에 값 다 넣어두고 O(N)에 한번에 세그트리 만들기
    void construct() {  
        for (int i = start - 1; i > 0; i--) {
            tree[i] = tree[i * 2] + tree[i * 2 + 1];  // 리프노드에 넣어둔 값 이용해서 밑에서부터 위로 쭉 트리 채우기
        }
    }

    // update() := i번 idx (1-BASED INDEX)의 값 업데이트
    // 리프노드로 내려가면서 값을 업데이트
    void update(int i, ll val) {
        i += start - 1;  // 트리 배열에서의 idx (리프노드 행으로 이동)
        tree[i] = val;
        while (i > 1) {
            i /= 2;
            tree[i] = tree[i * 2] + tree[i * 2 + 1];  // 값을 업데이트하는 부분인 만큼 문제마다 다르게 변경해야 함
        }
    }

    // 문제마다 다른 부분
    // 어떤 쿼리냐에 따라 알아서 수정할 것
    ll sum(int l, int r) {
        return sum(l, r, 1, 1, start);
    }
    // [l, r] : 우리가 구하려는 구간, node: 지금 보고 있는 노드 번호, [nl, nr]: 지금 보고 있는 노드가 나타내는 구간
    ll sum(int l, int r, int node, int nl, int nr) {  
        if (r < nl || nr < l) return 0;
        else if (l <= nl && nr <= r) return tree[node];
        else {
            int mid = (nl + nr) / 2;
            return sum(l, r, node * 2, nl, mid) + sum(l, r, node * 2 + 1, mid + 1, nr);
        }
    }
};


int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif

    int n, m, k; cin >> n >> m >> k;
    segTree ST(n);
    for (int i = 0; i < n; i++) {
        cin >> ST.tree[ST.start + i];
    }
    ST.construct();

    for (int i = 0; i < m + k; i++) {
        int a; cin >> a;
        if (a == 1) {
            int b; ll c; cin >> b >> c;
            ST.update(b, c);
        }
        else {
            int b, c; cin >> b >> c;
            cout << ST.sum(b, c) << '\n';
        }
    }
    
    return 0;
}
