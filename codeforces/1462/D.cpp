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

const ll sz = 3009;
ll ara[sz];

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n, sum = 0; sl(n);

        for1(i, n) {
            sl(ara[i]);
            sum += ara[i];
        }

        ll ans;

        rep1(i, n) {
            if(sum % i != 0)
                continue;

            ll ok = 1, eq = sum/i;

            for1(i, n) {
                if(ara[i] > eq) {
                    ok = 0;
                    break;
                }

                ll now = 0, stop = i;
                for(ll j = i; j <= n; j++) {
                    if(now+ara[j] > eq)
                        break;

                    now += ara[j];
                    stop = j;
                }

                if(now != eq) {
                    ok = 0;
                    break;
                }

                i = stop;
            }

            if(!ok)
                continue;

            ans = n-i;
            break;
        }

        pf("%lld\n", ans);
    }

    return 0;
}
