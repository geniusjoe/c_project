#include <bits/stdc++.h>

#define local
const int INF = 0x3f3f3f3f;
using namespace std;

#define setbit(x, y) x|=(1ll<<y)

#define clrbit(x, y) x&=~(1ll<<y)

#define reversebit(x, y) x^=(1ll<<y)

#define getbit(x, y) ((x) >> (y)&1ll)

long long T, N, M;
const int MAXN = 500;

long long buf[MAXN + 5][MAXN + 5], CMAX[MAXN + 5], CMIN[MAXN + 5], res;

long long maxq[MAXN + 10], minq[MAXN + 10];

// 1为下标开始
long long mono_q(const long long cmax[], const long long cmin[], const long long m) {
    long long maxhead = 0, maxtail = 0, minhead = 0, mintail = 0;
    long long l = 1;
    long long len = 0;
    for (int i = 1; i <= N; i++) {
        while (maxhead < maxtail && cmax[i] > cmax[maxq[maxtail - 1]]) maxtail--;
        maxq[maxtail++] = i;
        while (minhead < mintail && cmin[i] < cmin[minq[mintail - 1]]) mintail--;
        minq[mintail++] = i;

        while (minhead < mintail && maxhead < maxtail && cmax[maxq[maxhead]] - cmin[minq[minhead]] > m) {
            l = min(maxq[maxhead], minq[minhead]) + 1;  //跳到l + 1
            while (minhead < mintail && minq[minhead] < l) minhead++;
            while (maxhead < maxtail && maxq[maxhead] < l) maxhead++;
        }

        len = max(len, i - l + 1);
    }
    return len;
}


int main() {
    ios::sync_with_stdio(false);

#ifdef  local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif

    cin >> T;
    while (T--) {
        cin >> N >> M;
        res = 0;
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                cin >> buf[i][j];

        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                CMAX[j] = 0;
                CMIN[j] = INF;
            }
            for (int j = i; j <= N; j++) {
                for (int k = 1; k <= N; k++) {
                    CMAX[k] = max(CMAX[k], buf[j][k]);
                    CMIN[k] = min(CMIN[k], buf[j][k]);
                }
                res = max(res, mono_q(CMAX, CMIN, M) * (j - i + 1));
            }
        }
        cout << res << endl;
    }

    return 0;
}