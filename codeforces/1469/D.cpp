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
ll ara[sz];

int main()
{
    ll t;
    cin >> t;

    while(t--) {

        ll n; sl(n);

        vector <pii> ans;

        ll sqt1 = sqrtl(n) + 1;
        ll sqt2 = sqrtl(sqt1) + 1;

        for(ll i = 3; i < n; i++) {
            if(i == sqt1 || i == sqt2)
                continue;

            ans.pb(mp(i, n));
        }

        ans.pb(mp(n, sqt1)), ans.pb(mp(n, sqt1));

        if(sqt1 > 2)
            ans.pb(mp(sqt1, sqt2)), ans.pb(mp(sqt1, sqt2));

        if(sqt2 > 2) {
            ll tmp = sqt2;

            while(sqt2 > 1) {
                ans.pb(mp(tmp, 2));
                sqt2 = sqt2 / 2 + (sqt2 & 1);
            }
        }

        pf("%lld\n", (ll)ans.size());
        for(pii &p : ans)
            pf("%d %d\n", p.first, p.second);
    }

    return 0;
}
