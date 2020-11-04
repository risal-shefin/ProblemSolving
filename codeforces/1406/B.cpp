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

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n; sl(n);

        vector <int> pos, neg;

        for1(i, n) {
            ll x; sl(x);

            if(x >= 0) pos.pb(x);
            else neg.pb(-x);
        }

        sort(all(pos)), sort(all(neg));

        ll ans = -inf;

        for(ll i = 0; i <= 5; i++) {
            if(i > neg.size()) break;

            ll rest = 5-i;
            if(rest > pos.size())
                continue;

            ll mul = 1;
            if(i & 1) {
                for(ll j = 0; j < i; j++) mul *= -neg[j];
                for(ll j = 0; j < rest; j++) mul *= pos[j];
            }
            else {
                for(ll j = (ll)neg.size()-1, k = 1; k <= i; k++, j--) mul *= -neg[j];
                for(ll j = (ll)pos.size()-1, k = 1; k <= rest; k++, j--) mul *= pos[j];
            }

            ans = max(ans, mul);
        }

        pf("%lld\n", ans);
    }

    return 0;
}
