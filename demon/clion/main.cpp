#include<bits/stdc++.h>

#define loca
#define debu
using namespace std;

const int MAXN = 200025;
const int INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 1000000007;

long long n, m, T, M;
map<long, long> nm;

struct ele {
    long long id, val;

    bool operator<(ele ele1) {
        return this->val < ele1.val;
    }
} eles[MAXN];

bool is_ok(int m) {

    if (nm[m] == n - 2)
        return true;

    return false;
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

    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; i++) {
        eles[i].id = i;
        cin >> eles[i].val;
    }

    if (n <= 3) {
        cout << 1 << endl;
    } else {
        sort(eles + 1, eles + 1 + n);
        for (int i = 2; i <= n; i++)
            nm[eles[i].val - eles[i - 1].val]++;

        bool flg = false;
        nm[eles[2].val - eles[1].val]--;
        if (!flg && is_ok(eles[3].val - eles[2].val)) {
            cout << eles[1].id << endl;
            flg = true;
        }
        nm[eles[2].val - eles[1].val]++;

        nm[eles[n].val - eles[n - 1].val]--;
        if (!flg && is_ok(eles[2].val - eles[1].val)) {
            cout << eles[n].id << endl;
            flg = true;
        }
        nm[eles[n].val - eles[n - 1].val]++;

        for (int i = 2; i <= n - 1; i++) {
            nm[eles[i].val - eles[i - 1].val]--;
            nm[eles[i + 1].val - eles[i].val]--;
            nm[eles[i + 1].val - eles[i - 1].val]++;
            if (!flg && is_ok(eles[i + 1].val - eles[i - 1].val)) {
                flg = true;
                cout << eles[i].id << endl;
                break;
            }
            nm[eles[i].val - eles[i - 1].val]++;
            nm[eles[i + 1].val - eles[i].val]++;
            nm[eles[i + 1].val - eles[i - 1].val]--;
        }

        if (!flg)
            cout << "-1" << endl;
    }


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