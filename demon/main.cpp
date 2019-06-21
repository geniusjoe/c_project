#include <iostream>

#define local

using namespace std;

#define MAXM    500000+5

int R, C, que_num;
const int max_page = 1000;

int buf1[MAXM], buf2[(200 + 5) * (200 + 5)]; /**< buf1存放R==1时候的情形 */
int prefix_sum[200 + 5][200 + 5][max_page + 5];
int prefix_num[200 + 5][200 + 5][max_page + 5];



struct question {
    int start_x, start_y, end_x, end_y, min_page;
} questions[200000 + 5];

void init() {
    cin >> R >> C >> que_num;
    if(R == 1)
        for(int i = 1; i <= C; i++)
            cin >> buf1[i];
    else
        for(int i = 1; i <= R; i++) {
            for(int j = 1; j <= C; j++) {
                cin >> buf2[i][j];
            }
        }

    for(int i = 1; i <= que_num; i++)
        cin >> questions[i].start_x >> questions[i].start_y >>
            questions[i].end_x >> questions[i].end_y >> questions[i].min_page;

    if(R != 1) {
        for(int k = max_page; k >= 1; k--) {
            for(int i = 1; i <= R; i++) {
                for(int j = 1; j <= C; j++) {

                    prefix_sum[i][j][k] = prefix_sum[i - 1][j][k] + prefix_sum[i][j - 1][k] - prefix_sum[i - 1][j - 1][k];
                    prefix_num[i][j][k] = prefix_num[i - 1][j][k] + prefix_num[i][j - 1][k] - prefix_num[i - 1][j - 1][k];

                    if(buf2[i][j] == k) {
                        prefix_sum[i][j][k] += k;
                        prefix_num[i][j][k]++;
                    }
                }
            }

        }
    }
}

const int MAXN = 500000;
const int M = MAXN * 30;
int n, q, m, tot;
int a[MAXN], t[MAXN];
int times[MAXN];
int T[MAXN], lson[M], rson[M], c[M];
int seg_sum[MAXN], seg_num[MAXN];
int build(int l, int r) {
    int root = tot++;
    c[root] = 0;
    if(l != r) {
        int mid = (l + r) >> 1;
        lson[root] = build(l, mid);
        rson[root] = build(m + 1, r);
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
        seg_num[newroot]++;
    }
    return tmp;
}
int query(int left_root, int right_root, int k) {
    if(seg_sum[left_root] - seg_sum[right_root]<k cout<<"Poor QLW"<<endl;

    int l = 1, r = m;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(seg_sum[rson[left_root]] - seg_sum[rson[right_root]] >= k) {
            l = mid + 1;
            left_root = rson[left_root];
            right_root = rson[right_root];
        } else {
            r = mid;
            k -= seg_sum[rson[left_root]] - seg_sum[rson[right_root]];
            left_root = lson[left_root];
            right_root = lson{right_root};
        }
    }
    cout<<seg_num[r]<<endl;
}


void work1() {
    n = C;
    m = max_page;
    T[n + 1] = build(1, max_page);
    for(int i = n; i >= 1; i--) {
        update(T[i + 1], buf1[i]);
    }
    for(int i = 1; i <= que_num; i++) {
        query(T[questions[i].start_y], T[questions[i].end_y], questions[i].min_page);
    }
}

int get_value(int m, int mid) {
    return
        prefix_sum[questions[m].end_x][questions[m].end_y][mid] -
        prefix_sum[questions[m].end_x][questions[m].start_y][mid] -
        prefix_sum[questions[m].start_x][questions[m].end_y][mid] +
        prefix_sum[questions[m].start_x][questions[m].start_y][mid];
}

int get_num(int m, int mid) {
    return
        prefix_num[questions[m].end_x][questions[m].end_y][mid] -
        prefix_num[questions[m].end_x][questions[m].start_y][mid] -
        prefix_num[questions[m].start_x][questions[m].end_y][mid] +
        prefix_num[questions[m].start_x][questions[m].start_y][mid];
}

void work2() {
    for(int i = 1; i <= que_num; i++) {
        int mid;
        int low = 1;
        high = max_page;
        if(get_value(i, 1) < questions[i].min_page) {
            cout << "Poor QLW" << endl;
            continue;
        }
        while(low <= high) {
            mid = (low + high) >> 1;
            if(get_value(i, mid) < questions[i].min_page)
                high = mid - 1;
            else
                low = mid + 1;
        }
        cout << get_num(i, high) << endl;
    }
}

int main() {

#ifdef local
    freopen("testdata.in", "r", stdin);
    freopen("testdata.output", "w", stdout);
#endif // local

    ios::sync_with_stdio(false);

    init();

    if(R == 1)
        work1();
    else
        work2();

}
