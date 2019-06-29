#include<bits/stdc++.h>
#define loca
#define debu
using namespace std;

#define MAXM     500000+5
#define INF 0x3f3f3f3f

const int model = 1000000007;

char tmplate[250][2500];
char buf[1000010];
long long base1[3000][3000];
long long base2[3000][3000];
int tot = 0, res = 0;
int T, n;

long long  work1(int u, int t, int U, int T) {
#ifdef debug
    cout << u << "\t" << t << endl;
#endif // debug
    if(u == U && t == T)
        return 1;
    else if(u <= t)
        return 0;
    else if(u == U && t < T)
        return 1;
    else if(t == T && u > T)
        return 1;
    else if(t == T && u <= T)
        return 0;
    else {
        if(base1[u + 1][t] == -1)
            base1[u + 1][t] = work1(u + 1, t, U, T) % model;
        if(base1[u][t + 1] == -1)
            base1[u][t + 1] = work1(u, t + 1, U, T) % model;
        return base1[u + 1][t] + base1[u][t + 1] % model;
    }
}

long long work2(int u, int t, int U, int T) {
    if(u == U && t == T)
        return 1;
    else if(t < T && u > t)
        return 0;
    else if(t > T || u > U)
        return 0;
    else if(t == T && u > T)
        return 0;
    else if(t == T && u <= T)
        return 1;
    else {
        if(base2[u + 1][t] == -1)
            base2[u + 1][t] = work2(u + 1, t, U, T) % model;
        if(base2[u][t + 1] == -1)
            base2[u][t + 1] = work2(u, t + 1, U, T) % model;
        return base2[u + 1][t] + base2[u][t + 1] % model;
    }
}


int main() {
#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    int n;
    scanf("%d", &n);
    for(int k = 1; k <= n; k++) {
        memset(base1, -1, sizeof(base1));
        memset(base2, -1, sizeof(base2));
        int U, T;
        char hyphen;
        cin >> U >> hyphen >> T;
        long long res1 = work1(1, 0, U, T);
        long long res2 = work2(0, 0, U, T);
        cout << "Case #" << k << ": " << res1 << " " << res2 << endl;
    }
    return 0;
}

