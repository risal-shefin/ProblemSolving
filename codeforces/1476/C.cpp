// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define dd double
#define ld long double
#define sl(n) scanf("%lld", &n)
#define si(n) scanf("%d", &n)
#define sd(n) scanf("%lf", &n)
#define pll pair <ll, ll>
#define pii pair <int, int>
#define mp make_pair
#define pb push_back
#define all(v) v.begin(), v.end()
#define inf (1LL << 61)
#define loop(i, start, stop, inc) for(ll i = start; i <= stop; i += inc)
#define for1(i, stop) for(ll i = 1; i <= stop; ++i)
#define for0(i, stop) for(ll i = 0; i < stop; ++i)
#define rep1(i, start) for(ll i = start; i >= 1; --i)
#define rep0(i, start) for(ll i = (start-1); i >= 0; --i)
#define ms(n, i) memset(n, i, sizeof(n))
#define casep(n) printf("Case %lld:", ++n)
#define pn printf("\n")
#define pf printf
#define EL '\n'
#define fastio std::ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

const ll sz = 1e5 + 10;
ll a[sz], b[sz], c[sz], en[sz];

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n; sl(n);

        for1(i, n) sl(c[i]);
        for1(i, n) sl(a[i]);
        for1(i, n) sl(b[i]);

        for1(i, n) en[i] = 0;

        for(ll i = 2; i <= n; i++) {
            if(a[i] == b[i])
                en[i-1] = 1;
        }
        en[1] = en[n] = 1;

        ll ans = 0;

        for(ll i = 1; i < n;) {

            ll stop = i, cyc = 0, prv = 0;

            for(ll j = i; j <= n; j++) {

                stop = j;

                if(j == i) {
                    cyc += abs(a[j+1] - b[j+1])+1;
                    prv = cyc;
                    continue;
                }
                cyc = max(cyc, prv);
                ans = max(ans, cyc + c[j]);

                if(en[j]) {
                    cyc += c[j];
                    break;
                }

                if(c[j] - a[j+1] <= c[j] - b[j+1]) {
                    cyc += (c[j] - a[j+1] + 1);
                    cyc += b[j+1];
                }
                else {
                    cyc += (c[j] - b[j+1] + 1);
                    cyc += a[j+1];
                }

                if(i+1 <= n)
                    prv = max(cyc, abs(a[j+1]-b[j+1])+1);
            }

            i = stop;
            ans = max(ans, cyc);
        }

        pf("%lld\n", ans);
    }

    return 0;
}

