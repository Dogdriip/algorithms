// 11657 타임머신

#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ll = long long;
const ll INF = 1e18;

vector<pii> adj[501];
ll dist[501];

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].emplace_back(b, c);
    }

    // dist 초기화 (시작점 0으로, 나머지는 다 INF로)
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[1] = 0;

    // negcycle := 음수 사이클 여부
    bool negcycle = false;

    // n번 루프 (n-1번까지는 최단경로 갱신, 마지막 1번은 음수사이클 판별용)
    // 노드 n개짜리 그래프에서 어떠한 최단경로도 노드 수는 n-1개를 넘어갈 수 없으므로,
    // n-1번 루프로 충분하다.
    // n-1번 이후 한번 더 돌려서 값 갱신이 일어났다면, 음수 사이클이 있는 것.
    for (int k = 0; k < n; k++) {
        for (int i = 1; i <= n; i++) {
            for (auto [nx, w] : adj[i]) {
                if (dist[i] != INF && dist[nx] > dist[i] + w) {
                    dist[nx] = dist[i] + w;
                    if (k == n - 1) negcycle = true;  // 상기했듯 n번째 루프인데 값이 갱신되었다면 음수 사이클이 있는 것.
                }
            }
        }
    }

    if (negcycle) {
        cout << "-1\n";
    } else {
        for (int i = 2; i <= n; i++) {
            cout << (dist[i] == INF ? -1 : dist[i]) << '\n';
        }
    }

    return 0;
}
