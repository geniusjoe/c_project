#include<bits/stdc++.h>

#define loca
#define debu
using namespace std;

const int MAXN = 100005;
const int INF = 0x3f3f3f3f;

char tmp[20][20];
char raw[MAXN];

long long n, m, T, k;

bool check(int l, int r) {
    for (int i = 1; i <= n; i++) {
        if (r - l + 1 < strlen(tmp[i]))
            continue;
        else {
            int cur_len = strlen(tmp[i]);
            bool flg = true;
            for (int j = 0; j < cur_len; j++) {
                if (tmp[i][cur_len - j - 1] == raw[r - j])
                    continue;
                else {
                    flg = false;
                    continue;
                }
            }
            if (flg) return false;
        }
    }
    return true;
}

int main() {

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    //ios::sync_with_stdio(false);

    scanf("%s", raw);
    int l = 0, r = 0, res_len = 0, res_pos = 0;
    scanf("%I64d ", &n);
    for (int i = 1; i <= n; i++)
        scanf("%s", tmp[i]);
    while (r < strlen(raw)) {
        while (l <= r) {
            if (check(l, r)) {
                if (r - l + 1 > res_len) {
                    res_len = r - l + 1;
                    res_pos = l;
                }
                break;
            }
            l++;
        }
        r++;
    }
    cout << res_len << " " << res_pos << endl;

    return 0;
}