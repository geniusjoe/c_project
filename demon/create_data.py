import math
import sys
import random
import numpy as np
import collections

# sys.stdin = open("testdata.in", "r")
sys.stdout = open("testdata.in", "w+")

N = 100000
print(N)
for i in range(1, N):
    j = random.randint(1, 100000)
    print(j, end=' ')
