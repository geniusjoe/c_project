import random
import math
import sys

sys.stdout = open("testdata.in", "w")

N = 2000
for i in range(1, N):
    j=random.randint(1,1e9)
    print(j,end=' ')