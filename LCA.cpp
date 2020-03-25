#include <bits/stdc++.h>
using namespace std;

vector<int> adj[100001];
int par[100001][17];  // 100000 < 2^17  par[i][j] : i번 노드의 2^j번째 조상
int depth[100001];  // 노드의 깊이 (루트: 0)

void dfs(int x, int p, int d) {
    par[x][0] = p;
    depth[x] = d;
    for (int nx : adj[x]) {
        if (nx != p) {
            dfs(nx, x, d + 1);
        }
    }
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(par, -1, sizeof(par));
    memset(depth, -1, sizeof(depth));
    dfs(1, -1, 0);  // 트리 생성

    // par 배열 구성
    for (int j = 1; j < 17; j++) {
        for (int i = 1; i <= n; i++) {
            if (par[i][j - 1] != -1) {
                par[i][j] = par[par[i][j - 1]][j - 1];
            }
        }
    }

    int m; cin >> m;
    while (m--) {
        int u, v; cin >> u >> v;
        if (depth[u] < depth[v]) swap(u, v);  // 항상 depth[u] >= depth[v]

        int diff = depth[u] - depth[v];
        for (int j = 16; j >= 0; j--) {  // depth[u] == depth[v] 맞춰주는 과정 (diff만큼 logN시간에 u 건너뛰기)
            if ((diff & (1 << j))) {
                u = par[u][j];
            }
        }

        if (u != v) {
            for (int j = 16; j >= 0; j--) {
                if (par[u][j] != -1 && par[u][j] != par[v][j]) {
                    // par[u][j]가 -1이면 j가 너무 큰 것. 이는 v에게도 마찬가지. 
                    // 해서 par[u][j]랑 par[v][j]랑 계속 다르게 유지시키면서 j 0까지 가면 결국 두 노드의 LCA 직전까지 오고
                    // 마지막에 두 노드 중 한칸만 더 올리면 두 노드의 LCA
                    u = par[u][j];
                    v = par[v][j];
                }
            }
            u = par[u][0];
        }

        cout << u << '\n';
    }

    return 0;
}