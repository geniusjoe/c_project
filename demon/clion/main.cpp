#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 300500;
const long long PHI = (long long) 1e9 + 6;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;

long long n, m, q;
long long tar[MAXN];
vector<tuple<long long, long long, long long>> res;

struct item {
    long long id, nm, delta;

    bool operator<(item item1) {
        return this->nm < item1.nm;
    }
} items[MAXN];

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
    6.0-1子矩阵子序列:前缀和,异或和
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
    cin >> n;
    for (long long i = 1; i <= n; i++) {
        items[i].id = i;
        cin >> items[i].nm;
    }
    for (long long i = 1; i <= n; i++) cin >> tar[i];
    sort(tar + 1, tar + 1 + n), sort(items + 1, items + 1 + n);

    long long sm = 0;
    for (long long i = 1; i <= n; i++) {
        items[i].delta = items[i].nm - tar[i];
        sm += items[i].delta;
    }
    if (sm != 0) {
        cout << "NO" << endl;
    } else {
        bool flg = true;
        long long tail = 1;
        for (long long front = 1; front <= n; front++) {
            if (items[front].delta > 0) {
                cout << "NO" << '\n';
                flg = false;
                break;
            } else {
                while (items[front].delta < 0) {
                    while (items[tail].delta <= 0) tail++;
                    long long d = min(-items[front].delta, items[tail].delta);
                    res.emplace_back(items[front].id, items[tail].id, d);
                    items[front].delta += d, items[tail].delta -= d;
                }
            }
        }
        if (flg) {
            cout << "YES" << '\n';
            cout << res.size() << '\n';
            for (auto it:res) {
                cout << get<0>(it) << " " << get<1>(it) << " " << get<2>(it) << '\n';
            }
        }
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}