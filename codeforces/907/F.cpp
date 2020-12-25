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
ll n, m, ara[sz];
vector <ll> pmod;

inline f(ll x, ll mod)
{
    if(x < mod)
        return x;
    else
        return x%mod + mod;
}

ll fastPow(ll x, ll n, ll MOD)
{
    ll ret = 1;
    while (n)
    {
        if (n & 1) ret = f(ret*x, MOD);
        x = f(x*x, MOD);
        n >>= 1;
    }
    return ret;
}

ll phi(ll n)
{
    ll res = n;

    // this loop runs sqrt(n / ln(n)) times
    for (ll i=2; i*i <= n; i++)
    {
        if (n % i == 0)
        {
            // subtract multiples of i from r
            res -= (res / i);

            // Remove all occurrences of i in n
            while (n % i== 0)
               n /= i;
        }
    }

    // when n has prime factor greater
    // than sqrt(n)
    if (n > 1)
       res -= (res / n);

    return res;
}

ll solve(ll idx, ll r, ll idm)
{
    if(pmod[idm] == 1 || idx > r)
        return 1;

    return fastPow(ara[idx], solve(idx+1, r, idm+1), pmod[idm]);
}

int main()
{
    cin >> n >> m;
    for1(i, n)
        sl(ara[i]);

    ll tm = m;
    pmod.pb(tm);
    while(tm != 1) {
        tm = phi(tm);
        pmod.pb(tm);
    }

    ll q;
    cin >> q;

    while(q--) {
        ll l, r;
        sl(l), sl(r);

        pf("%lld\n", solve(l, r, 0)%m);
    }

    return 0;
}
