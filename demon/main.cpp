#include<bits/stdc++.h>
#define local
#define debu
using namespace std;

#define MAXM     500000+5
#define INF 0x3f3f3f3f

char tmplate[250][2500];
char buf[1000010];
int tot = 0, res = 0;
int T, n;

int nxt[9000010][26], fail[6000010], End[1000010];

int root, L;
int newnode() {
    for(int i = 0; i < 26; i++)
        nxt[L][i] = -1;
    End[L++] = 0;
    return L - 1;
}
void init() {
    L = 0;
    root = newnode();
    res = 0;
}
void insert(char buf[], int order) {
    int len = strlen(buf);
    int now = root, counter = 0;
    res++;
    for(int i = 0; i < len; i++) {
        if(nxt[now][buf[i] - 'a'] == -1) {
            nxt[now][buf[i] - 'a'] = newnode();
        } else {
            counter++;
            res++;
        }
        now = nxt[now][buf[i] - 'a'];
    }
    if(counter == len)
        res--;
    End[now]++;
}

void debug() {
    for(int i = 0; i < L; i++) {
        printf("id = %3d,fail = %3d,End = %3d,chi = [", i, fail[i],
               End[i]);
        for(int j = 0; j < 26; j++)
            printf("%2d", nxt[i][j]);
        printf("]\n");
    }
}

int main() {

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    int T;
    scanf("%d", &T);
    for(int k = 1; k <= T; k++) {
        cin >> n;
        init();
        for(int i = 1; i <= n; i++) {
            scanf("%s", buf);
            insert(buf, i);
        }
        cout << "Case #" << k << ": " << res << endl;
    }
    return 0;
}
