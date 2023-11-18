def main():
    card_number = int(input("Number: "))
    if (len(str(card_number)) in [13, 15, 16]):
        n = 0
        even = 0
        odd = 0
        num = card_number

        while (num != 0):
            # i saved the the last digit of number
            save = num % 10
            n += 1
            # i deleted the last digit of number
            num = num // 10
            # i check if the digit its in the even sport
            if (n % 2 == 0):

                # if the number has double digits i sum them
                save1 = save * 2
                while (save1 > 9):

                    save1 = save1 // 10 + save1 % 10

                even += save1
            else:

                # for odd number we dont double them
                save2 = save
                odd += save2

            # sum the even and odd numbers in save
        save = even + odd

        if ((save % 10) == 0):
            # if true print the brand
            # all the if below compare the first digits of the number with the wanted values but multiplied by 10 at the power of the digit place
            if ((card_number >= 34 * pow(10, 13) and card_number < 35 * pow(10, 13)) or (card_number >= 37 * pow(10, 13)
                                                                                         and card_number < 38 * pow(10, 13))):
                return print("AMEX")
            # all the else if below compare the first digits of the number
            elif ((card_number >= 51 * pow(10, 14) and card_number < 56 * pow(10, 14))):

                return print("MASTERCARD")

            elif ((card_number >= 4 * pow(10, 12) and card_number < 5 * pow(10, 12)) or (card_number >= 4 * pow(10, 15)
                                                                                         and card_number < 5 * pow(10, 15))):

                return print("VISA")

            else:

                return print("INVALID")

        else:

            return print("INVALID")
    else:

        return print("INVALID")
        # check if lenght and sum conditions are true


main()

