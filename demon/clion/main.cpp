#include<bits/stdc++.h>

#define loca
#define debu
using namespace std;

const int MAXN = 100025;
const int INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 1000000007;

long long n, m;
bool graph[105][105];
bool vis[105];

void dfs(int u) {
    vis[u] = true;
    for (int i = 1; i <= n; i++) {
        if (vis[i] || !graph[u][i]) continue;
        dfs(i);
    }
}


int main() {

#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // ONLINE_JUDGE

#ifndef ONLINE_JUDGE
    auto start_time = clock();
    cerr << setprecision(3) << fixed;
#endif

//    ios::sync_with_stdio(false);
//    cin >> T;
    cin >> n >> m;
    if (n != m) {
        cout << "NO" << endl;
        return 0;
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = graph[v][u] = true;
    }
    dfs(1);
    bool flg = true;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            flg = false;
            break;
        }
    }
    if (!flg)
        cout << "NO" << endl;
    else
        cout << "FHTAGN!" << endl;
    return 0;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}

/*
写代码时请注意：
    1.是否要开Long Long？数组边界处理好了么？
    2.实数精度有没有处理？
    3.特殊情况处理好了么？
    4.做一些总比不做好。
思考提醒：
    1.最大值和最小值问题可不可以用二分答案？
    2.有没有贪心策略？否则能不能dp？
*/