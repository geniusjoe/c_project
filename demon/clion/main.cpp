#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 300005;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

char buf[MAXN];
long long n, k, a, b, m, T;

struct song {
    long long len, bty;

    bool operator<(song song1) {
        return this->bty > song1.bty;
    }
} songs[MAXN];

priority_queue<long long, vector<long long>, greater<long long>> q;


int main() {

#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // ONLINE_JUDGE

#ifndef ONLINE_JUDGE
    auto start_time = clock();
    cerr << setprecision(3) << fixed;
#endif

/*
写代码时请注意：
    1.是否要开Long Long？数组边界处理好了么？
    2.实数精度
    4.做一些总比不做好.
    5.排序之前不能取模.
思考提醒：
    1.最大值和最小值问题可不可以用二分答案？
    2.有没有贪心策略？否则能不能dp？
    3.如果规模小的话还能尝试dfs
*/

    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (long long i = 1; i <= n; i++) {
        cin >> songs[i].len >> songs[i].bty;
    }
    sort(songs + 1, songs + 1 + n);
    long long cur_len = 0, res = 0;
    for (long long i = 1; i <= n; i++) {
        cur_len += songs[i].len;
        q.push(songs[i].len);
        if (q.size() > k) {
            cur_len -= q.top();
            q.pop();
        }
        res = max(res, cur_len * songs[i].bty);
    }
    cout << res << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}