#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int num;
    char* name;
};

void write_student(struct student*);
void read_student();

int main() {
    struct student *st = (struct student*)malloc(sizeof(struct student) * 2);

    int num;

    int el = 0;
    printf("Num: ");
    while (scanf("%d", &num) != EOF) {
        char* name = (char*)malloc(sizeof(char) * 50);
        if (name == NULL) {
            perror("malloc");
            free(st);
            return -1;
        }
        printf("Name: ");
        scanf("%s", name);
        (st + 0)->num = 22;
        (st + 0)->name = (char*)malloc(sizeof(char) * strlen(name));
        if ((st + 0)->name == NULL) {
            perror("malloc");
            free(st);
            free(name);
            return -1;
        }
        strcpy((st + 0)->name, name);
        free(name);
        el++;
        printf("Num: ");
    }

    write_student(st);

    free((st + 0)->name);
    free((st + 1)->name);
    free(st);

    read_student();

    return 0;
}

void write_student(struct student *st) {
    FILE *fp = NULL;

    if ((fp = fopen("student", "wb")) == NULL) {
        perror("fopen");
        return;
    }

    if (fwrite(st, sizeof(struct student), 2, fp) != 2) {
        perror("fwrite");
        fclose(fp);
        return;
    }

    fclose(fp);
}

void read_student() {
    FILE *fp = NULL;

    if ((fp = fopen("student", "rb")) == NULL) {
        perror("fopen");
        return;
    }

    struct student st;

    if (fread(&st, sizeof(struct student), 1, fp) != 1) {
        perror("fread");
        fclose(fp);
        return;
    }

    printf("\n%d %s", st.num, st.name);

    fclose(fp);
}

