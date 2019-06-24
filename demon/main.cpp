#include<bits/stdc++.h>
#define local
#define debu
using namespace std;

#define MAXM    500000+5

int buf1[MAXM];

const int MAXN = 200005;
const int M = MAXN * 50;

int mission_num, time_num, rnk_cnt;
struct mission {
    int start, finish, val, rnk;
    bool operator<(mission mission1) {
        return this->val < mission1.val;
    }
} missions[MAXN];

struct mission1 {
    int pos, rnk;
    bool type;
} brk_missions[MAXN * 2 + 5];

void init() {
    cin >> mission_num >> time_num;
    for(int i = 1; i <= init_num; i++) {
        cin >> missions[i].start >> missions[i].finish >> missions[i].val;
    }
    sort(missions + 1, missions + 1 + mission_num);

    for(int i = 1; i <= mission_num; i++) {
        if(missions[i].val != missions[i - 1].val)
            missions[i].rnk = ++rnk_cnt;
        else {
            missions[i].rnk = rnk_cnt;
            reverse_rnk[rnk_cnt] = missions[i].val;
        }
    }
    /**< type==true 代表起点 */
    /**< 2*i 代表起点 */
    for(int i = 1; i <= mission_num; i++) {
        brk_missions[i * 2].pos = missions[i].start;
        brk_missions[i * 2].type = true;
        brk_missions[i * 2].rnk = missions[i].rnk;
        brk_missions[i * 2 + 1].pos = missions[i].finish;
        brk_missions[i * 2 + 1].type = false;
        brk_missions[i * 2 + 1].rnk = missions[i].rnk;
    }
}


int n, q, m, tot;
int a[MAXN], t[MAXN];
int times[MAXN];
int T[MAXN], lson[M], rson[M], c[M];
int seg_sum[M], seg_num[M];
int build(int l, int r) {
    int root = tot++;
    seg_sum[root] = 0;
    seg_num[root] = 0;
    if(l != r) {
        int mid = (l + r) >> 1;
        lson[root] = build(l, mid);
        rson[root] = build(mid + 1, r);
    }
    return root;
}
int update(int root, int pos) {
    int newroot = tot++, tmp = newroot;
    seg_sum[newroot] = seg_sum[root] + pos;
    seg_num[newroot] = seg_num[root] + 1;
    int l = 1, r = max_page;
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
        seg_sum[newroot] = seg_sum[root] + pos;
        seg_num[newroot] = seg_num[root] + 1;
    }
    return tmp;
}
void query(int left_root, int right_root, int k) {
    if(seg_sum[left_root] - seg_sum[right_root] < k) {
        cout << "Poor QLW" << endl;
        return;
    }
    int l = 1, r = m, times = 0;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(seg_sum[rson[left_root]] - seg_sum[rson[right_root]] >= k) {
            l = mid + 1;
            left_root = rson[left_root];
            right_root = rson[right_root];
        } else {
            r = mid;
            times += seg_num[rson[left_root]] - seg_num[rson[right_root]];
            k -= seg_sum[rson[left_root]] - seg_sum[rson[right_root]];
            left_root = lson[left_root];
            right_root = lson[right_root];
        }
    }
    if(k % r == 0)
        cout << times + k / r << endl;
    else
        cout << times + k / r + 1 << endl;
}
void _copy(int x,int y){
    T[x]=T[y];
    lson[x]=lson[y];
    rson[x]=rson[y];
    seg_sum[x]=seg_sum[y];
    seg_num[x]=seg_num[y];

}

void work1() {
    n = C;
    m = rnk_cnt;
    T[n + 1] = build(1, m);
    for(int i = n; i >= 1; i--) {
        T[i] = update(T[i + 1], buf1[i]);
    }
    for(int i = 1; i <= que_num; i++) {
        query(T[questions[i].start_y], T[questions[i].end_y + 1], questions[i].min_page);
    }
}

int main() {

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    ios::sync_with_stdio(false);

    init();

    work1();

}
