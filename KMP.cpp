// 1786 찾기

#include <bits/stdc++.h>
using namespace std;

int fail[1000005];

void get_fail(int _fail[], string _s) {
    int m = _s.length();
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && _s[i] != _s[j]) j = _fail[j - 1];
        if (_s[i] == _s[j]) _fail[i] = ++j;
    }
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    // t에서 p가 몇 번 나타나는지를 구해야 한다
    // t가 전체 문자열 (길이 n)
    // p가 부분 문자열 (길이 m)
    string t, p;
    getline(cin, t);
    getline(cin, p);
    int n = t.length(), m = p.length();

    // 부분 문자열 p에 대해 failure function(array)를 구해둔다
    get_fail(fail, p);

    // KMP
    vector<int> res;
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && t[i] != p[j]) j = fail[j - 1];
        if (t[i] == p[j]) {
            if (j == m - 1) {
                // found
                // t에서 p를 찾은 경우
                // 이 때 t에서의 시작 idx는 (i - (p길이) + 1)이 된다
                res.push_back(i - m + 1);
                j = fail[j];
            } else j++;
        }
    }

    cout << res.size() << '\n';
    for (auto it : res) cout << it + 1 << ' ';

    return 0;
}