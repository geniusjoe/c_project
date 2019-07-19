import math
import sys


# sys.stdin = open("testdata.in", "r")
# sys.stdout = open("testdata.out", "w")


def main():
    for line in sys.stdin:
        buf = str(line).split()
        x, a, y, b = int(buf[0]), int(buf[1]), int(buf[2]), int(buf[3])
        left_res = x * b
        right_res = y * a
        if left_res < right_res:
            print("<")
        elif left_res == right_res:
            print("=")
        else:
            print(">")


if __name__ == "__main__":
    main()
