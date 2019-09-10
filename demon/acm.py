import random
import math
import sys

sys.stdout = open("testdata.in", "w")

print("200000 200000")
for i in range(200):
    j=random.randint(1,1e9)
    print(j,end=' ')
    print()

for i in range(200):
    j=random.randint(1,2)
    print(j,end=' ')
    if j==1:
        k=random.randint(1,200000)
