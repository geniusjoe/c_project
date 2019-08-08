import math
import sys
import random
import numpy as np

# sys.stdin = open("testdata.in", "r")
sys.stdout = open("testdata.in", "w")


def main():
    cur_str = ""
    for i in range(100000):
        t = random.random()
        if t > 0.5:
            cur_str += "4"
        else:
            cur_str += "7"
    print(cur_str)


if __name__ == "__main__":
    main()
