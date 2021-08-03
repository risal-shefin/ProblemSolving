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

// === DEBUG MACRO STARTS HERE === //
#ifndef ONLINE_JUDGE
#define DEBUG
#define SYS_COL system("COLOR")
#endif

int recur_depth = 0;
#ifdef DEBUG
#define dbg(x) {++recur_depth; auto x_=x; --recur_depth; SYS_COL; \
                cerr<<string(recur_depth, '\t')<<"\e[91m"<<__func__<<":" \
                <<__LINE__<<"\t"<<#x<<" = "<<x_<<"\e[39m"<<endl;}

template<typename Ostream, typename Cont>
typename enable_if<is_same<Ostream,ostream>::value,
            Ostream&>::type operator<<(Ostream& os,  const Cont& v) {
	os<<"[";
	for(auto& x:v){os<<x<<", ";}
	return os<<"]";
}
template<typename Ostream, typename ...Ts>
Ostream& operator<<(Ostream& os,  const pair<Ts...>& p){
	return os<<"{"<<p.first<<", "<<p.second<<"}";
}
#else
#define dbg(x)
#endif
// === DEBUG MACRO ENDS HERE === //

#define ff first
#define ss second

const ll sz = 1e5 + 10, mod = 1e9 + 7, LN = 18;
vector <ll> g[sz], g2[sz];
ll num[sz], vis[sz], par[sz], cyc[sz], idx = 0;
ll pre[sz], depth[sz], pa[LN][sz], two[sz];

void dfs(ll u, ll p)
{
    if(vis[u] == 1) {
        ll cur = p, now = ++idx;
        num[cur] = now, cyc[now] = 1;

        while(cur != u) {
           cur = par[cur];
           num[cur] = now;
        }
        return;
    }

    vis[u] = 1, par[u] = p;

    for(ll &v : g[u]) {
        if(vis[v] == 2 || v == p)
            continue;

        dfs(v, u);
    }

    vis[u] = 2;
}

void dfs2(ll u, ll p, ll d, ll c)
{
    pa[0][u] = p, depth[u] = d;
    pre[u] = c+cyc[u];

    for(ll &v : g2[u]) {
        if(v == p)
            continue;

        dfs2(v, u, d+1, pre[u]);
    }
}

ll LCA(ll u, ll v)
{
    if(depth[u] < depth[v]) swap(u,v);
    ll diff = depth[u] - depth[v];
    for(ll i = 0; i < LN; i++) if( (diff>>i)&1 ) u = pa[i][u];
    if(u == v) return u;
    for(ll i = LN-1; i >= 0; i--) {
        if(pa[i][u] != pa[i][v]) {
            u = pa[i][u];
            v = pa[i][v];
        }
    }
    return pa[0][u];
}

int main()
{
    two[0] = 1;
    for1(i, sz-1) two[i] = (two[i-1] * 2) % mod;

    ll n, m;
    cin >> n >> m;

    for1(i, m) {
        ll u, v;
        sl(u), sl(v);

        g[u].pb(v);
        g[v].pb(u);
    }

    dfs(1, -1);

    for1(i, n) if(num[i] == 0) num[i] = ++idx;

    for1(u, n) {
        for(ll &v : g[u])
            if(num[u] != num[v])
                g2[ num[u] ].pb(num[v]);
    }

    ms(pa, -1);
    dfs2(1, -1, 0, 0);

    for(int i=1; i<LN; i++)
        for(int j=1; j<=n; j++)
            if(pa[i-1][j] != -1)
                pa[i][j] = pa[i-1][pa[i-1][j]];


    ll q; sl(q);

    while(q--) {
        ll u, v;
        sl(u), sl(v);
        u = num[u], v = num[v];

        ll lca = LCA(u, v);
        ll pw = pre[u]+pre[v] - 2*pre[lca] + cyc[lca];

        pf("%lld\n", two[pw]);
    }

    return 0;
}
