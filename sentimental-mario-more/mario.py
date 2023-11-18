# TODO

while True:
    try:
        n = int(input('Size: '))
        if ((n > 0) and (n < 9)):
            break

    except ValueError:
        print('Please enter an integer.')


if (True):
    # //i trece prin coloane
    for i in range(n):
        # j trece prin randuri
        # trebuie sa printez n-i randuri cu ' ' si i cu '#'
        for j in range(n * 2 + 2):
            # if(j>n-i-1) conditie partea dreapta
            # if(j<n-i-1) conditie zerouri stanga
            if (j < n - i - 1):
                print(" ", end='')
            elif (j == n):
                print(" ", end='')
            elif (j == n + 1):
                print(" ", end='')
            elif (j < n + i + 3):
                print("#", end='')
        print("")