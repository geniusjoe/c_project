#include<bits/stdc++.h>
#define local
#define debu
using namespace std;

const int MAXN = 50010;
const int MAXM = 50010;
struct Query {
    int L, R, id;
} node[MAXM];

int a[MAXN];
int num[MAXN];
int n, m, k, unit;
int ans[MAXN];
bool cmp(Query a, Query b) {
    if(a.L / unit != b.L / unit)
        return a.L / unit < b.L / unit;
    else
        return a.R < b.R;
}
void work() {
    long long temp = 0;
    memset(num, 0, sizeof(num));
    int L = 1;
    int R = 0;
    for(int i = 1; i <= m; i++) {
        while(R < node[i].R) {
            R++;
            temp += (long long )  2 * num[a[R]] + 1;
            num[a[R]]++;
        }
        while(R > node[i].R) {
            num[a[R]]--;
            temp -= (long long )  2 * num[a[R]] + 1;
            R--;
        }
        while(L < node[i].L) {
            num[a[L]]--;
            temp -= (long long )  2 * num[a[L]] + 1;
            L++;
        }
        while(L > node[i].L) {
            L--;
            temp += (long long )  2*num[a[L]]+1;
            num[a[L]]++;
        }
        ans[node[i].id] = temp;
    }
}

int main() {

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i <= m; i++) {
        node[i].id = i;
        cin>>node[i].L>>node[i].R;
    }
    unit = (int)  sqrt(n);
    sort(node+1, node+1 + m, cmp);
    work();
    for(int i=1;i<=m;i++)
        cout<<ans[i]<<endl;
    return 0;
}
