import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Missing command-line argument")
        sys.exit()
    # TODO: Read database file into a variable
    Data = []
    # open the file with python csv syntax
    with open(sys.argv[1], newline="") as csvfile:
        # read the file with python csv syntax in memorry with Database name
        Database = csv.reader(csvfile, delimiter=" ", quotechar="|")
        # Copy the Database memory in a list
        for row in Database:
            Data += row
    # split the list first entry, that is the name of the variables in different items at every ,
    dict_bases = Data[0].split(',')
    dict_entry = []
    dict_names = []
    for i in range(1, len(Data)):
        # split the list first entry, that is the value of the variables in different items at every ,
        dict_entry += [Data[i].split(',')]

    for i in range(0, len(dict_entry)):
        # create a list of names
        dict_names.append(dict_entry[i][0])
        # remove names from previous variable list
        dict_entry[i].pop(0)

    for i in range(0, len(dict_entry)):
        for j in range(0, len(dict_entry[i])):
            # turn string that contain digits in integers
            if (dict_entry[i][j].isdigit()):
                dict_entry[i][j] = int(dict_entry[i][j])

    # TODO: Read DNA sequence file into a variable

    Sequence = ""
    ADN = []
    ADN_LIST = []
    # same as above
    with open(sys.argv[2], newline="") as csvfile:
        sequence = csv.reader(csvfile, delimiter=" ", quotechar="|")
        for row in sequence:
            ADN += row
            ADN_LIST += [ADN[0]]

    for i in ADN_LIST[0]:
        Sequence += i

    # TODO: Find longest match of each STR in DNA sequence
    subsequence = []
    check = []
    # create a list with the ADN subsequences to look for
    for i in range(1, len(dict_bases)):
        subsequence.append(dict_bases[i])

    for i in range(0, len(subsequence)):
        # search in the DNA sequence
        check.append(longest_match(Sequence, subsequence[i]))

    # TODO: Check database for matching profiles

    for i in range(0, len(dict_names)):
        for j in range(0, len(check)):
            # if the sequences from database corespond to the matched sequences print the name
            if (dict_entry[i] == check):
                print(dict_names[i])
                return
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
