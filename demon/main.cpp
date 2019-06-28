#include<bits/stdc++.h>
#define local
#define debu
using namespace std;

#define MAXM     500000+5

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
    void insert(char buf[]) {
        int len = strlen(buf);
        int now = root;
        for(int i = 0; i < len; i++) {
            if(next[now][buf[i] - 'a'] == 1)
                next[now][buf[i] - 'a'] = newnode();
            now = next[now][buf[i] - 'a'];
        }
        end[now]++;
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
        int res = 0;
        for(int i = 0; i < len; i++) {
            now = next[now][buf[i] - 'a'];
            int temp = now;
            while( temp != root ) {
                res += end[temp];
                end[temp] = 0;
                temp = fail[temp];
            }
        }
        return res;
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
char buf[1000010];
Trie ac;

void kmp_pre(char x[], int m, int next[]) {
    int i, j;
    j = next[0] = -1;
    i = 0;
    while(i < m) {
        while(-1 != j && x[i] != x[j])
            j = next[j];
        next[++i] = ++j;
    }
}
int next[100010];
int KMP_Count(char x[], int m, char y[], int n) {
    int i, j;
    int ans = 0;
    kmp_pre(x, m, next);
    i = j = 0;
    while(i < n) {
        while(-1 != j && y[i] != x[j])
            j = next[j];
        i++;
        j++;
        if(j >= m) {
            ans++;
            j = next[j];
        }
    }
    return ans;
}

char x[1000010], y[1000010];
int n;

int main() {

    scanf("%d", &n);
    if(n == 1) {
        scanf("%s", x);
        scanf("%s", y);
        printf("%d\n",KMP_Count(x,strlen(x),y,strlen(y)));
    }
    else {
        ac.init();
        for(int i = 0; i < n; i++) {
            scanf("%s", buf);
            ac.insert(buf);
        }
        ac.build();
        scanf("%s", buf);
        printf("%d\n", ac.query(buf));
    }
    return 0;
}

