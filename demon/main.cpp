#include<bits/stdc++.h>
#define local
#define debu
using namespace std;

#define MAXM    500000+5

int buf[100000 + 5], order[100000 + 5];
int init_num, del_num;

const int MAXN = 60010;
const int M = 2500010;
int n, q, m, tot;
int a[MAXN], t[MAXN];
int T[MAXN], lson[M], rson[M], c[M];
int S[MAXN];
void Init_hash(int k) {
    sort(t, t + k);
    m = unique(t, t + k) - t;
}
int hash(int x) {
    return lower_bound(t, t + m, x) - t;
}
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
    int newroot = tot++, tmp = newroot;
    int l = 0, r = m - 1;
    c[newroot] = c[root] + val;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(pos <= mid) {
            lson[newroot] = tot++;
            rson[newroot] = rson[root];
            newroot = lson[newroot];
            root = lson[root];
            r = mid;
        } else {
            rson[newroot] = tot++;
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
void add(int x, int pos, int val) {
    while(x <= n) {
        S[x] = Insert(S[x], pos, val);
        x += lowbit(x);
    }
}
int sum(int x) {
    int ret = 0;
    while(x > 0) {
        ret += c[lson[use[x]]];
        x -= lowbit(x);
    }
    return ret;
}
int Query(int left, int right, int k, int type) { /**< type==0 代表后面的点，type==1代表前面的点 */
    int left_root = T[left - 1];
    int right_root = T[right];
    int l = 0, r = m - 1;
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
                for(int i = left - 1; i; i -= lowbit(i)) {
                    res -= rson[use[i]];
                }
                for(int i = right; i; i -= lowbit(i)) {
                    res += rson[use[i]];
                }
            }
            for(int i = left - 1; i; i -= lowbit(i)) {
                res -= rson[use[i]];
                use[i] = lson[use[i]];
            }
            for(int i = right; i; i -= lowbit(i)) {
                res += rson[use[i]];
                use[i] = lson[use[i]];
            }
            left_root = lson[left_root];
            right_root = lson[right_root];
        } else {
            l = mid + 1;
            if(type == 1) {
                for(int i = left - 1; i; i -= lowbit(i)) {
                    res -= lson[use[i]];
                }
                for(int i = right; i; i -= lowbit(i)) {
                    res += lson[use[i]];
                }
            }
            for(int i = left - 1; i; i -= lowbit(i))
                use[i] = rson[use[i]];
            for(int i = right; i; i -= lowbit(i))
                use[i] = rson[use[i]];
            left_root = rson[left_root];
            right_root = rson[right_root];
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

    int res = 0;

    T[0] = build(1, init_num);
    for(int i = 1; i <= init_num; i++) {
        res += Query(1, i - 1, buf[i], 0);
        for(int j = i; j; j -= lowbit(j))
            T[j] = Insert(T[j], buf[i], 1);
    }

    for(int i = 1; i <= del_num; i++) {
        int cur_del;
        cin >> cur_del;

        res -= Query(1, order[cur_del], cur_del, 0);
        res -= Query(order[cur_del], init_num, cur_del, 1);
        cout<<res<<endl;

        for(int j = cur_del; j; j -= lowbit(j)){
            T[j] = Insert(T[j], cur_del, -1);
        }
    }
}

