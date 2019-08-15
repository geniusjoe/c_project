import math
import sys
import random
import numpy as np
import collections

# sys.stdin = open("testdata.in", "r")
sys.stdout = open("testdata.in", "w")

N = 100
for i in range(1, N):
    for j in range(i + 1, N):
        print(i, j, sep=" ")
