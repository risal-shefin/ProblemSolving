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

const ll sz = 3e5 + 10, mod = 998244353;

pii ara[sz];
vector <pii> pnt[2*sz];
vector <int> num;
set <int> lst;

ll fact[sz], inv[sz];

ll fastPow(ll x, ll n, ll MOD)
{
    ll ret = 1;
    while (n)
    {
        if (n & 1) ret = (ret * x) % MOD;
        x = (x * x) % MOD;
        n >>= 1;
    }
    return ret % MOD;
}

inline ll nCr(ll n, ll r)
{
    ll den = (inv[r] * inv[n-r]) % mod;
    return (fact[n] * den) % mod;
}

int main()
{
    fact[0] = 1;
    for1(i, sz-1) fact[i] = (fact[i-1] * i) % mod;

    inv[sz-1] = fastPow(fact[sz-1], mod-2, mod);
    rep0(i, sz-1) inv[i] = (inv[i+1] * (i+1)) % mod;

    ll n, k;
    cin >> n >> k;

    for1(i, n) {
        si(ara[i].first), si(ara[i].second);
        num.pb(ara[i].first), num.pb(ara[i].second);
    }

    sort(all(num));
    num.erase(unique(all(num)), num.end());

    for1(i, n) {
        ll l = lower_bound(all(num), ara[i].first) - num.begin();
        ll r = lower_bound(all(num), ara[i].second) - num.begin();

        pnt[l].pb(mp(i, 0));
        pnt[r].pb(mp(i, 1));
    }

    ll ans = 0;

    for(ll i = 0; i < num.size(); i++) {

        for(pii &info : pnt[i]) {

            if(info.second == 1)
                continue;

            lst.insert(info.first);

            if(lst.size() >= k) {
                ans += nCr(lst.size()-1, k-1);
                if(ans >= mod) ans -= mod;
            }
        }

        for(pii &info : pnt[i]) {

            if(info.second == 0)
                continue;

            lst.erase(info.first);
        }
    }

    cout << ans << EL;

    return 0;
}
