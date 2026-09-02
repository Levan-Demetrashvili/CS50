import re


def main():
    while True:
        try:
            card_number = int(input('Number: '))
            if type(card_number) is int:
                break
        except ValueError:
            print(end='')
    pattern = r'^[345]([0-9]{12}|[0-9]{14}|[0-9]{15})$'
    formatted_number = str(card_number)
    digits = list(map(int, list(formatted_number)))
    sum_of_odds = 0
    sum_of_products = 0
    length = len(formatted_number)

    if not re.match(pattern, formatted_number):
        print("INVALID")
        return 1

    for i in range(len(digits) - 1, -1, -2):
        sum_of_odds += digits[i]
        if i - 1 < 0:
            break
        digits[i - 1] *= 2

        sum_of_products += digits[i - 1] // 10 + \
            digits[i - 1] % 10 if digits[i - 1] > 9 else digits[i - 1]

    index = int(formatted_number[:2])

    if ((sum_of_odds + sum_of_products) % 10 == 0):
        if length == 15 and (index == 34 or index == 37):
            print("AMEX")
            return 0

        elif length == 16 and (index >= 50 and index <= 55):
            print("MASTERCARD")
            return 0

        elif (length == 13 or length == 16) and index // 10 == 4:
            print("VISA")
            return 0

        else:
            print("INVALID")
            return 1

    else:
        print("INVALID")
        return 1


if __name__ == '__main__':
    main()
