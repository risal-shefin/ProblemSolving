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

const ll sz = 20, lim = 1<<19;
vector <ll> g[sz];
ll dp[lim][sz];

ll solve(ll u, ll got, ll s)
{
    if(got == 0)
        return 1;

    ll &ret = dp[got][u];
    if(ret != -1)
        return ret;

    ret = 0;

    for(ll &v : g[u]) {
        bool state = (got >> v) & 1;
        if(!state)
            continue;

        ll nmsk = got^(1<<v);

        if(v == s && nmsk != 0)
            continue;

        ret += solve(v, nmsk, s);
    }

    return ret;
}

int main()
{
    ll n, m;
    cin >> n >> m;

    ms(dp, -1);

    for1(i, m) {
        ll u, v;
        sl(u), sl(v);

        u--, v--;

        g[u].pb(v);
        g[v].pb(u);

        dp[(1<<u)][v] = 1;
        dp[(1<<v)][u] = 1;
    }

    ll tot = 1<<n;

    ll ans = 0;

    for1(msk, tot-1) {

        ll cnt = __builtin_popcount(msk);
        if(cnt <= 2)
            continue;

        ll src;
        for0(j, n) {
            if((msk>>j) & 1) {
                src = j;
                break;
            }
        }

        ll ret = solve(src, msk, src);
        ans += ret;
    }

    cout << ans/2 << EL;

    return 0;
}