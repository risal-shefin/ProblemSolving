#include <stdio.h>

int main()

{
    long long int n, m , a, row, col;

    scanf("%lld %lld %lld", &n, &m, &a);

    if(n % a == 0) {
       col  = n / a;
    }
    else {
       col = n / a + 1;
    }

    if(m % a == 0) {
        row = m / a;
    }
    else {
        row = m / a + 1;
    }

    printf("%lld\n", row * col);
    return 0;
}

