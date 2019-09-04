import random
import math
import sys

# sys.stdout = open("testdata.in", "w")

N = 1000
for i in range(1, N):
    print(i)
    for j in range(0, i + 10000):
        if i - j == i ^ j:
            print(j)
    print("\n")
