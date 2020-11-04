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
vector <ll> g[sz];
ll sub[sz], cen1, cen2, mn, n;

void dfs(ll u, ll p)
{
    sub[u] = 1;

    for(ll &v : g[u]) {
        if(v == p)
            continue;

        dfs(v, u);
        sub[u] += sub[v];
    }
}

void cen_dfs(ll u, ll p)
{
    ll mxSub = n-sub[u];

    for(ll &v : g[u]) {
        if(v == p)
            continue;

        cen_dfs(v, u);
        mxSub = max(mxSub, sub[v]);
    }

    if(mxSub < mn) {
        cen1 = u, cen2 = -1;
        mn = mxSub;
    }
    else if(mxSub == mn)
        cen2 = u;
}

ll eu, ev;
void gen_dfs(ll u, ll p)
{
    for(ll &v : g[u]) {
        if(v == p || v == cen2)
            continue;

        if(eu != -1) return;

        gen_dfs(v, u);
    }

    if(g[u].size() == 1) eu = p, ev = u;
}

int main()
{
    ll t; sl(t);

    while(t--) {
        sl(n);

        for1(i, n-1) {
            ll u, v;
            sl(u), sl(v);

            g[u].pb(v), g[v].pb(u);
        }

        dfs(1, -1);

        cen1 = -1, cen2 = -1, mn = inf;
        cen_dfs(1, -1);

        if(cen2 == -1) {
            pf("1 %lld\n", g[1][0]);
            pf("1 %lld\n", g[1][0]);
        }
        else {
            eu = -1, ev = -1;
            gen_dfs(cen1, -1);

            pf("%lld %lld\n", eu, ev);
            pf("%lld %lld\n", cen2, ev);
        }

        for1(i, n) g[i].clear();
    }

    return 0;
}
