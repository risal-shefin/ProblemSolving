#include <bits/stdc++.h>
using namespace std;

#define ll int

char todo[18][6] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
int mat[5202][5202], n;
char inp[1500];

int check(int x)

{
    ll ni = 1, nj = 1;
    ll cnti = 0, cntj = 0;
    for(ll i = 1; i <= n; i++)
    {
        nj = 1;
        cntj = 0;

        cnti++;
        if(cnti > x)
        {
            cnti = 1;
            ni = i;
        }
        for(ll j = 1; j <= n; j++)
        {
            cntj++;
            if (cntj > x)
            {
                cntj = 1;
                nj = j;
            }

            if(mat[i][j] != mat[ni][nj])
            {
                return 0;
            }
        }
    }
    return 1;
}

int main()

{
    ll pos;
    cin >> n;
    ll rw = n / 4;
    char ch;
    for(ll i = 1; i <= n; i++) {
        scanf("%s", inp);

        for(ll j = 0; j < rw; j++) {
            pos = inp[j] - '0';
            if(inp[j] >= 'A' && inp[j] <= 'F')
                pos = inp[j] - 'A' + 10;

            for(ll k = j * 4 + 1, s = 0; s < 4; k++, s++)
                mat[i][k] = (todo[pos][s] - '0');
        }
    }

    for(ll k = n; k > 1; k--) {

        if(n % k)
            continue;

        if(check(k)) {
            printf("%d\n", k);
            return 0;
        }

    }

    printf("1\n");

    return 0;
}
