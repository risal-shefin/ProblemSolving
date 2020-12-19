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

struct info {
    ll v, w;
};
vector <info> g[sz];
bool vis[sz];
ll val[sz], n, m;

void dfs(ll u)
{
    vis[u] = 1;
    if(val[u] == 0) val[u] = 1;

    ll other = n;
    if(val[u] == n) other = 1;

    for(info &e : g[u]) {
        if(vis[e.v])
            continue;

        if(val[u] == e.w)
            val[e.v] = other;
        else
            val[e.v] = e.w;

        dfs(e.v);
    }
}

int main()
{
    sl(n), sl(m);

    for1(i, m) {
        ll u, v, w;
        sl(u), sl(v), sl(w);

        g[u].pb({v, w});
        g[v].pb({u, w});
    }

    dfs(1);

    for1(i, n)
        pf("%lld\n", val[i]);

    return 0;
}