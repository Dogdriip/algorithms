// 1753 최단경로

#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int INF = 987654321;

vector<pii> adj[20001];  // {연결된 정점 번호, 간선 가중치}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int V, E; cin >> V >> E;
    int k; cin >> k;  // 시작 정점 k
    for (int i = 0; i < E; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }

    // dist[i] := 시작점에서 i번 정점까지의 최단거리
    // 시작점은 0으로 초기화
    vector<int> dist(V + 1, INF);
    dist[k] = 0;

    // {가중치, 정점}. 가중치가 작은 노드부터 나옴 (min heap)
    // bfs처럼 시작점 넣고 시작
    priority_queue<pii, vector<pii>, greater<> > pq;
    pq.push({0, k});

    while (!pq.empty()) {
        auto [cost, x] = pq.top();
        pq.pop();

        if (dist[x] < cost) continue;  // 이미 이전에 더 작은 최단거리로 갱신된 정점이라면 스킵

        for (auto [nx, ncost] : adj[x]) {  // adj에서 뽑아오는 순서와 pq 순서 헷갈림 주의
            if (dist[nx] > cost + ncost) {
                // nx의 dist 갱신 후 pq에 삽입
                dist[nx] = cost + ncost;
                pq.push({cost + ncost, nx});
            }
        }
    }

    for (int i = 1; i <= V; i++) {
        if (dist[i] == INF) {
            cout << "INF\n";
        } else {
            cout << dist[i] << '\n';
        }
    }

    return 0;
}
