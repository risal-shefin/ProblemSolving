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

const ll sz = 2e5 + 10, mod = 2e9 + 63, base = 1e9 + 21;
vector <pll> g[sz];
ll pw[sz], n, m, k, vis[sz], hash_val[10][10], mat;

void dfs(ll u)
{
    vis[u] = 1;
    sort(all(g[u]));

    ll siz = g[u].size();
    for(ll i = 0; i < siz; i++) {
        pll edge = g[u][i];
        ll nxt = edge.second;

        hash_val[siz][i+1] = (hash_val[siz][i+1] + pw[nxt]) % mod;

        if(!vis[nxt])
            dfs(nxt);
    }
}

ll solve(ll pos, ll hsh)
{
    if(pos > k)
        return hsh == mat;

    ll ret = 0;
    for1(i, pos) {
        ll now = (hsh + hash_val[pos][i]) % mod;
        ret += solve(pos+1, now);
    }

    return ret;
}

int main()
{
    pw[0] = 1;
    for1(i, sz-1) pw[i] = (pw[i-1] * base) % mod;

    cin >> n >> m >> k;
    for1(i, m) {
        ll u, v, w;
        sl(u), sl(v), sl(w);

        g[u].pb(mp(w, v));
    }

    for1(i, n) {
        if(!vis[i])
            dfs(i);
    }

    for1(i, n) mat = (mat + pw[i]) % mod;

    cout << solve(1, 0) << EL;

    return 0;
}
