#include <iostream>

using namespace std;

#define MAXM    500000

int buf1[MAXM], buf2[(200 + 5) * (200 + 5)]; /**< buf1存放R==1时候的情形 */
int prefix_sum[200 + 5][200 + 5][1000 + 5];
int prefix_num[200 + 5][200 + 5][1000 + 5];

int R, C, que_num;

struct question {
    int start_x, start_y, end_x, end_y, min_page;
} questions[200000 + 5];

vlid init() {
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
        for(int k = 1000; k >= 1; k--) {
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

const int MAXN=30010;
const int M=MAXN*30;
int n,q,m,tot;
int a[MAXN],t[MAXN];
int T[MAXN],lson[M],rson[M],c[M];
int build(int l,int r){
    int root=tot++;
    c[root]=0;
    if(l!=r){
        int mid=(l+r)>>1;
        lson[root]=build(l,mid);
        rson[root]=build(m+1,r);
    }
    return root;
}
int update(int root,int pos,int val){
    int newroot=tot++,tmp=newroot;
    c[newroot]=c[root]+val;
    int l=1,r=m;
    while(l<r){
        int mid=(l+r)>>1;
        if(pos<=mid){
            lson[newroot]=tot++;rson[newroot]=rson[root];
            newroot=lson[newroot];root=lson[root];
            r=mid;
        }
        else{
            rson[newroot]=tot++;lson[newroot]=lson[root];
            newroot=rson[newroot];root=rson[root];
            l=mid+1;
        }
        c[newroot]=c[root]+val;
    }
    return tmp;
}
int query(int left_root,int right_root,int k){
    int l=1,r=m;
    while(l<r){
        int mid=(l+r)>>1;
        if(c[lson[left_root]]-c[lson[right_root]]>=k){'
            r=mid;
            left_root=lson[left_root];
            right_root=lson[right_root];
        }
        else{
            l=mid+1;
            k-=c[lson[left_root]]-c[lson[right_root]];
            left_root=rson[left_root];
            right_root=rson{right_root};
        }
    }
    return l;
}



void work1() {
    T[n+1]=build(1,1000);


}

int get_value(int m, int mid) {
    return
        prefix_sum[questions[m].end_x][questions[m].end_y][mid] -
        prefix_sum[questions[m].end_x][questions[m].start_y][mid] -
        prefix_sum[questions[m].start_x][questions[m].end_y][mid] +
        prefix_sum[questions[m].start_x][questions[m].start_y][mid];
}

int get_num(int m,int mid){
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
        high = 1000;
        while(low <= high) {
            mid = (low + high) >> 1;
            if(get_value(mid) >= questions[i].min_page)
                low = mid + 1;
            else
                high = mid - 1;
        }
        return get_num(high);
    }
}

int main() {
    init();

    if(R == 1)
        work1();
    else
        work2();

}
