def main():
    while True:
        try:
            change = float(input("Change: ")) * 100
            if change > 0:
                break
        except ValueError:
            print(end='')
    (change, quarters) = calculate_coins(change, 25)
    (change, dimes) = calculate_coins(change, 10)
    (change, nickels) = calculate_coins(change, 5)
    (change, pennies) = calculate_coins(change, 1)
    print(int(quarters + dimes + nickels + pennies))


def calculate_coins(change, coin):
    return change % coin, change // coin


if __name__ == '__main__':
    main()
