#include<bits/stdc++.h>
#define local
#define debu
using namespace std;

const int MAXN = 500010;

long long buf[MAXN];

long long n, m, k;

template<class T>
inline bool scan_d(T&ret) {
    char c;
    int sgn;
    if(c = getchar(), c == EOF)
        return 0;
    while(c != '-' && (c < '0' || c > '9'))
        c = getchar();
    sgn = (c == '-')    ? -1 : 1;
    ret = (c == '-') ?    0 : (c - '0');
    while(c = getchar(), c >= '0' && c <= '9')
        ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}


long long Search(long long num, long long low, long long high) {
    long long mid;
    while(low < high) {
        mid = (low + high) >> 1;
        if(num >= buf[mid])
            low = mid + 1;
        else
            high = mid - 1;
    }
    return high;
}

int main() {

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    //ios::sync_with_stdio(false);


    scan_d(n), scan_d(m), scan_d(k);

    for(long long i = 1; i <= m; i++)
        scan_d(buf[i]);

    long long  cnt1 = 0, cnt2 = 0, res = 0;

    cnt1=lower_bound(buf+1,buf+1+m,k)-buf-1;
    if(buf[cnt1+1]==k)    cnt1++;
    k += cnt1;

    if(cnt1 == 0||cnt1==m)
        cout << 1 << endl;
    else {
        res++;
        while(cnt2 <= m) {

            cnt2=lower_bound(buf+cnt1+1,buf+1+m,k)-buf-1;
            if(buf[cnt2+1]==k)    cnt2++;
            if(cnt2 == cnt1)
                break;
            else    {
                k += cnt2 - cnt1;
                cnt1 = cnt2;
                res++;
            }
        }
        if(cnt2 == m)
            cout << res << endl;
        else
            cout << res + 1 << endl;
    }
}
