import math
import sys
import random
import numpy as np


# sys.stdin = open("testdata.in", "r")
# sys.stdout = open("testdata.out", "w")


def main():
    for i in range(1,100000):
        cnt = 0
        times = 1000000
        for j in range(times):
            if i == 1:
                r1 = i
            else:
                r1 = np.random.randint(1, i + 1)
            if r1 == 1:
                l1 = 1
            else:
                l1 = np.random.randint(1, r1 + 1)
            if i == 1:
                r2 = 1
            else:
                r2 = np.random.randint(1, i + 1)
            if r2 == 1:
                l2 = 1
            else:
                l2 = np.random.randint(1, r2 + 1)
            if l1 > l2:
                tmp1 = l1
                tmp2 = r1
                l1 = l2
                r1 = r2
                l2 = tmp1
                r2 = tmp2
            if r1 >= l2 :
                cnt += 1
        print(i, cnt / times)


if __name__ == "__main__":
    main()
