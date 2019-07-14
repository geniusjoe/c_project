import math
import sys


# sys.stdin = open("testdata.in", "r")
# sys.stdout = open("testdata.out", "w")


def main():
    T = int(input())
    for i in range(T):
        N = int(input())
        N += 1
        n = N // 7
        c = N % 7
        ans = (n * (n - 1) // 2 * 21) + n * (21 - (7 - c) * (7 - c - 1) // 2)
        ans %= 1e9 + 7
        print("Case " + str(i+1) + ": " + str(int(ans)))


if __name__ == "__main__":
    main()
