// 10999 구간 합 구하기 2

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int ST_MAX = 1 << 21;

// 세그먼트 트리 구조체
struct SegTree{
    int start;
    ll arr[ST_MAX], lazy[ST_MAX];

    // 생성자
    SegTree() {
        start = ST_MAX / 2;
        memset(arr, 0, sizeof(arr));
        memset(lazy, 0, sizeof(lazy));
    }

    // 리프 노드들의 값을 먼저 입력한 후 전체 세그먼트 트리 구축
    void construct(){
        for (int i = start - 1; i > 0; i--) {
            arr[i] = arr[i * 2] + arr[i * 2 + 1];
        }
    }

    // 구간 [ns, ne)인 node의 lazy 값을 propagate
    void propagate(int node, int ns, int ne) {
        // lazy 값이 존재하면 실행
        if (lazy[node]) {
            // 리프 노드가 아니면 자식들에게 lazy 미룸
            if (node < start) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            // 자신에 해당하는 만큼의 값을 더함
            arr[node] += lazy[node] * (ne - ns);
            lazy[node] = 0;
        }
    }

    // 구간 [s, e)에 k를 더하라
    void add(int s, int e, int k) {
        add(s, e, k, 1, 0, start);
    }
    void add(int s, int e, int k, int node, int ns, int ne){
        // 일단 propagate
        propagate(node, ns, ne);

        if (e <= ns || ne <= s) return;
        if (s <= ns && ne <= e){
            // 이 노드가 구간에 완전히 포함되면 lazy 부여 후 propagate
            lazy[node] += k;
            propagate(node, ns, ne);
            return;
        }

        int mid = (ns + ne) / 2;
        add(s, e, k, node * 2, ns, mid);
        add(s, e, k, node * 2 + 1, mid, ne);

        // 마지막에 자식들의 값을 사용해 다시 자신의 값 갱신
        arr[node] = arr[node * 2] + arr[node * 2 + 1];
    }

    // 구간 [s, e)의 합을 구하라
    long long sum(int s, int e) {
        return sum(s, e, 1, 0, start);
    }
    long long sum(int s, int e, int node, int ns, int ne) {
        // 일단 propagate
        propagate(node, ns, ne);

        if (e <= ns || ne <= s) return 0;
        if (s <= ns && ne <= e) return arr[node];

        int mid = (ns + ne) / 2;
        return sum(s, e, node * 2, ns, mid) + sum(s, e, node * 2 + 1, mid, ne);
    }
};

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    // 초기 세그먼트 트리 입력받기
    int n, m, k; cin >> n >> m >> k;
    SegTree ST;
    for (int i = 0; i < n; i++) {
        cin >> ST.arr[ST.start + i];
    }

    ST.construct();

    // 쿼리 처리
    for (int i = 0; i < m + k; i++) {
        int a, b, c, d;
        cin >> a;
        if (a == 1) {
            cin >> b >> c >> d;
            ST.add(b - 1, c, d);
        } else {
            cin >> b >> c;
            cout << ST.sum(b - 1, c) << '\n';
        }
    }

    return 0;
}
