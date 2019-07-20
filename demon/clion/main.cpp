#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 30;
ll a[maxn][maxn], n, ans,m;
int vis[maxn];
void dfs(int x,int t,ll sum)
{
    vis[x] = 1;
    if (x != 0)
    {
        for (int i = 1; i <= n; ++i)
        {
            if (vis[i]) sum -= a[i][x];
            else sum += a[i][x];
        }
    }
    if (t == n/2) { ans = max(ans, sum); return; }
    for (int i = x + 1; i <= n; ++i)
    {
        if (n - i >= n/2 - t - 1)
        {
            dfs(i, t + 1, sum);
            vis[i] = 0;
        }
    }
}
int main()
{
    scanf("%d", &n);
    n*=2;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
            scanf("%lld", &a[i][j]);
    }
    ans = 0;
    dfs(0, 0, 0);
    printf("%lld\n", ans);
}