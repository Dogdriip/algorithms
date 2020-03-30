#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

int n, m;
vector<int> adj[20001];

////////// SCC 관련 부분
int cnt, dfsn[20001];
int SN, sn[20001];
bool finished[20001];
stack<int> st;
vector<vector<int> > SCC;
int dfs(int x) {
    /* ... */
}
////////// SCC 관련 부분

int oppo(int x) {  // 변수 넘버링 어떻게 했는지 잘 보고 적절히 수정
    return (x % 2 ? x - 1 : x + 1);
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;

        // a, b를 노드 번호로 써야 하니까 다시 넘버링
        // x1, x2, x3, ... (1, 2, 3, ...) => 1, 3, 5, ...
        // ~x1, ~x2, ~x3, ... (-1, -2, -3, ...) => 0, 2, 4, ...
        // 음수로 안 들어오고 변수 번호랑 not 여부로 들어온다 하더라도 1, 3, 5 / 0, 2, 4 이런 식으로 나눠서 저장할 수 있어야 함
        a = (a < 0 ? -(a + 1) * 2 : a * 2 - 1);
        b = (b < 0 ? -(b + 1) * 2 : b * 2 - 1);

        // (a OR b) 절을 (~a -> b), (~b -> a) 두 개의 간선으로 바꾼다
        // + (a XOR b) 절은 (~a -> b), (~b -> a), (b -> ~a), (a -> ~b) 네 개 간선으로 바꿀 수 있다
        adj[oppo(a)].push_back(b);
        adj[oppo(b)].push_back(a);
    }

    // SCC
    for (int i = 0; i < n * 2; i++) {
        if (!dfsn[i]) {
            dfs(i);
        }
    }

    // ~x_k랑 x_k랑 같은 SCC에 있으면 안 되는 거시다
    // ~x1=0, x1=1, ~x2=2, x2=3, ... 이런 식으로 정했으니까 적절히 포문 돌고
    for (int i = 0; i < n; i++) {
        if (sn[i * 2] == sn[i * 2 + 1]) {
            cout << "0\n";
            return 0;
        }
    }

    cout << "1\n";

    // 모순이 없다면, 식을 true로 만드는 각 변수의 값을 진짜루 구해보자
    int res[10001];  // 변수 x1, x2, x3, ...의 값 (-1: 아직 미설정, 0: false, 1: true)
    memset(res, -1, sizeof(res));

    pii p[20001];  // 각 노드의 SCC 번호, 노드 번호
    for (int i = 0; i < n * 2; i++) {
        p[i] = {sn[i], i};
    }
    // 위에서 SCC 구할 때, dfs 쭉 방문해서 맨 뒤부터 SN 매겼으니까,
    // SN이 큰 순서대로 방문하면 그게 SCC 위상정렬 방문 순서가 된다
    sort(p, p + n * 2, greater<>());  // SCC 번호 기준 내림차순으로 정렬

    for (int i = 0; i < n * 2; i++) {
        int var = p[i].second;  // 노드 번호: ~x1=0, x1=1, ~x2=2, x2=3, ...
        // SCC 위상정렬 순으로 방문하면서
        // x1, x2, ...에 대해 변수값이 설정되지 않았다면, 일단은 false로 설정
        // 현재 방문 노드가 짝수면 not 변수 방문중인 거니까 not 변수는 true로 설정. 그래서 밑에처럼 하면 된다
        if (res[var / 2] == -1) res[var / 2] = !(var % 2);
    }

    for (int i = 0; i < n; i++) {
        cout << res[i] << ' ';
    }
    cout << '\n';

    return 0;
}
