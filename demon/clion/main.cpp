#include<bits/stdc++.h>

using namespace std;

#define loc

const int maxn = 1000;
bool vis[28 + 5];

int buf[maxn][maxn];
int n;
long long ans;


void dfs(int x, int t, long long Sum) {
    if (x == 2 * n) {
        ans = max(ans, Sum);
        return;
    }
    if (x - t < n) {
        vis[x + 1] = false;
        dfs(x + 1, t, Sum);
    }
    if (t < n) {
        vis[x + 1] = true;
        for (int i = 1; i <= 2 * n; i++) {
            if (vis[i]) Sum -= buf[i][x + 1];
            else Sum += buf[i][x + 1];
        }
        dfs(x + 1, t + 1, Sum);
    }
}

int main() {
#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif

    ios::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= 2 * n; i++) {
        for (int j = 1; j <= 2 * n; j++) {
            cin >> buf[i][j];
        }
    }
    dfs(0, 0, ans);
    cout << ans << endl;
}