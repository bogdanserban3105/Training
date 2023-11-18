#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    FILE *file = fopen(argv[1], "r");

    if (argc != 2 || !file)
    {
        return 1;
    }

    FILE *img = 0;

    BYTE buffer[512];

    int number = 0;
    //the name its 8 bytes long - 7 char and 1 0

    char name[8];

    while (fread(buffer, sizeof(BYTE), 512, file) == 512)
    {
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {

            if (img)
            {
                fclose(img);
            }

            sprintf(name, "%03i.jpg", number++);
            img = fopen(name, "w");

        }
        if (img)
        {
            fwrite(buffer, sizeof(BYTE), 512, img);
        }

    }

    fclose(img);
    fclose(file);
    return 0;
}

//buffer stocheaza cate 512 biti, mai trebuie o bucla care sa treaca din 512 in 512
// bucla sa fie while si conditia sa fie (fread(...)<512) sau ceva de genu
// doua bucle for in while
// astea inregistreaza biti in buffer
// verifica in buffer daca biti stocati contin inceputu jpegului
// daca contin sprintf pana ies din for
// for urile tre sa tina cont de trecerea prin memorie
//how to read and store 512 bytes at the time from external file in c?




