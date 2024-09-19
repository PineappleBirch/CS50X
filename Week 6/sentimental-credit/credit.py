from cs50 import get_int


def main():

    ccn = get_int("What is your credit card number?\n")
    ccntemp = ccn

    count = len(str(ccn))

    total_sum = 0

    for i in range(count):
        current = ccntemp % 10
        if i % 2 != 0:
            current *= 2
            if current > 9:
                current = current % 10 + current // 10
        total_sum += current
        ccntemp //= 10

    ccntemp = ccn
    while ccntemp >= 100:
        ccntemp //= 10

    first_digit = ccntemp // 10
    second_digit = ccntemp % 10

    if total_sum % 10 == 0:
        if first_digit == 4 and count in [13, 16]:
            print("VISA")
        elif first_digit == 5 and 1 <= second_digit <= 5 and count == 16:
            print("MASTERCARD")
        elif first_digit == 3 and second_digit in [4, 7] and count == 15:
            print("AMEX")
        else:
            print("INVALID")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
