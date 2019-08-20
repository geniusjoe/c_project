import random
import math
import sys

# sys.stdout = open("testdata.in", "w")

times = 1000000

for m in range(1, 1000):
    expt = 0
    print(m)
    for _ in range(times):
        ary = []
        gcd=0
        while True:
            j = random.randint(1, m)
            ary.append(j)
            if len(ary) == 1:
                gcd = ary[0]
            else:
                gcd = math.gcd(gcd, j)
            if gcd == 1:
                break
        expt += len(ary)
    print(expt / times)
