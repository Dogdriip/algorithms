#include <bits/stdc++.h>
using namespace std;

const int GO_MAX = 10;  // 트라이 노드마다 최대 포인터 개수. 등장할 수 있는 문자 개수랑 연관
class Trie {  // 트라이 노드 하나를 나타냄. Trie *root; 로 루트 하나 만들고 사용.
public:
    Trie* go[GO_MAX];  // 자식노드 포인터 배열
    bool output;  // 이 노드에서 끝나는 문자열이 있는가? (output이 있다 / final state / accepting node / ...)
    bool goexist;  // 이 노드의 자식이 있는가?
    // 이외에도 필요에 따라 변수 추가해서 풀어야 함.
    // 노드 내려오면서 누적합을 구한다던가...

    Trie() {
        // 생성자. 변수 초기화
        fill(go, go + GO_MAX, nullptr);
        output = goexist = false;
    }
    ~Trie() {
        // 소멸자
        for (int i = 0; i < GO_MAX; i++) {
            if (go[i]) {
                delete go[i];
            }
        }
    }

    // 문자열 s의 idx번째 글자를 트라이에 삽입
    void insert(string *s, int idx) {
        if ((*s).length() == idx) {
            output = true;  // 여기서 끝나는 문자열이 있다면, 현재 노드에서 끝나는 문자열이 있다고 체크하고 진행 종료
        } else {
            int nx = (*s)[idx] - '0';  // 지금 보고있는 문자 (자식노드 만들어서 내려갈 노드). 들어올 수 있는 문자 범위 보고 알아서 0 indexing 해야 함
            if (!go[nx]) {  // Remind: go는 트라이 노드 포인터 배열. nx 노드가 없으면 하나 만든다.
                go[nx] = new Trie();  // 빈 노드 생성 완료
            }
            goexist = true;  // 이 노드의 자식이 있다고 표기
            go[nx]->insert(s, idx + 1);  // 다음 글자로 진행
        }
    }
    
    // 문제마다 알아서 함수 정의해서 알아서 풀자
    // for (int i = 0; i < GO_MAX; i++) { ... return go[i]->func() ... } 이런 식으로 노드 쭉 진행시키는 식이겠지
};

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        Trie *root = new Trie();
        int n; cin >> n;
        for (int i = 0; i < n; i++) {
            string s; cin >> s;
            root->insert(&s, 0);
        }

        // do something

        delete root;
    }

    return 0;
}
