#include <bits/stdc++.h>
using namespace std;

string s[100001];

const int GO_MAX = 26;  // 알파벳이겠죠?
class Trie {
public:
    map<string, Trie*> go;  // 원래 트라이에서 go[] 배열의 원리를 생각해보면, 지금은 string 하나가 key고 그에 해당하는 Trie 노드 포인터가 나오면 되니까
    bool output;

    Trie() {

    }
    ~Trie() {

    }

    void insert(vector<string>& strings, int idx) {
        if (strings.size() == idx) {
            output = true;
        } else {
            map<string, Trie*>::iterator it;
            if ((it = go.find(strings[idx])) == go.end()) {  // 다음 자식 노드를 찾을 수 없으면
                Trie *nx = new Trie();  // 하나 만들자
                go.insert({strings[idx], nx});  // 현재 노드의 go에 현재 key (string)과 자식 노드를 매핑시킨다
                nx->insert(strings, idx + 1);
            } else {
                (it->second)->insert(strings, idx + 1);  // 현재 go에 다음 자식 노드가 있으면 거기로 진행
            }
        }
    }

    // 필요에 따라 함수 추가
    // for (auto &it : go) { ... it.second->func() ... } 이런 식이겠지
};


int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    Trie *root = new Trie();

    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int k; cin >> k;
        vector<string> s(k);  // vector<string>이 기존의 string인 셈. 벡터 원소 하나가 string에서의 문자 하나.
        // 기존에는 string 하나의 각 문자가 Trie의 노드 하나였다면, 지금은 string 자체가 Trie의 노드 하나이다.
        for (int j = 0; j < k; j++) {
            cin >> s[j];
        }
        root->insert(s, 0);
    }

    // do something

    return 0;
}