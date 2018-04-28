#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main()

{

    ll n;
    cin >> n;
    for(ll i = 1; i <= n; i++) {
        ll seg = (i * (i + 1)) / 2;
        if(seg == n) {
            cout << i << endl;
            return 0;
        }
        if(seg > n) {
            ll tot = seg - n;
            cout << (i - tot) << endl;
            return 0;
        }
    }
    return 0;
}

