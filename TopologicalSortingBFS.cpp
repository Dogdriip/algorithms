// 2623 음악프로그램
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> adj[1001];
int indegree[1001];  // indegree[i] : 정점 i로 들어오는 간선 수
vector<int> order;  // 위상정렬 결과

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int cnt; cin >> cnt;
        int buf; cin >> buf;  // 입력받는 부분 조심
        for (int j = 0; j < cnt - 1; j++) {
            int y; cin >> y;
            indegree[y]++;  // buf에서 y로 들어오는 간선 하나 생김
            adj[buf].push_back(y);
            buf = y;
        }
    }
    
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {  // 초기에 들어오는 간선이 없는 애들은 큐에 넣어주자
            q.push(i);
        }
    }
    
    while (!q.empty()) {
        int curr = q.front(); q.pop();
        order.push_back(curr);
        
        for (int next : adj[curr]) {
            indegree[next]--;  // 큐의 맨 앞 정점과 연결된 모든 간선 제거
            if (indegree[next] == 0) {
                q.push(next);
            }
        }
    }
    
    if (order.size() != n) {  // 위상정렬이 조기종료된 경우 정렬 불가라는 소리
        cout << 0 << '\n';
    } else {
        for (int it : order) {
            cout << it << '\n';
        }
    }
    
    return 0;
}
