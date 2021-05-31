// 2389 세상의 중심에서...
// https://hongjun7.tistory.com/25
// http://codeforces.com/blog/entry/23554

#include <bits/stdc++.h>
using namespace std;
using point = pair<double, double>;
#define X first
#define Y second

double dist(point a, point b) {
    return sqrt((a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y));
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    point p[1001];
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p[i].X >> p[i].Y;
    }

    // 평균점 P 구하기
    point P = {0, 0};
    for (int i = 0; i < n; i++) {
        P.X += p[i].X;
        P.Y += p[i].Y;
    }
    P.X /= n;
    P.Y /= n;

    // 전체 점들에 대한 컨벡스 다각형의 내부의 한 점에서 가장 먼 점으로 계속 이동해 나가다보면(한 term에 이동하는 비율은 단조 감소해야함)
    // 반지름이 최소인 원의 좌표를 알 수 있다.
    double ratio = 0.1;
    double mx_d;
    int mx_d_idx;
    for (int i = 0; i < 30000; i++) {
        mx_d = dist(P, p[0]);
        mx_d_idx = 0;
        for (int j = 1; j < n; j++) {
            double d = dist(P, p[j]);
            if (mx_d < d) {
                mx_d = d;
                mx_d_idx = j;
            }
        }
        P.X += (p[mx_d_idx].X - P.X) * ratio;
        P.Y += (p[mx_d_idx].Y - P.Y) * ratio;

        ratio *= 0.999;
    }

    cout.precision(9);
    cout << P.X << ' ' << P.Y << ' ' << mx_d << '\n';

    return 0;
}
