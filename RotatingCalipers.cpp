#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using point = pair<ll, ll>;
#define x first
#define y second

point operator+ (const point& a, const point& b) { return {a.x + b.x, a.y + b.y}; }
point operator- (const point& a, const point& b) { return {a.x - b.x, a.y - b.y}; }
double dist(point& a, point& b) {
    return sqrt((a.x -  b.x) * (a.x -  b.x) + (a.y -  b.y) * (a.y -  b.y));
}

ll cross(point v1, point v2) {
    return v1.x * v2.y - v2.x * v1.y;
}

ll ccw(point o, point a, point b) {
    ll res = cross(a - o, b - o);
    if (res > 0) return 1;
    else if (res < 0) return -1;
    else return 0;
}

double max_dist(vector<point> &pts) {  // 주어진 점들 중 가장 거리가 긴 두 점 사이의 거리 리턴
    // monotone chain으로 upper hull, lower hull까지 구한다
    // 마지막에 합치는 부분만 빼면 동일
    sort(pts.begin(), pts.end());
    vector<point> uh, dh;
    for (auto &p : pts) {
        while (uh.size() >= 2 && ccw(uh[uh.size() - 2], uh[uh.size() - 1], p) >= 0) {
            uh.pop_back();
        }
        uh.push_back(p);
        while (dh.size() >= 2 && ccw(dh[dh.size() - 2], dh[dh.size() - 1], p) <= 0) {
            dh.pop_back();
        }
        dh.push_back(p);
    }

    //// rotating calipers
    double mx = 0;
    int uh_sz = uh.size(), dh_sz = dh.size();
    for (int i = 0, j = dh_sz - 1; i < uh_sz - 1 || j > 0;) {
        // Remind: uh, dh 모두 왼쪽에서 오른쪽으로 진행했기 때문에 uh는 cw, dh는 ccw 방향으로 잡혀 있음 (그래서 convex_hull 마지막에 역순으로 붙여줬던 것)
        // upper hull의 맨 왼쪽 점부터, lower hull의 맨 오른쪽 점부터 두 개 잡고 투포인터처럼 돌려가는 것
        // lower hull은 ccw 방향으로 들어가있는데 얘를 cw 방향으로 돌면서 upper hull이랑 같이 비교해줘야 하니까 j가 반대로 도는 것
        // i=0 --> uh[i], j=dh.size()-1 --> dh[j]

        mx = max(mx, dist(uh[i], dh[j]));

        if (i == uh_sz - 1) j--;  // upper hull이 끝까지 다 돌았다면, lower hull만 끝까지 돌린다
        else if (j == 0) i++;  // 반대로 lower hull만 끝까지 다 돌았다면, upper hull 남은 거 처리
        else {  // 둘 다 돌고 있는 중이면, upper hull의 진행방향 직선 (현재 점 -> 다음 점)과 lower hull의 진행방향 직선 기울기 비교, 기울기가 더 큰 쪽의 hull의 점을 움직인다
            ll upX = uh[i + 1].x - uh[i].x;
            ll upY = uh[i + 1].y - uh[i].y;
            ll downX = dh[j].x - dh[j - 1].x;
            ll downY = dh[j].y - dh[j - 1].y;

            // upper hull 직선 기울기 : upY / upX
            // lower hull 직선 기울기 : downY / downX
            // upY / upX > downY / downX  <=>  upY * downX > downY * upX
            if (upY * downX > downY * upX) {
                // upper쪽이 기울기가 더 크다면, upper 점 이동
                i++;
            } else {
                // 아니면 lower 점 이동
                j--;
            }
        }
    }

    return mx;
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    vector<point> p;
    int c; cin >> c;
    p.resize(c);
    for (int i = 0; i < c; i++) {
        cin >> p[i].x >> p[i].y;
    }

    cout.precision(10);
    cout << fixed;
    cout << max_dist(p) << '\n';

    return 0;
}
