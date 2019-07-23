#include<bits/stdc++.h>

using namespace std;

const int maxn = 5e5;

#define loca
#define debu

int n, m;

long long buf[maxn];
long long pre_sum[maxn];
long long up, down, cur_gcd;

long long gcd(long long a, long long b) { return (!b) ? a : gcd(b, a % b); }

bool cmp(int a, int b) {
    return a > b;
}

int main() {
#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif

    ios::sync_with_stdio(false);

    while (cin >> n >> m) {
        cur_gcd = up = down = 0;

        if (n == 1) {
            cin >> buf[1];
            up = (m - buf[1]) * (m - buf[1]);
            down = m*m;
            cur_gcd = gcd(up, down);
            up /= cur_gcd, down /= cur_gcd;
            if (down == 1)
                cout << up << endl;
            else
                cout << up << '/' << down << endl;
            continue;
        }


        for (int i = 1; i <= n; i++) {
            cin >> buf[i];
        }
        sort(buf + 1, buf + 1 + n, cmp);

        pre_sum[1] = buf[1] - buf[2];
        for (int i = 2; i < n; i++) pre_sum[i] = pre_sum[i - 1] + i * (buf[i] - buf[i + 1]);

        int pos = lower_bound(pre_sum + 1, pre_sum + n, m) - pre_sum;

        if(pos==n){
            for(int i=1;i<=n;i++){
                up+=buf[i];
            }
            up-=m;
            up*=up;
            down=n*m*m;
        }

        else{
            for (int i = 1; i <= pos; i++) {
                up += buf[i];
            }
            up -= m;
            up *= up;
            for (int i = pos + 1; i <= n; i++) up += pos * buf[i] * buf[i];

            down = pos * m * m;
        }


        cur_gcd = gcd(up, down);
        up /= cur_gcd, down /= cur_gcd;
        if (down == 1) cout << up << endl;
        else {
            cout << up << '/' << down << endl;
        }

    }


}