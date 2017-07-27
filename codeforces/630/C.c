#include <stdio.h>

int main()

{
    long long int count = 0, power = 1;
    int n, i;
    scanf("%d", &n);
    for(i = 1; i <= n; i++) {
        power *= 2;
        count += power;
    }

    printf("%lld\n", count);
    return 0;
}
