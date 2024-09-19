from cs50 import *


def main():

    height = get_int("Height: ")

    while height < 1 or height > 8:
        print("Height must be a value between 1 and 8 (inclusive)")
        height = get_int("Height: ")

    for i in range(1, height + 1):
        print(" " * (height - i), end="")
        print("#" * i, end="")
        print("  ", end="")
        print("#" * i)


if __name__ == "__main__":
    main()
