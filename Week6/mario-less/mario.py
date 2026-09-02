def main():

    while True:
        try:
            height = int(input('Height: '))
            if height >= 1 and height <= 8:
                break
        except ValueError:
            print(end="")

    for row in range(height):
        print(" " * (height - 1 - row), end='')
        print("#" * (row + 1))


if __name__ == '__main__':
    main()
