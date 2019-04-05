#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;

    if ((fp = fopen("FILE1.bin", "ab")) == NULL) {
        printf("Cannot openfile. \n");
        exit(1);
    }

    int ID, len;
    char Marka[20], address[20];
    double price;

    scanf("%d", &ID);
    scanf("%s", Marka);
    scanf("%lf", &price);
    scanf("%s", address);

    if (fwrite(&ID, sizeof(int), 1, fp) != 1) {
        printf("Write error occured. \n");
        exit(1);
    }

    len = strlen(Marka);
    if (fwrite(&len, sizeof(int), 1, fp) != 1) {
        printf("Write error occured. \n");
        exit(1);
    }
    if (fwrite(Marka, sizeof(char), len, fp) != len) {
        printf("Write error occured. \n");
        exit(1);
    }

    if (fwrite(&price, sizeof(double), 1, fp) != 1) {
        printf("Write error occured. \n");
        exit(1);
    }

    len = strlen(address);
    if (fwrite(&len, sizeof(int), 1, fp) != 1) {
        printf("Write error occured. \n");
        exit(1);
    }
    if (fwrite(address, sizeof(char), len, fp) != len) {
        printf("Write error occured. \n");
        exit(1);
    }

    fclose(fp);

    return 0;
}
