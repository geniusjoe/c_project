import random
import math
import sys

sys.stdout = open("testdata.in", "w")

print(1)
print('1000000')

N = 1000000
for i in range(1, N):
    j=random.randint(1,10000)
    print(j,end=' ')