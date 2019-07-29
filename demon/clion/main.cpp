#include <bits/stdc++.h>

#define setbit(x, y) x|=(1ll<<y)

#define clrbit(x, y) x&=~(1ll<<y)

#define reversebit(x, y) x^=(1ll<<y)

#define getbit(x, y) ((x) >> (y)&1ll)


#define local

using namespace std;

long long T, counter, len, mod, pos;
long long buf, raw, res1, res2;
bool all_one, all_two;

// 查找二进制下第一个1的位置
int get_pos(long long buf, int start) {
    int res = -1;
    for (int i = start; i <= len; i += 2) {
        if (getbit(buf, i - 1)) {
            res = i;
            break;
        }
    }
    return res;
}


int main() {
//    ios::sync_with_stdio(false);

#ifdef  local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif

    cin >> T;
//    scanf("%d",&T);
    while (T--) {
        counter = 1;
        len = 0;
        cin >> raw;
//        scanf("%lld",&raw);
#ifdef local
        cout << raw << "\t";
#endif
        res2 = mod = 0;
        res1 = buf = raw;
        all_one = all_two = true;
//        得到数字的长度
        while (buf) {
            if (buf & 1) {
                mod += counter;
                if (counter == 1) all_two = false;
                else all_one = false;
            }
            if (counter == 1) counter = 2;
            else counter = 1;
            buf >>= 1;
            len++;
        }
        buf = raw;

//        如果当前数能被3整除
        if (mod % 3 == 0) {
            cout << 1 << " " << raw << endl;
            continue;
        }

//        如果有1也有2存在
        if (!all_one && !all_two) {
//            模1取出一个1
            if (mod % 3 == 1) {
                pos = get_pos(buf, 1);
                clrbit(res1, (pos - 1));
                setbit(res2, (pos - 1));

                pos = get_pos(buf, 2);
                setbit(res2, (pos - 1));

                assert(res1 % 3 == 0 && res2 % 3 == 0);
                assert(res1 | res2 == raw);

//            模2取出一个2
            } else if (mod % 3 == 2) {
                pos = get_pos(buf, 2);

                clrbit(res1, (pos - 1));
                setbit(res2, (pos - 1));

                pos = get_pos(buf, 1);
                setbit(res2, (pos - 1));
            }

//            如果为全1的数字
        } else if (all_one) {
//            模1取出1个1
            if (mod % 3 == 1) {
                pos = get_pos(buf, 1);
                clrbit(res1, (pos - 1));
                setbit(res2, (pos - 1));

                pos = get_pos(buf, pos + 2);
                setbit(res2, (pos - 1));

                pos = get_pos(buf, pos + 2);
                setbit(res2, (pos - 1));

//                模2取出2个1
            } else if (mod % 3 == 2) {
                pos = get_pos(buf, 1);
                clrbit(res1, (pos - 1));
                setbit(res2, (pos - 1));

                pos = get_pos(buf, pos + 2);
                clrbit(res1, (pos - 1));
                setbit(res2, (pos - 1));

                pos = get_pos(buf, pos + 2);
                setbit(res2, (pos - 1));
            }

//             如果为全2的数组
        } else {
//            如果模1取出2个2
            if (mod % 3 == 1) {
                int pos = get_pos(buf, 2);
                clrbit(res1, (pos - 1));
                setbit(res2, (pos - 1));

                pos = get_pos(buf, pos + 2);
                clrbit(res1, (pos - 1));
                setbit(res2, (pos - 1));

                pos = get_pos(buf, pos + 2);
                setbit(res2, (pos - 1));

//              如果模2取出1个2
            } else if (mod % 3 == 2) {
                int pos = get_pos(buf, 2);
                clrbit(res1, (pos - 1));
                setbit(res2, (pos - 1));

                pos = get_pos(buf, pos + 2);
                setbit(res2, (pos - 1));

                pos = get_pos(buf, pos + 2);
                setbit(res2, (pos - 1));

            }
        }

//        assert(res1%3==0&&res2%3==0);
//        assert(res1|res2==raw);

        cout << 2 << " " << res2 << " " << res1 << endl;

    }

    return 0;
}