// 6086 최대 유량
#include <bits/stdc++.h>
using namespace std;
const int MAX_V = 52;
const int INF = 987654321;

int c[MAX_V+1][MAX_V+1];  // c[i][j] := i->j 간선의 용량
int f[MAX_V+1][MAX_V+1];  // f[i][j] := i->j 현재 흐르는 유량
vector<int> adj[MAX_V+1];

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        char _u, _v; int w; cin >> _u >> _v >> w;

        // A~Z: 0~25, a~z: 26~51
        int u = (_u <= 'Z' ? _u - 'A' : _u - 'a' + 26);
        int v = (_v <= 'Z' ? _v - 'A' : _v - 'a' + 26);

        // 같은 간선이 여러 번 들어올 수 있으므로 누적
        c[u][v] += w;
        c[v][u] += w;
        adj[u].push_back(v);
        adj[v].push_back(u);  // 역방향 간선도 추가해줘야 한다!
    }

    // total: 총 유량
    // S: Source, E: Sink
    int total = 0, S = 0, E = 25;

    // 증가 경로(Augmenting path)를 못 찾을 때까지 루프
    while (true) {
        // Augmenting path를 BFS로 찾는다
        int prev[MAX_V+1];
        memset(prev, -1, sizeof(prev));
        queue<int> q;
        q.push(S);
        while (!q.empty() && prev[E] == -1) {
            int x = q.front(); q.pop();
            for (int nx : adj[x]) {
                // c[i][j] - f[i][j] > 0 : i에서 j로 유량을 흘릴 여유가 남았는가?
                // prev[nx] == -1 : nx를 아직 방문하지 않았는가?
                if (c[x][nx] - f[x][nx] > 0 && prev[nx] == -1) {
                    q.push(nx);
                    prev[nx] = x;  // 경로를 기억하기 위해 prev 배열 사용
                    if (nx == E) break;  // Sink에 도달하면 break
                }
            }
        }

        // Sink로 가는 경로가 더 없으면 루프 탈출
        if (prev[E] == -1) break;

        // 경로를 따라가면서 가장 허용치가 낮은 곳을 찾음
        int flow = INF;
        for (int i = E; i != S; i = prev[i]) {
            flow = min(flow, c[prev[i]][i] - f[prev[i]][i]);
        }

        // 찾은 flow만큼 해당 경로에 유량을 흘려준다
        for (int i = E; i != S; i = prev[i]) {
            f[prev[i]][i] += flow;
            f[i][prev[i]] -= flow;
        }

        // 총 유량 합 갱신
        total += flow;
    }

    cout << total << '\n';

    return 0;
}
