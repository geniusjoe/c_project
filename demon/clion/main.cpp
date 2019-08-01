#include <bits/stdc++.h>

#define loc
const int INF = 0x3f3f3f3f;
using namespace std;
const long long maxn = 2e5 + 5;

long long n, res = 0, cnt;
long long sz[maxn + 5], dp[maxn + 5];

int head[maxn + 5]; // 当前点的第一条边
struct road {
    int to, next;
} roads[2 * maxn + 5];


void add(int a, int b) {
    cnt++;
    roads[cnt].to = b;
    roads[cnt].next = head[a];
    head[a] = cnt;
}

long long dfs1(int p, int i) {
    sz[i] = 1;
    for (int cur_road = head[i]; cur_road; cur_road = roads[cur_road].next) {
        int j = roads[cur_road].to;
        if (j == p) continue;
        sz[i] += dfs1(i, j);
    }
    return sz[i];
}

long long dfs2(int p, int i) {
    for (int cur_road = head[i]; cur_road; cur_road = roads[cur_road].next) {
        int j = roads[cur_road].to;
        if (j == p) continue;

        long long cur1 = sz[i], cur2 = dp[i], cur3 = sz[j];
        dp[j] = dp[i];
        dp[j] -= sz[i];
        dp[j] -= sz[j];
        sz[i] -= sz[j];
        sz[j] += sz[i];
        dp[j] += sz[i];
        dp[j] += sz[j];

        res = max(res, dp[j]);

        dfs2(i, j);

        sz[j] = cur3;
        sz[i] = cur1;
        dp[i] = cur2;
    }
}


int main() {
    ios::sync_with_stdio(false);

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    dfs1(-1, 1);
    for (int i = 1; i <= n; i++) dp[1] += sz[i];
    res = dp[1];
    dfs2(-1, 1);
    cout << res << endl;
}