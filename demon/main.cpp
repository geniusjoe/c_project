#include <iostream>

using namespace std;

#define MAXM    500000

int buf1[MAXM], buf2[(200 + 5) * (200 + 5)]; /**< buf1存放R==1时候的情形 */
int prefix_sum[200 + 5][200 + 5][1000 + 5];
int prefix_num[200 + 5][200 + 5][1000 + 5];

int R, C, M;

struct question {
    int start_x, start_y, end_x, end_y, min_page;
} questions[200000 + 5];

vlid init() {
    cin >> R >> C >> M;
    if(R == 1)
        for(int i = 1; i <= C; i++)
            cin >> buf1[i];
    else
        for(int i = 1; i <= R; i++) {
            for(int j = 1; j <= C; j++) {
                cin >> buf2[i][j];
            }
        }

    for(int i = 1; i <= M; i++)
        cin >> questions[i].start_x >> questions[i].start_y >>
            questions[i].end_x >> questions[i].end_y >> questions[i].min_page;

    if(R != 1) {
        for(int k = 1; k <= 1000; k++) {
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

void work1() {



}

int get_value(int m, int mid) {
    return
        prefix_sum[questions[m].end_x][questions[m].end_y][mid] -
        prefix_sum[questions[m].end_x][questions[m].start_y][mid]-
        prefix_sum[questions[m].start_x][questions[m].end_y][mid]+
        prefix_sum[questions[m].start_x][questions[m].start_y][mid];
}


void work2() {
    for(int i = 1; i <= M; i++) {
        int mid;
        int low = 1;
        high = 1000;
        while(low <= high) {
            mid = (low + high) >> 1;
            if(get_value(mid) > questions[i].min_page)
                high = mid - 1;
            else
                low = mid + 1;
        }
        return get_num(mid);
    }
}


int main() {
    init();

    if(R == 1)
        work1();
    else
        work2();

}
