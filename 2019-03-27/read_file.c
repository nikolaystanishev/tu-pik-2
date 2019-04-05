#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;

    if ((fp = fopen("FILE1.bin", "rb")) == NULL) {
        printf("Cannot openfile. \n");
        exit(1);
    }

    int ID, len;
    char Marka[20], address[20];
    double price;

    while (1) {
        if (fread(&ID, sizeof(int), 1, fp) != 1) {
            printf("Write error occured. \n");
            exit(1);
        }

        len = strlen(Marka);
        if (fread(&len, sizeof(int), 1, fp) != 1) {
            printf("Write error occured. \n");
            exit(1);
        }
        if (fread(Marka, sizeof(char), len, fp) != len) {
            printf("Write error occured. \n");
            exit(1);
        }
        Marka[len] = '\0';

        if (fread(&price, sizeof(double), 1, fp) != 1) {
            printf("Write error occured. \n");
            exit(1);
        }

        len = strlen(address);
        if (fread(&len, sizeof(int), 1, fp) != 1) {
            printf("Write error occured. \n");
            exit(1);
        }
        if (fread(address, sizeof(char), len, fp) != len) {
            printf("Write error occured. \n");
            exit(1);
        }
        address[len] = '\0';


        printf("%d %s %lf %s\n", ID, Marka, price, address);
    }

    fclose(fp);

    return 0;
}
