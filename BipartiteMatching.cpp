// 1298 노트북의 주인을 찾아서
#include <bits/stdc++.h>
using namespace std;

int n, m;  // A그룹 크기, B그룹 크기
int A[101], B[5001];  // A[i], B[i] := 각 정점이 매칭된 반대편 정점 번호
vector<int> adj[101];  // adj[i] := A그룹 정점 i에 인접한 B그룹 정점들 (A그룹->B그룹)
bool visited[101];

bool dfs(int a) {  // A그룹에 속한 정점 a를 매칭시켜서 성공하면 true, 아니면 false
    visited[a] = true;
    for (int b : adj[a]) {
        if (B[b] == -1 || (!visited[B[b]] && dfs(B[b]))) {
            A[a] = b;
            B[b] = a;
            return true;
        }
    }

    // 매칭 실패
    return false;
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
    }

    int match = 0;
    memset(A, -1, sizeof(A));
    memset(B, -1, sizeof(B));

    for (int i = 1; i <= n; i++) {
        if (A[i] == -1) {
            memset(visited, 0, sizeof(visited));
            if (dfs(i)) {
                match++;
            }
        }
    }

    cout << match << '\n';

    return 0;
}
