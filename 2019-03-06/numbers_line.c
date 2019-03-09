#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int numbers[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", (numbers + i));
    }

    int start_pos = 0;
    int end_pos = 0;

    int start_pos_temp = 0;
    int end_pos_temp = 0;

    for (int i = 0, j = 1; j < n; i++, j++) {
        if (numbers[i] < numbers[j]) {
            end_pos_temp++;
        } else {
            if ((end_pos_temp - start_pos_temp) > (end_pos - start_pos)) {
                start_pos = start_pos_temp;
                end_pos = end_pos_temp;
            }
            start_pos_temp = j;
            end_pos_temp = j;
        }
    }

    for (int i = start_pos; i <= end_pos; i++) {
        printf("%d ", *(numbers + i));
    }

    return 0;
}
