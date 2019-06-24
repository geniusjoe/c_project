#include<bits/stdc++.h>
#define local
#define debu
using namespace std;

#define MAXM    500000+5

int buf[100000 + 5], order[100000 + 5];
int init_num, del_num;

const int MAXN = 100005;
const int M = 25000100;
int n, q, m, tot;
int a[MAXN], t[MAXN];
int T[MAXN], lson[M], rson[M], c[M];
int S[MAXN];
int build(int l, int r) {
    int root = tot++;
    c[root] = 0;
    if(l != r) {
        int mid = (l + r) >> 1;
        lson[root] = build(l, mid);
        rson[root] = build(mid + 1, r);
    }
    return root;
}

int Insert(int root, int pos, int val) {
    int newroot;
    if(!root)
        newroot = tot++;
    else
        newroot = root;
    int tmp = newroot;
    int l = 1, r = m ;
    c[newroot] = c[root] + val;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(pos <= mid) {
            if(!lson[newroot]) lson[newroot]=tot++;
            rson[newroot] = rson[root];
            newroot = lson[newroot];
            root = lson[root];
            r = mid;
        } else {
            if(!rson[newroot]) rson[newroot]=tot++;
            lson[newroot] = lson[root];
            newroot = rson[newroot];
            root = rson[root];
            l = mid + 1;
        }
        c[newroot] = c[root] + val;
    }
    return tmp;
}
int lowbit(int x) {
    return x & (-x);
}
int use[MAXN];
int Query(int left, int right, int k, int type) { /**< type==0 代表后面的点，type==1代表前面的点 */
    int l = 1, r = m;
    int res = 0;
    for(int i = left - 1; i; i -= lowbit(i))
        use[i] = S[i];
    for(int i = right; i; i -= lowbit(i))
        use[i] = S[i];
    while(l < r) {
        int mid = (l + r) >> 1;
        if(mid >= k) {
            r = mid;
            if(type == 0) {
                for(int i = left - 1; i; i -= lowbit(i))
                    res -= c[rson[use[i]]];
                for(int i = right; i; i -= lowbit(i))
                    res += c[rson[use[i]]];
            }
            for(int i = left - 1; i; i -= lowbit(i))
                use[i] = lson[use[i]];
            for(int i = right; i; i -= lowbit(i))
                use[i] = lson[use[i]];

        } else {
            l = mid + 1;
            if(type == 1) {
                for(int i = left - 1; i; i -= lowbit(i))
                    res -= c[lson[use[i]]];
                for(int i = right; i; i -= lowbit(i))
                    res += c[lson[use[i]]];
            }
            for(int i = left - 1; i; i -= lowbit(i))
                use[i] = rson[use[i]];
            for(int i = right; i; i -= lowbit(i))
                use[i] = rson[use[i]];
        }
    }
    return res;
}
void Modify(int x, int p, int d) {
    while(x <= n) {
        S[x] = Insert(S[x], p, d);
        x += lowbit(x);
    }
}
int main() {

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    ios::sync_with_stdio(false);

    cin >> init_num >> del_num;
    for(int i = 1; i <= init_num; i++) {
        cin >> buf[i];
        order[buf[i]] = i;
    }

    long long res = 0;
    n = m = init_num;


    T[0] = build(1, init_num);
    for(int i = 1; i <= init_num; i++)
        S[i] = T[0];

    for(int i = 1; i <= init_num; i++) {
        res += Query(1, i - 1, buf[i], 0);
        Modify(i, buf[i], 1);
    }

    for(int i = 1; i <= del_num; i++) {
        int cur_del;
        cin >> cur_del;

        cout << res << endl;

        res -= Query(1, order[cur_del], cur_del, 0);
        res -= Query(order[cur_del], init_num, cur_del, 1);

        Modify(order[cur_del], cur_del, -1);
    }
}
