#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 5005;
const long long INF = 0x7f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n; /**< n个数,m个操作,以model为模 */
const int N = 1000002;
int nxt[N];
char S[N], T[N];
int slen, tlen;

void getNext()
{
    int j, k;
    j = 0; k = -1; nxt[0] = -1;
    while(j < tlen)
        if(k == -1 || T[j] == T[k])
            nxt[++j] = ++k;
        else
            k = nxt[k];

}
int KMP(int len)
{
    int n=strlen(T);

    int i=max(0,len-n),j=0;
    getNext();
    for(i; i<len;)
    {
        while(S[i]!=T[j])
        {
            if(nxt[j]==0)
            {
                j=0;
                break;
            }
            else j=nxt[j];
        }
        if(S[i]==T[j])
        {
            j++;
        }
        i++;
    }
    return j;

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
*/

    ios::sync_with_stdio(false);
    int TT;
    cin>>TT;
    cin>>S;
    slen = strlen(S);
    while(TT--)
    {
        cin>>T;
        tlen = strlen(T);
        int m=tlen;
        int c=KMP(slen);
        int i=slen-c;
        for(int j=0;j<m;j++){
            S[i++]=T[j];
        }S[i]='\0';
        slen+=m-c;
    }
    cout<<S<<"\n";

#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}