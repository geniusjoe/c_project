#include<bits/stdc++.h>

#define loca
#define debu
using namespace std;

const int MAXN = 400005;
const int INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 998244353;

long long n, q, upd;
long long buf[MAXN], qry[MAXN], tme[MAXN];

int main() {

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

#ifdef local
    auto start_time = clock();
    cerr << setprecision(3) << fixed;
#endif

    ios::sync_with_stdio(false);
    cin >> n;
    upd=1;
    fill_n(tme + 1, n, 1);

    for (int i = 1; i <= n; i++) cin >> buf[i];
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int u, v, w;
        cin >> u;
        if (u == 1) {
            cin >> v;
            cin >> buf[v];
            tme[v] = upd;
        } else {
            cin >> qry[upd];
            ++upd;
        }
    }
    for (int i = upd - 1; i >= 1; i--) qry[i] = max(qry[i + 1], qry[i]);

    for (int i = 1; i <= n; i++)
        cout << max(buf[i], qry[tme[i]]) << " ";
    cout << endl;


#ifdef local
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}