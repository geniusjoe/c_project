#include<bits/stdc++.h>
#define local
#define debu
using namespace std;

const int MAXN = 10000;
int prime[MAXN + 1];
void getPrime() {
    memset(prime, 0, sizeof(prime));
    for(int i = 2; i <= MAXN; i++) {
        if(!prime[i])
            prime[++prime[0]] = i;
        for(int j = 1; j <= prime[0] && prime[j] <= MAXN / i; j++) {
            prime[prime[j]*i] = 1;
            if(i % prime[j] == 0)
                break;
        }
    }
}

long long factor[100][2];
int fatCnt;
int getFactors(long long x) {
    fatCnt  = 0;
    long long tmp = x;
    for(int i = 1; prime[i] <= tmp / prime[i]; i++) {
        factor[fatCnt][1] = 0;
        if(tmp % prime[i] == 0) {
            factor[fatCnt][0] = prime[i];
            while(tmp % prime[i] == 0) {
                factor[fatCnt][1]++;
                tmp /= prime[i];
            }
            fatCnt++;
        }
    }
    if(tmp != 1) {
        factor[fatCnt][0] = tmp;
        factor[fatCnt++][1] = 1;
    }
    return fatCnt;
}

int buf[10001000];



int main() {

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    //ios::sync_with_stdio(false);

    getPrime();
    for(int i = 1; i <= 10000010; i++) {
        buf[i] = getFactors(i);
    }


    getPrime();
    int T;
    cin >> T;

    #ifdef debug
    int tmp=0;
    for(int i=1;i<=10000000;i++)
        tmp=max(tmp,buf[i]);
    #endif // debug

    for(int k = 1; k <= T; k++) {
        int A, B, K;
        int counter = 0;
        cin >> A >> B >> K;
        if(K>8) {
            cout << "Case #" << k << ": " << 0 << endl;
            continue;
        }
        for(int i = A; i <= B; i++) {
            if(buf[i] == K)
                counter++;
        }
        cout << "Case #" << k << ": " << counter << endl;
    }

}
