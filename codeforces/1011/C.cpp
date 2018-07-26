#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define eps 1e-6
ll a[1009], b[1009];

int main()

{
    //std::ios_base::sync_with_stdio(false);
    ll n;
    double tot, m;
    cin >> n >> m;
    for(ll i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    for(ll i = 1; i <= n; i++)
        scanf("%lld", &b[i]);

    bool found = 0;

    double lo = 0, hi = 1000000009, ans = -1;
    ll cnt = 1;
    while(cnt <= 100) {
        double mid = (lo + hi) / 2.0;

        tot = m + mid;

        for(ll i = 1, j = 2; i <= n; i++, j++) {
            if(i == n)
                j = 1;
            tot -= (tot / a[i]);
            if(tot < m)
                break;
            tot -= (tot / b[j]);
            if(tot < m)
                break;
        }

        if(tot < m) {
            lo = mid - 0.0000001;
        }
        else {
            found = 1;
            ans = mid;
            hi = mid + 0.0000001;
        }

        cnt++;
    }

    if(!found)
        cout << -1 << endl;
    else
        printf("%0.7f\n", ans);

    return 0;
}

