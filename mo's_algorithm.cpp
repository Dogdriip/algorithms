#include <bits/stdc++.h>
using namespace std;

struct qNode {
    int s, e, n;  // 시작, 끝, 쿼리 번호
};

int n, a[100001];
int sz;
qNode Q[100001];
int res[100001];  // res[i] : i번째 쿼리 결과
int curr;  // 쿼리 하나 처리했을 때 결과. 얘를 계속 누적해서 써먹는 것

void Plus(int x) {
    // a[x]값이 새로 추가되는 상황
    // 적절히 curr값 갱신
}
void Minus(int x) {
    // a[x]값이 빠지는 상황
    // 얘도 알아서 curr 갱신
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sz = sqrt(n);

    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        Q[i] = {l - 1, r, i};  // 주의
    }

    // 쿼리 정렬 : (1) s / sqrt(n) 기준 오름차순 --> 시작 버킷 먼저 오는 순으로
    //            (2) e 기준 오름차순 --> 끝나는게 먼저 오는 순으로
    sort(Q, Q + m, [](qNode& a, qNode b) {
        if (a.s / sz != b.s / sz) return a.s / sz < b.s / sz;
        return a.e < b.e;
    });

    // 0번째 쿼리는 직접 처리
    int s = Q[0].s, e = Q[0].e;
    for (int i = s; i < e; i++) {
        Plus(i);
    }
    res[Q[0].n] = curr;

    // 1번째 쿼리부터 바로 이전 쿼리 결과 사용해서 계산해 나감
    // query[i]가 현재 쿼리, 그냥 s, e가 이전 쿼리
    for (int i = 1; i < m; i++) {
        // 현재 쿼리 s가 이전 쿼리 s보다 크면 --> s를 오른쪽으로 이동하면서 축소
        while (s < Q[i].s) {
            Minus(s++);
        }
        // 현재 쿼리 e가 이전 쿼리 e보다 작으면 --> e를 왼쪽으로 이동하면서 축소
        while (Q[i].e < e) {
            Minus(--e);
        }

        // 현재 쿼리 s가 이전 쿼리 s보다 작으면 --> s를 왼쪽으로 이동하면서 확장
        while (s > Q[i].s) {
            Plus(--s);
        }
        // 현재 쿼리 e가 이전 쿼리 e보다 크면 --> e를 오른쪽으로 이동하면서 확장
        while (Q[i].e > e) {
            Plus(e++);
        }

        // i번 쿼리 결과 계산 끝
        res[Q[i].n] = curr;
    }

    for (int i = 0; i < m; i++) {
        cout << res[i] << '\n';
    }

    return 0;
}
