#include<bits/stdc++.h>
#define local
#define debu
using namespace std;

#define MAXM     500000+5
#define INF 0x3f3f3f3f

char tmplate[65][250];
char buf[1000010];
int hash[1000010], tot = 0;
int res[1000010];
int T, n;

struct Trie {
    int next[1000010][26], fail[1000010], end[1000010];
    int root, L;
    int newnode() {
        for(int i = 0; i < 26; i++)
            next[L][i] = 1;
        end[L++] = 0;
        return L - 1;
    }
    void init() {
        L = 0;
        root = newnode();
    }
    void insert(char buf[], int order) {
        int len = strlen(buf);
        int now = root;
        for(int i = 0; i < len; i++) {
            if(next[now][buf[i] - 'a'] == 1)
                next[now][buf[i] - 'a'] = newnode();
            now = next[now][buf[i] - 'a'];
        }
        end[now] = order;
    }
    void build() {
        queue<int>Q;
        fail[root] = root;
        for(int i = 0; i < 26; i++)
            if(next[root][i] == 1)
                next[root][i] = root;
            else {
                fail[next[root][i]] = root;
                Q.push(next[root][i]);
            }
        while( !Q.empty() ) {
            int now = Q.front();
            Q.pop();
            for(int i = 0; i < 26; i++)
                if(next[now][i] == 1)
                    next[now][i] = next[fail[now]][i];
                else {
                    fail[next[now][i]] = next[fail[now]][i];
                    Q.push(next[now][i]);
                }
        }
    }
    int query(char buf[]) {
        int len = strlen(buf);
        int now = root;
        for(int i = 0; i < len; i++) {
            now = next[now][buf[i] - 'a'];
            int temp = now;
            while( temp != root ) {
                hash[end[temp]]++;
                temp = fail[temp];
            }
        }
        int cnt = -1, max = -INF;
        for(int i = 1; i <= n; i++) {
            if(hash[i] == max)
                res[++cnt] = i;
            else if(hash[i] > max)    {
                max = hash[i];
                cnt = 0;
                res[cnt] = i;
            } else
                continue;
        }
        cout << cnt + 1 << endl;
        for(int i = 0; i <= cnt; i++) {
            printf("%s\n", tmplate[res[i]]);
        }
    }
    void debug() {
        for(int i = 0; i < L; i++) {
            printf("id = %3d,fail = %3d,end = %3d,chi = [", i, fail[i],
                   end[i]);
            for(int j = 0; j < 26; j++)
                printf("%2d", next[i][j]);
            printf("]\n");
        }
    }
};

Trie ac;

int main() {

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("tertdata.out", "w+", stdout);
#endif // local


    while(scanf("%d", &n) && n != 0) {
        ac.init();
        for(int i = 1; i <= n; i++) {
            scanf("%s", tmplate[i]);
            ac.insert(tmplate[i], i);
        }
        ac.build();
        scanf("%s", buf);
        ac.query(buf);
    }
    return 0;
}

