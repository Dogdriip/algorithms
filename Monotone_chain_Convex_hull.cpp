#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using point = pair<ll, ll>;
#define x first
#define y second

point operator+ (const point& a, const point& b) {
    return {a.x + b.x, a.y + b.y};
}
point operator- (const point& a, const point& b) {
    return {a.x - b.x, a.y - b.y};
}

ll cross(point v1, point v2) {  // cross product, outer product of two vectors
    return v1.x * v2.y - v2.x * v1.y;
}

ll ccw(point o, point a, point b) {  // ccw of two vectors (o->a), (o->b)
    ll res = cross(a - o, b - o);
    // Remind: 외적 부호가 +이면 ccw, -이면 cw
    if (res > 0) return 1;
    else if (res < 0) return -1;
    else return 0;
}

vector<point> convex_hull(vector<point> &pts) {  // return convex hull of given points, pts
    if (pts.size() <= 3) {
        return pts;
    }

    sort(pts.begin(), pts.end());  // ordinary pair sort

    vector<point> uh, dh;  // upper hull, lower hull
    // pts 중 좌하단 점은 무조건 convex hull에 포함되므로 uh, dh에 넣고 시작 (로직상 첫 루프에서)
    for (auto &p : pts) {
        // upper hull은 ccw <= 0이 되도록 유지 (while문 ccw 등호)
        // 1708의 경우 "볼록 껍질의 변에 점이 여러 개 있는 경우에는 가장 양 끝 점만 개수에 포함한다." 이 조건 때문에 ccw < 0이 되도록 유지해야 함
        while (uh.size() >= 2 && ccw(uh[uh.size() - 2], uh[uh.size() - 1], p) > 0) {
            uh.pop_back();
        }
        uh.push_back(p);
        // lower hull은 ccw >= 0이 되도록 유지
        // 얘도 위에랑 마찬가지
        while (dh.size() >= 2 && ccw(dh[dh.size() - 2], dh[dh.size() - 1], p) < 0) {
            dh.pop_back();
        }
        dh.push_back(p);
    }
    // upper hull의 뒤에 lower hull의 시작점, 끝점을 빼고 역순으로 붙여주면 끝
    // convex hull을 이루는 점들 중 첫 점(좌하단)부터 시작하여 cw방향 순서대로 들어가게 됨
    uh.insert(uh.end(), dh.rbegin() + 1, dh.rend() - 1);
    return uh;
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    vector<point> p;
    int n; cin >> n;
    p.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
    }

    // get convex hull of points p
    vector<point> res = convex_hull(p);
    // 시작점부터 cw방향 순서대로 들어감

    return 0;
}
