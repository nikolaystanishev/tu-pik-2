#include <stdio.h>

int main() {
    printf("Hello world!\n");
    printf("\a\a\a\a\a\a");

    int b = 5;
    printf("%d %d %d %d\n", b++, b++, ++b, b++);

    int a;
    scanf("%d", &a);
    printf("%d %d %d %d\n", a++, a++, ++a, a++);
    return 0;
}
