import math
import sys
import random
import numpy as np
import collections

# sys.stdin = open("testdata.in", "r")
sys.stdout = open("testdata.in", "w")


def main():
    print(10, 10, sep=" ")

    cur_str = collections.deque()
    for i in range(10):
        t = random.randint(1, 9)
        cur_str.append(t)
    for i in cur_str:
        print(i, end=" ")
    print("")

    rnd = []
    for i in range(10):
        rnd.append(random.randint(1, 10))
    rnd.sort()
    for i in rnd:
        print(i, sep='\n')

    for i in range(100):
        A = cur_str.popleft()
        B = cur_str.popleft()
        for j in rnd:
            if i == j - 1:
                print(A, B)
        if (A < B):
            t = A
            A = B
            B = t
        cur_str.appendleft(A)
        cur_str.append(B)


if __name__ == "__main__":
    main()
