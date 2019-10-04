#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 200500;
const long long PHI = (long long) 998244352;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n, K, m;

const long long MAX_BASE = 30;
long long a[MAXN], b[MAXN]; // a为所有元素的集合,b为线性基
long long cal() {
    long long res = 0;
    for (long long i = 1; i <= n; ++i) {
        for (long long j = MAX_BASE; j >= 0; --j) {
            if (a[i] >> j & 1) {
                if (b[j]) a[i] ^= b[j];
                else {
                    b[j] = a[i];
                    for (long long k = j - 1; k >= 0; --k) if (b[k] && (b[j] >> k & 1)) b[j] ^= b[k];
                    for (long long k = j + 1; k <= MAX_BASE; ++k) if (b[k] >> j & 1) b[k] ^= b[j];
                    res++;
                    break;
                }
            }
        }
    }
    return res;
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
    1.数学公式尝试化简
    2.数量值太大尝试给出递推公式
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
    cin>>n;
    for(long long i=1;i<=n;i++) cin>>a[i];
    long long cur=0;
    for(long long i=1;i<=n;i++) cur^=a[i];
    if(cur==0){
        cout<<-1<<endl;
    }else{
        cout<<cal()<<endl;
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}