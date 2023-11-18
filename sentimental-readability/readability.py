from cs50 import get_string

text = get_string("Text: ")
len = len(text)


def main():
    # string input for the text
    # get the length of the text
    # loop, while there is text
    if (count_words(text, len)):
        # calculate the %
        procent = count_words(text, len) / 100.0
        # imparte la numarul de procente
        letters = count_letters(text, len) / procent
        # imparte la procente
        sentences = count_sentences(text, len) / procent
        # the ecuation of grade equivalent
        index = 0.0588 * letters - 0.296 * sentences - 15.8
        # round only possible with math.
        grade = round(index)
        # conditions for the grade output
        if (grade > 0 and grade < 16):

            print("Grade " + str(grade))

        elif (grade > 16):

            print("Grade 16+")

        else:

            print("Before Grade 1")


# function for counting the letters


def count_letters(text, len):

    L = 0
    for i in range(len):

        # isalnum checks if the char belongs to the alphabet
        if (text[i].isalnum()):

            L += 1

    return L


# function for counting the words


def count_words(text, len):

    W = 1
    for n in range(len):
        if (ord(text[n]) == 32):

            W += 1

    return W

# function for counting the sentences


def count_sentences(text, len):

    S = 0
    for m in range(len):

        if (ord(text[m]) == 46 or ord(text[m]) == 33 or ord(text[m]) == 63):

            S += 1

    return S


main()