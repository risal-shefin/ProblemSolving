// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
using namespace std;

#define ll int
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
#define pn printf("\n")
#define pf printf
#define EL '\n'
#define fastio std::ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

const ll sz = 85;
ll onePos[sz], ara[sz], idx, one, zero, n;
ll dp[sz][sz][3165];

ll solve(ll o, ll z, ll rem)
{
    if(o+z == n || o == one)
        return 0;

    ll &ret = dp[o][z][rem];
    if(ret != -1)
        return ret;

    ll taken = o+z, restz = zero-z, oneIdx = o+1;
   
    for(ll i = 0; i <= restz; i++) {
        ll pos = taken + i + 1, swp = abs(pos - onePos[oneIdx]);
        if(swp > rem)
            continue;

        ret = max(ret, i*(restz-i) + solve(o+1, z+i, rem-swp));
    }

    return ret;
}

int main()
{
    si(n);

    for1(i, n) {
        si(ara[i]);
        if(ara[i] == 1) onePos[++idx] = i, one++;
        else zero++;
    }

    ms(dp, -1);

    ll tot = n*(n-1) / 2;

    for(ll i = 0; i <= tot; i++) {
        ll got = solve(0, 0, i);
        pf("%d ", got);
    }
    pn;

    return 0;
}