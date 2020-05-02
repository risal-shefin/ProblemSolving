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
#define inf (1LL << 62)
#define loop(i, start, stop, inc) for(ll i = start; i <= stop; i += inc)
#define for1(i, stop) for(ll i = 1; i <= stop; i++)
#define for0(i, stop) for(ll i = 0; i < stop; i++)
#define rep1(i, start) for(ll i = start; i >= 1; i--)
#define rep0(i, start) for(ll i = (start-1); i >= 0; i--)
#define ms(n, i) memset(n, i, sizeof(n))
#define casep(n) printf("Case %lld:", ++n)
#define pn printf("\n")
#define pf printf
#define EL '\n'
#define fastio std::ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

const ll sz = 1e5 + 10;
vector <ll> g[sz], got[sz];

struct qnode {
    ll a, b;
} qry[sz];

ll tim, n, m, start[sz], stop[sz], ans[sz];

const ll psz = 4*sz + 2*sz*54;
int root[psz], val[psz], lazy[psz], Left[psz], Right[psz], per = 0;

void build(ll lo, ll hi, ll node)
{
    if(lo == hi) {
        val[node] = 0, lazy[node] = -1;
        return;
    }

    ll mid = lo+hi >> 1;
    Left[node] = ++per, Right[node] = ++per;

    build(lo, mid, Left[node]);
    build(mid+1, hi, Right[node]);

    val[node] = 0, lazy[node] = -1;
}

int update_prop(int l, int r, int v, int node)
{
    int nnode = ++per;
    val[nnode] = (r-l+1) * v;
    lazy[nnode] = v;
    Left[nnode] = Left[node], Right[nnode] = Right[node];

    return nnode;
}

int update(ll lo, ll hi, ll l, ll r, ll v, ll node)
{
    if(lo > r || hi < l) return node;

    int nnode = ++per;

    if(lo >= l && hi <= r) {
        val[nnode] = (hi - lo + 1) * v;
        lazy[nnode] = v;

        Left[nnode] = Left[node];
        Right[nnode] = Right[node];

        return nnode;
    }

    ll mid = lo+hi >> 1;

    lazy[nnode] = lazy[node], Left[nnode] = Left[node], Right[nnode] = Right[node];

    if(lazy[nnode] != -1) {
        Left[nnode] = update_prop(lo, mid, lazy[nnode], Left[nnode]);
        Right[nnode] = update_prop(mid+1, hi, lazy[nnode], Right[nnode]);
        lazy[nnode] = -1;
    }

    Left[nnode] = update(lo, mid, l, r, v, Left[nnode]);
    Right[nnode] = update(mid+1, hi, l, r, v, Right[nnode]);

    val[nnode] = val[ Left[nnode] ] + val[ Right[nnode] ];

    return nnode;
}

void dfs(ll u, ll p)
{
    start[u] = ++tim;
    for(ll &v : g[u]) {
        if(v == p)
            continue;
        dfs(v, u);
    }
    stop[u] = tim;
}

void ans_dfs(ll u, ll p)
{
    root[u] = root[p];
    //cout << u << endl;
    for(ll &idx : got[u]) {
        ll a = qry[idx].a, b = qry[idx].b;

        root[u] = update(1, tim, start[a], stop[a], 1, root[u]);
        root[u] = update(1, tim, start[b], stop[b], 1, root[u]);
    }
    //cout << u << "  " << 5 << " " << n << endl;

    int lastPer = per;
    ans[u] = val[ root[u] ] - 1;

    for(ll &v : g[u]) {
        if(v == p)
            continue;
        ans_dfs(v, u);
    }
    per = lastPer;
}

int main()
{
    cin >> n >> m;

    for(ll i = 1; i < n; i++) {
        ll u, v;
        si(u), si(v);

        g[u].pb(v);
        g[v].pb(u);
    }

    for1(i, m) {
        ll a, b;
        si(a), si(b);

        qry[i] = {a, b};

        got[a].pb(i), got[b].pb(i);
    }

    dfs(1, -1);

    root[0] = ++per;
    build(1, tim, root[0]);

    ans_dfs(1, 0);

    for1(i, n) {
        if(i != 1)
            pf(" ");

        pf("%d", ans[i] == -1? 0 : ans[i]);
    }
    pn;

    return 0;
}
