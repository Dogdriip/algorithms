#include <bits/stdc++.h>
using namespace std;

int parent[200001];  // uf

int Find(int x) {
    if (parent[x] < 0) return x;
    return parent[x] = Find(parent[x]);
}
void Union(int x, int y) {
    x = Find(x); y = Find(y);
    if (x == y) return;
    parent[x] += parent[y];
    parent[y] = x;
}

// 루트 정점은 par[]가 음수이면서 그 값은 -(원소 개수)가 됨
// a번 원소가 들어있는 집합의 크기 == -par[Find(a)]
