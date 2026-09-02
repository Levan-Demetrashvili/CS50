def main():
    text = input('Text: ')

    if len(text) == 0:
        return 1
    letters = words = sentences = 0
    for char in text:
        if char.isalpha():
            letters += 1
        elif char.isspace():
            words += 1
        elif char in ['.', '?', '!']:
            sentences += 1
    words += 1

    L = letters / words * 100
    S = sentences / words * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)
    if index >= 16:
        print('Grade 16+')
    elif index < 1:
        print('Before Grade 1')
    else:
        print(f"Grade {index}")


if __name__ == '__main__':
    main()
