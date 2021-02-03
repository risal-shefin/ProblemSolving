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

const ll sz = 20;
ll fact[sz], cnt[sz], dp[sz][sz][sz], idx;

ll solve(ll pos, ll ase, ll z)
{
    if(pos == idx) {
        if(ase == 1 && z == 0)
            return 1;
        else
            return 0;
    }

    ll &ret = dp[pos][ase][z];
    if(ret != -1)
        return ret;

    ret = 0;
    if(ase > 0)
        ret += ase * solve(pos+1, ase-1 + cnt[pos], z);
    if(z > 0)
        ret += z * solve(pos+1, ase+cnt[pos], z-1);

    return ret;
}

int main()
{
    fact[0] = 1;
    for1(i, sz-1) fact[i] = fact[i-1]*i;

    ll t;
    cin >> t;
    while(t--) {
        ll n; sl(n);

        ms(cnt, 0);

        idx = 1;
        while(n) {
            ++idx;
            ll rem = n%idx;
            n /= idx;

            cnt[rem]++;
        }

        ms(dp, -1);
        ll ans = solve(2, cnt[1], cnt[0]);

        for(ll i = 0; i <= idx; i++)
            ans /= fact[ cnt[i] ];

        pf("%lld\n", ans-1);
    }

    return 0;
}
