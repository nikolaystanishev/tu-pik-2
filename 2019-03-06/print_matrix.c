#include <stdio.h>

int N = 3;

void print_edjes(int matrix[N][N], int, int);

int main() {
    int n;
    scanf("%d", &n);
    N = n;

    int matrix[n][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    print_edjes(matrix, n, 0);

    return 0;
}

void print_edjes(int matrix[N][N], int n, int edje) {
    if (((edje * 2) + 1) == n) {
        printf("%d", matrix[edje][edje]);
        return;
    }
 
    for (int j = edje; j < (n - edje); j++) {
        printf("%d ", matrix[j][edje]);
    }
    for (int j = (1 + edje); j < (n - edje); j++) {
        printf("%d ", matrix[(n - 1) - edje][j]);
    }
    for (int j = ((n - 2) - edje); edje <= j; j--) {
        printf("%d ", matrix[j][(n - 1) - edje]);
    }
    for (int j = ((n - 2) - edje); edje < j; j--) {
        printf("%d ", matrix[edje][j]);
    }

    if ((edje * 2) == n) {
        return;
    }

    print_edjes(matrix, n, edje + 1);
}
