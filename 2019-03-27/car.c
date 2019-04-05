#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void unique_marka();
void make_add();

int main() {
    unique_marka();
    make_add();

    return 0;
}

void unique_marka() {
    FILE *fp;

    if ((fp = fopen("FILE1.bin", "rb")) == NULL) {
        printf("Cannot openfile. \n");
        return;
    }

    FILE *fp2;

    if ((fp2 = fopen("Marka.bin", "wb")) == NULL) {
        printf("Cannot openfile. \n");
        fclose(fp);
        return;
    }

    int ID, len;
    char Marka[20], address[20];
    double price;

    while (1) {
        if (fread(&ID, sizeof(int), 1, fp) != 1) {
            printf("Write error occured. \n");
            break;
        }

        len = strlen(Marka);
        if (fread(&len, sizeof(int), 1, fp) != 1) {
            printf("Write error occured. \n");
            break;
        }
        if (fread(Marka, sizeof(char), len, fp) != len) {
            printf("Write error occured. \n");
            break;
        }
        Marka[len] = '\0';

        if (fread(&price, sizeof(double), 1, fp) != 1) {
            printf("Write error occured. \n");
            break;
        }

        len = strlen(address);
        if (fread(&len, sizeof(int), 1, fp) != 1) {
            printf("Write error occured. \n");
            break;
        }
        if (fread(address, sizeof(char), len, fp) != len) {
            printf("Write error occured. \n");
            break;
        }
        address[len] = '\0';

        int fl = 0;
        if (!((fp2 = fopen("Marka.bin", "rb")) == NULL)) {
            fl = 0;
            while (1) {
                char Marka_check[20];

                if (fread(&len, sizeof(int), 1, fp) != 1) {
                    printf("Write error occured. \n");
                    break;
                }
                if (fread(Marka_check, sizeof(char), len, fp) != len) {
                    printf("Write error occured. \n");
                    break;
                }
                Marka_check[len] = '\0';

                if (strcmp(Marka, Marka_check) == 0) {
                    fl = 1;
                    break;
                }
            }
            fclose(fp2);
        }

        if (fl == 0) {
            if ((fp2 = fopen("Marka.bin", "ab")) == NULL) {
                printf("Cannot openfile. \n");
                return;
            }

            len = strlen(Marka);
            if (fwrite(&len, sizeof(int), 1, fp2) != 1) {
                printf("Len Write error occured. \n");
            }
            if (fwrite(Marka, sizeof(char), len, fp2) != len) {
                printf("Marka Write error occured. \n");
            }

            fclose(fp2);
        }
    }

    fclose(fp);
}

void make_add() {
    FILE *fp;

    if ((fp = fopen("FILE1.bin", "rb")) == NULL) {
        printf("Cannot openfile. \n");
        return;
    }

    int ID, len;
    char Marka[20], address[20];
    double price;
    double avg = 0, counter = 0;

    while (1) {
        if (fread(&ID, sizeof(int), 1, fp) != 1) {
            printf("Write error occured. \n");
            break;
        }

        len = strlen(Marka);
        if (fread(&len, sizeof(int), 1, fp) != 1) {
            printf("Write error occured. \n");
            break;
        }
        if (fread(Marka, sizeof(char), len, fp) != len) {
            printf("Write error occured. \n");
            break;
        }
        Marka[len] = '\0';

        if (fread(&price, sizeof(double), 1, fp) != 1) {
            printf("Write error occured. \n");
            break;
        }

        len = strlen(address);
        if (fread(&len, sizeof(int), 1, fp) != 1) {
            printf("Write error occured. \n");
            break;
        }
        if (fread(address, sizeof(char), len, fp) != len) {
            printf("Write error occured. \n");
            break;
        }
        address[len] = '\0';

        avg = avg + price;
        counter = counter + 1;
    }

    fclose(fp);

    if (avg != 0 && counter != 0) {
        avg = avg / counter;
    } else {
        return;
    }

    if ((fp = fopen("FILE1.bin", "rb")) == NULL) {
        printf("Cannot openfile. \n");
        return;
    }

    FILE *fp2;

    if ((fp2 = fopen("Address.bin", "wb")) == NULL) {
        printf("Cannot openfile. \n");
        fclose(fp);
        return;
    }

    while (1) {
        if (fread(&ID, sizeof(int), 1, fp) != 1) {
            printf("Write error occured. \n");
            break;
        }

        len = strlen(Marka);
        if (fread(&len, sizeof(int), 1, fp) != 1) {
            printf("Write error occured. \n");
            break;
        }
        if (fread(Marka, sizeof(char), len, fp) != len) {
            printf("Write error occured. \n");
            break;
        }
        Marka[len] = '\0';

        if (fread(&price, sizeof(double), 1, fp) != 1) {
            printf("Write error occured. \n");
            break;
        }

        len = strlen(address);
        if (fread(&len, sizeof(int), 1, fp) != 1) {
            printf("Write error occured. \n");
            break;
        }
        if (fread(address, sizeof(char), len, fp) != len) {
            printf("Write error occured. \n");
            break;
        }
        address[len] = '\0';

        if (price > avg) {
            len = strlen(address);
            if (fwrite(&len, sizeof(int), 1, fp2) != 1) {
                printf("Write error occured. \n");
                exit(1);
            }
            if (fwrite(address, sizeof(char), len, fp2) != len) {
                printf("Write error occured. \n");
                exit(1);
            }
        }
    }

    fclose(fp);
    fclose(fp2);
}

