#include <stdio.h>

int main()

{
    int c1, c2, c3, c4, c5, sum = 0;
    scanf("%d %d %d %d %d", &c1, &c2, &c3, &c4, &c5);
    sum = c1 + c2 + c3 + c4 + c5;
    if(sum == 0) {
        printf("-1\n");
        return 0;
    }
    if((sum % 5) == 0) {
        printf("%d\n", sum / 5);
    }

    else {
        printf("-1\n");
    }

    return 0;
}