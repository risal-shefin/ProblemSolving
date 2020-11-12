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

const ll sz = 5e5 + 10;
vector <ll> g[sz], dep[sz];
bool vis[sz];
ll n, m, h, par[sz], gotPath;

void dfs(ll u, ll p, ll d)
{
    vis[u] = 1, par[u] = p;
    dep[d].pb(u);

    if(d == h) {
        pf("PATH\n%lld\n", d);

        ll now = u;
        while(now != -1) {
            pf("%lld ", now);
            now = par[now];
        }
        pn;
        gotPath = 1;
        return;
    }

    for(ll &v : g[u]) {
        if(vis[v])
            continue;

        dfs(v, u, d+1);

        if(gotPath)
            return;
    }
}

inline void clr()
{
    for1(i, n) g[i].clear(), dep[i].clear(), vis[i] = 0;
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        sl(n), sl(m);

        for1(i, m) {
            ll u, v;
            sl(u), sl(v);

            g[u].pb(v);
            g[v].pb(u);
        }

        h = n/2 + (n&1), gotPath = 0;
        dfs(1, -1, 1);

        if(gotPath) {
            clr();
            continue;
        }

        pf("PAIRING\n");
        ll pr = 0;
        for1(i, n) pr += dep[i].size() / 2;

        pf("%lld\n", pr);
        for1(i, n) {
            for(ll j = 0; j+1 < dep[i].size(); j += 2)
                pf("%lld %lld\n", dep[i][j], dep[i][j+1]);
        }
        clr();
    }

    return 0;
}
