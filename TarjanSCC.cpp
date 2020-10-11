#include <bits/stdc++.h>
using namespace std;

int v, e;
vector<int> adj[10001];

int cnt, dfsn[10001];  // dfs시 정점 방문 순서 (0: 미방문)
int SN, sn[10001];  // SN: 총 SCC 개수, sn[i]: 정점 i가 속한 SCC 번호
bool finished[10001];  // SCC 분리 끝난 정점은 true
stack<int> st;
vector<vector<int> > SCC;

int dfs(int x) {
    dfsn[x] = ++cnt;  // dfsn 설정
    st.push(x);  // 일단 스택에 자신 push

    // 자신의 dfsn, 자식들의 res, 자식들의 dfsn 중 가장 작은 걸 res에 저장
    int res = dfsn[x];
    for (int nx : adj[x]) {
        if (!dfsn[nx]) res = min(res, dfs(nx));  // 아직 방문 안 한 정점은 dfs 돌려서 res 확인
        else if (!finished[nx]) res = min(res, dfsn[nx]);  // 방문은 했지만 아직 SCC로 분리되지 않은 정점
    }

    // res가 자기 자신 dfsn일 경우, 즉
    // 자신과 자신의 자손들이 도달 가능한 제일 높은 정점이 자기 자신일 경우, 즉
    // 자신의 자손들이 조상으로 갈 수 있는 경우가 하나도 없을 경우
    // 자기 자신을 포함해서 SCC로 추출
    if (res == dfsn[x]) {
        vector<int> xSCC;
        // 스택에서 자신이 나올 때까지 pop
        while (true) {
            int t = st.top(); st.pop();
            xSCC.push_back(t);
            finished[t] = true;
            sn[t] = SN;
            if (t == x) break;
        }

        SCC.push_back(xSCC);
        SN++;
    }

    return res;
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    cin >> v >> e;
    for (int i = 0; i < e; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
    }

    for (int i = 1; i <= v; i++) {
        if (!dfsn[i]) {
            dfs(i);
        }
    }

    cout << SN << '\n';
    for (auto& xSCC : SCC) {
        for (int it : xSCC) {
            cout << it << ' ';
        }
        cout << '\n';
    }

    return 0;
}
