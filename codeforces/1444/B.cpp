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
ll fact[sz], inv[sz], ara[sz];

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

inline ll nCr(ll n, ll r) {
    ll den = (inv[r] * inv[n-r]) % mod;
    return (fact[n] * den) % mod;
}

int main()
{
    fact[0] = 1;
    for1(i, sz-1) fact[i] = (fact[i-1]*i) % mod;

    inv[sz-1] = fastPow(fact[sz-1], mod-2, mod);
    rep0(i, sz-1) inv[i] = (inv[i+1] * (i+1)) % mod;

    ll n; sl(n);
    ll way = nCr(2*n-1, n-1), ans = 0;

    for1(i, 2*n) sl(ara[i]);

    sort(ara+1, ara+2*n+1);

    for1(i, n) {
        ans -= (way * ara[i]) % mod;
        if(ans < 0) ans += mod;
    }

    for(ll i = n+1; i <= 2*n; i++) {
        ans += (way * ara[i]) % mod;
        if(ans >= mod) ans -= mod;
    }

    cout << (2*ans)%mod << EL;

    return 0;
}
