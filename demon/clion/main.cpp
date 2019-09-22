#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 2050;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n, m, q;

map<long long, long long> people;
map<long long, vector<pair<long long, long long>>> cakes;

#define setbit(x, y) x|=(1ll<<y)

#define clrbit(x, y) x&=~(1ll<<y)

#define reversebit(x, y) x^=(1ll<<y)

#define getbit(x, y) ((x) >> (y)&1ll)

void update(long long pos, long long cur) {
    if (pos == 10) {
        people[cur]++;
        return;
    }
    if (getbit(cur, pos)) update(pos + 1, cur);
    else {
        auto now = cur;
        setbit(now, pos);
        update(pos + 1, now);
        update(pos + 1, cur);
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

/*
写代码时请注意：
    1.是否要开Long Long？数组边界处理好了么？
    2.实数精度
    3.下标能从最小值开始就从最小值开始
    5.排序之前不能取模.
    6.0-1子矩阵子序列:前缀和
    7.模拟题注意代码复用.
    8.单个区间问题考虑前缀和,多个区间左右端点拆开,排序,记录端点极值
思考提醒：
    1.最大值和最小值问题可不可以用二分+贪心？
    2.dp
    3.如果规模小的话还能尝试dfs
    4.如果存在等式.转换关系少可以暴力枚举变量,或者考虑从数据大小入手
    5.离散化+打表
*/

    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (long long i = 1; i <= n; i++) {
        long long nm, cur = 0;
        cin >> nm;
        for (long long j = 1; j <= nm; j++) {
            long long u;
            cin >> u;
            setbit(cur, u);
        }
        update(1, cur);
    }
    for (long long i = 1; i <= m; i++) {
        long long price, nm, cur = 0;
        cin >> price >> nm;
        for (long long j = 1; j <= nm; j++) {
            long long u;
            cin >> u;
            setbit(cur, u);
        }
        if (cakes[cur].empty()) {
            cakes[cur].emplace_back(price, i);
        } else if (cakes[cur].size() == 1) {
            auto fst = cakes[cur][0], snd = make_pair(price, i);
            if (fst.first > snd.first) swap(fst, snd);
            cakes[cur][0] = fst;
            cakes[cur].push_back(snd);
        } else {
            auto fst = cakes[cur][0], snd = cakes[cur][1];
            if (fst.first > snd.first) swap(fst, snd);
            if (price < fst.first) {
                cakes[cur][0] = make_pair(price, i);
                cakes[cur][1] = fst;
            } else if (price < snd.first) {
                cakes[cur][0] = fst;
                cakes[cur][1] = make_pair(price, i);
            }
        }
    }

    long long res = 0, cst = LINF;
    pair<long long, long long> ans;
    for (auto it = cakes.begin(); it != cakes.end(); it++) {
        if (it->second.size() == 2) {
            auto cur = people[it->first];
            if (cur > res or (cur == res and it->second[0].first + it->second[1].first < cst)) {
                ans.first = it->second[0].second, ans.second = it->second[1].second;
                res = cur, cst = it->second[0].first + it->second[1].first;
            }
        }
        for (auto it2 = next(it); it2 != cakes.end(); it2++) {
            long long cur = people[it->first | it2->first];
            if (cur > res or (cur == res and it->second[0].first + it2->second[0].first < cst)) {
                ans.first = it->second[0].second, ans.second = it2->second[0].second;
                res = cur, cst = it->second[0].first + it2->second[0].first;
            }
        }
    }

    cout << ans.first << " " << ans.second << "\n";


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}