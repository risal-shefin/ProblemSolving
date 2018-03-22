#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main()

{
    bool check = 0;
    int n, mx, ans;
    cin >> n;
    char s[120];
    scanf(" %s", s + 1);
    for(int i = n / 2; i >= 1; i--) {
        int k = 2 * i;
        check = 1;
        for(int j = 0; j < i; j++) {
            if(s[i - j] != s[k - j]) {
                check = 0;
                break;
            }
        }

        if(check == 1) {
            mx = i;
            break;
        }
    }

    if(check) {
       ans = n - mx + 1;
    }
    else
        ans = n;
    cout << ans << endl;

    return 0;
}
