import math
import sys

sys.stdin = open("testdata.in", "r")
sys.stdout = open("testdata.out", "w")

MAXN = 10010

prime = [0 for i in range(MAXN + 1)]


def get_prime():
    for i in range(2, MAXN + 1):
        if not prime[i]:
            prime[0] += 1
            prime[prime[0]] = i
        for j in range(1, prime[0] + 1):
            if prime[j] > MAXN // i:
                break
            prime[prime[j] * i] = 1
            if i % prime[j] == 0:
                break


get_prime()
turn = int(input())
# turn = 100000000000000000000000
last = -1
for i in range(turn):
    up, down, counter = 1, 1, 1
    n = int(input())
    # n=i
    while up * prime[counter] <= n:
        up *= prime[counter]
        down *= prime[counter] + 1
        counter += 1
    gcd = math.gcd(up, down)
    up //= gcd
    down //= gcd
    if last != str(up) + '/' + str(down):
        last = str(up) + '/' + str(down)
        print(n,last)
