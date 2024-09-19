def main():
    uinput = input("What is your input? ")

    myCount = count(uinput)

    lvalue = (myCount['lettercount'] / myCount['wordcount']) * 100
    svalue = (myCount['sentencecount'] / myCount['wordcount']) * 100

    index = round((0.0588 * lvalue - 0.296 * svalue - 15.8))

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def count(a):
    counts = {'lettercount': 0, 'wordcount': 1, 'sentencecount': 0}
    for i in a:
        if i.isalpha():
            counts['lettercount'] += 1
        elif i.isspace():
            counts['wordcount'] += 1
        elif i in ['.', '!', '?']:
            counts['sentencecount'] += 1
    return counts


if __name__ == "__main__":
    main()
