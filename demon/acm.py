import random
import math
import sys

sys.stdout = open("testdata.in", "w")

print("1\n199999")
for i in range(199999):
    print(random.randint(1,199999),end=' ')
print()
