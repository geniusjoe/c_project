#include<bits/stdc++.h>
#define loca
#define debu
using namespace std;

const int MAXN = 10000;

char buf[1000005];
int buf1[1000005];

char alphabet[] = {
    'A',
    'A', 'B', 'C', 'D', 'E', 'F', 'G',
    'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U',
    'V', 'W', 'X', 'Y', 'Z'
};

int main() {

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    //ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while(T--) {
        scanf("%s", buf);
        bool flg1 = false, flg2 = false;
        int type = 2;
        int len = strlen(buf);

        for(int i = 0; i < len; i++) {
            if(buf[i] >= '0' && buf[i] <= '9') {
                if(flg1 == false)
                    flg1 = true;
                if(flg2 == true)
                    type = 1;
            } else {
                if(flg1 == true)
                    flg2 = true;
            }
        }

        if(type == 1) {
            int c_pos = 0;
            for(int i = 0; i < len; i++) {
                if(buf[i] == 'C') {
                    c_pos = i;
                    break;
                }
            }

            int raw_ext = 0, col_ext = 0;

            for(int i = 1; i < c_pos; i++) {
                raw_ext = raw_ext * 10 + buf[i] - '0';
            }
            for(int i = c_pos + 1; i < len; i++) {
                col_ext = col_ext * 10 + buf[i] - '0';
            }

            int cnt = 0;
            /*
                        if(col_ext == 702) {
                            cout<<"ZZ";
                        }
                        else if(col_ext == 18278) {
                            cout<<"ZZZ";
                        }
                        else if(col_ext==475254){
                            cout<<"ZZZZ";
                        }
                        else {*/
            while(col_ext > 26) {
                int tmp = col_ext % 26;
                if(tmp == 0) {
                    col_ext = (col_ext - 26) / 26;
                    buf1[++cnt] = 26;
                } else {
                    col_ext = col_ext / 26;
                    buf1[++cnt] = tmp;
                }
            }

            cout << alphabet[col_ext];
            for(int i = cnt; i >= 1; i--) {
                cout << alphabet[buf1[i]];
            }

            cout << raw_ext << endl;
            continue;
        }

        else if(type == 2) {
            int second_pos = 0;
            for(int i = 0; i < len; i++) {
                if(buf[i] >= '0' && buf[i] <= '9') {
                    second_pos = i;
                    break;
                }
            }

            int col_num = 0, raw_num = 0;

            for(int i = 0; i < second_pos; i++) {
                col_num = col_num * 26 + (buf[i] - 'A') + 1;
            }

            for(int i = second_pos; i < len; i++) {
                raw_num = raw_num * 10 + buf[i] - '0';
            }

            cout << "R" << raw_num << "C" << col_num << endl;
        }
    }

