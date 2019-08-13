import math
import sys
import random
import numpy as np
import collections

# sys.stdin = open("testdata.in", "r")
sys.stdout = open("testdata.in", "w")

res = []
for i in range(10):
    j = random.randint(1, 10000000000000)
    cur_fct = []
    for k in range(1, 10000000):
        if k * k > j:
            break
        elif j % k == 0:
            cur_fct.append(k)
            if j / k != k:
                cur_fct.append(j / k)
    if len(cur_fct) > 2:
        res.append(j)
        cur_fct.sort()
        print(len(cur_fct) - 2)
        for e in cur_fct[1:-1]:
            print(int(e), end=" ")
        print("")

print(res)
