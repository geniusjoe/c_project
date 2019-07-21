#include<bits/stdc++.h>

using namespace std;

#define local

const int maxn = 100000 + 5;
bool vis[28 + 5];

int buf1[maxn], buf2[maxn];
int n, c;
long long ans;
int odd_cnt, even_cnt;
int odd_len, even_len;

struct clr {
    int l, r;
    int i;
} odd[maxn], even[maxn];

int main() {
#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif

    ios::sync_with_stdio(false);

    cin >> n >> c;

    for (int i = 1; i <= n; i++) {
        if (i % 2 == 1) cin >> buf1[++odd_cnt];
        else cin >> buf2[++even_cnt];
    }

    int odd_head = 1, even_head = 1;
    for (int i = 1; i <= odd_cnt; i++) {
        if (buf1[i] == buf1[odd_head]) continue;
        else {
            odd[++odd_len].i = buf1[odd_head];
            odd[odd_len].l = 2 * odd_head - 1;
            odd[odd_len].r = 2 * i - 1;
        }
    }
    for (int i = 1; i <= even_cnt; i++) {
        if (buf2[i] == buf2[even_cnt]) continue;
        else {
            even[++even_len].i = buf2[even_head];
            even[even_len].l = 2 * even_head;
            even[even_len].r = 2 * i;
        }
    }

    int odd_ptr=1,even_ptr=1;
    while(odd_ptr<=odd_len&&even_ptr<=even_len){
        if(odd[odd_ptr].i)
    }

}