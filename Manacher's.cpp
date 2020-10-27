// Manacher's Alg.: 문자열 내에 존재한 모든 팰린드롬 부분 문자열을 O(N)에 구함.

// 13275, 14444 가장 긴 팰린드롬 부분 문자열
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int a[200005];

// s := padding 처리된 문자열 (manachers를 그냥 쓰게 되면 짝수 길이 팰린드롬을 찾을 수 없으므로 padding 처리)
//      padding 처리된 문자열의 팰린드롬 반지름 길이가 원래 문자열의 팰린드롬 전체 길이가 됨을 알 수 있다.
// a[i] := i번째 문자를 중심으로 하는 가장 긴 팰린드롬의 반지름 길이
//         a[i] = 2라면, i - 2부터 i + 2까지 팰린드롬이라는 것
// r := 각 인덱스에 대해 팰린드롬이 될 수 있는 최대 범위
// p := 그러한 r이 형성되는 중심점 idx
void manachers(string s, int a[]) {
	int r = 0, p = 0;

	for (int i = 0; i < s.size(); i++) {
		if (i <= r) {
			a[i] = min(a[2 * p - i], r - i);
		} else {
			a[i] = 0;
		}

		while (i - a[i] - 1 >= 0 && i + a[i] + 1 < s.size() && s[i - a[i] - 1] == s[i + a[i] + 1]) {
			a[i]++;
		}

		if (r < i + a[i]) {
			r = i + a[i];
			p = i;
		}
	}
}

int main() {
	string tmp; cin >> tmp;
	string s;
	for (char c : tmp) {
		s += '#';
		s += c;
	}
	s += '#';

	manachers(s, a);
	
	int ans = 0;
	for (int i = 0; i < s.size(); i++) {
		ans = max(ans, a[i]);
	}
	cout << ans << '\n';
	
	return 0;
}
