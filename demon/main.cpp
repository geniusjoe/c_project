#include<bits/stdc++.h>
#define local
#define debu
using namespace std;

#define MAXM     500000+5
#define INF 0x3f3f3f3f

char buf[1000010];
int hash[1000010], tot = 0;
int res[1000010];
bool vis[1000010], ins[1000010], flag;
int T, n;

struct Trie {
    int next[10000100][2], fail[10000100], end[10000100];
    int root, L;
    int newnode() {
        for(int i = 0; i < 26; i++)
            next[L][i] = -1;
        end[L++] = 0;
        return L - 1;
    }
    void init() {
        L = 0;
        root = newnode();
        memset(hash, 0, sizeof(hash));
        memset(res, 0, sizeof(res));
    }
    void insert(char buf[]) {
        int len = strlen(buf);
        int now = root;
        for(int i = 0; i < len; i++) {
            if(next[now][buf[i] - '0'] == -1)
                next[now][buf[i] - '0'] = newnode();
            now = next[now][buf[i] - '0'];
        }
        end[now] = 1;
    }
    void build() {
        queue<int>Q;
        fail[root] = root;
        for(int i = 0; i < 2; i++)
            if(next[root][i] == -1)
                next[root][i] = root;
            else {
                fail[next[root][i]] = root;
                Q.push(next[root][i]);
            }
        while( !Q.empty() ) {
            int now = Q.front();
            Q.pop();
            for(int i = 0; i < 2; i++)
                if(next[now][i] == -1)
                    next[now][i] = next[fail[now]][i];
                else {
                    fail[next[now][i]] = next[fail[now]][i];
                    if(end[next[now][i]] == 0)
                        end[next[now][i]] = end[next[fail[now]][i]];
                    Q.push(next[now][i]);
                }
        }
    }

    inline void dfs(int x) {
        if(ins[x]) {
            printf("TAK\n");
            exit(0);
        }
        if(vis[x] || end[x])
            return;
        vis[x] = ins[x] = 1;
        if(next[x][0])
            dfs(next[x][0]);
        if(next[x][1])
            dfs(next[x][1]);
        ins[x] = 0;
    }

    void debug() {
        for(int i = 0; i < L; i++) {
            printf("id = %3d,fail = %3d,end = %3d,chi = [", i, fail[i],
                   end[i]);
            for(int j = 0; j < 2; j++)
                printf("%2d", next[i][j]);
            printf("]\n");
        }
    }
};

Trie ac;

int main() {

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local


    scanf("%d", &n);
    ac.init();
    for(int i = 1; i <= n; i++) {
        scanf("%s", buf);
        ac.insert(buf);
    }
    ac.build();
    //ac.debug();
    ac.dfs(0);

    if(flag == true)
        cout << "TAK" << endl;
    else
        cout << "NIE" << endl;

    return 0;
}

