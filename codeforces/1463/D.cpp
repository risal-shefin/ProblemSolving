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

const ll sz = 2e5 + 10;
ll ara[sz], ara2[sz], vis[2*sz], large[sz], chk[sz];

int main()
{
    ll t;
    cin >> t;

    while(t--) {

        ll n;
        sl(n);

        for1(i, n) {
            sl(ara[i]);
            vis[ ara[i] ] = 1;
        }

        ll idx = 0;
        for1(i, 2*n) {
            if(!vis[i])
                ara2[++idx] = i;

            vis[i] = 0;
        }

        rep1(i, n) {
            ll pos = lower_bound(ara2+1, ara2+n+1, ara[i]) - ara2;
            pos--;

            large[i] = pos, chk[i] = pos-i;

            if(i != n) chk[i] = min(chk[i], chk[i+1]);
        }

        ll ans = 0, mn = inf;

        for(ll x = 0; x <= n; x++) {

            if(x == 0) {
                if(chk[x+1] >= 0)
                    ans++;
                continue;
            }

            ll pos = upper_bound(ara2+1, ara2+n+1, ara[x]) - ara2;
            pos = n-pos+1;
            mn = min(mn, pos+x);

            if(mn < x+1)
                break;

            if(x == n)
                ans++;
            else if(chk[x+1] >= 1-(x+1))
                ans++;
        }

        pf("%lld\n", ans);
    }

    return 0;
}
