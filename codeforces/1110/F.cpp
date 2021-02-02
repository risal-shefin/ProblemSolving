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

ll ans[sz], tr[4*sz], lazy[4*sz], start[sz], stop[sz], n, q, id;

struct Qry {
    int l, r, id;
};
vector <Qry> qry[sz];

struct node {
    int v, c;
    const bool operator<(const node &b) {
        return v < b.v;
    }
};
vector <node> g[sz];

void prop(ll lo, ll hi, ll node)
{
    ll mid = lo+hi >> 1, lft=node<<1, rgt=lft|1;

    tr[lft] += lazy[node], tr[rgt] += lazy[node];
    lazy[lft] += lazy[node], lazy[rgt] += lazy[node];

    lazy[node] = 0;
}

void upd(ll lo, ll hi, ll l, ll r, ll v, bool w, ll node)
{
    if(lo > r || hi < l)
        return;
    if(lo >= l && hi <= r) {

        if(w) tr[node] = v;
        else tr[node] += v;

        lazy[node] += v;
        return;
    }

    if(lazy[node]) prop(lo, hi, node);

    ll mid = lo+hi >> 1, lft=node<<1, rgt=lft|1;

    upd(lo, mid, l, r, v, w, lft);
    upd(mid+1, hi, l, r, v, w, rgt);

    tr[node] = min(tr[lft], tr[rgt]);
}

ll query(ll lo, ll hi, ll l, ll r, ll node)
{
    if(lo > r || hi < l)
        return inf;
    if(lo >= l && hi <= r)
        return tr[node];

    if(lazy[node]) prop(lo, hi, node);

    ll mid = lo+hi >> 1, lft=node<<1, rgt=lft|1;

    return min(query(lo, mid, l, r, lft),
               query(mid+1, hi, l, r, rgt));
}

void dfs(ll u, ll p, ll c)
{
    start[u] = ++id;

    if(g[u].size() == 1) upd(1, n, start[u], start[u], c, 1, 1);

    for(node &e : g[u]) {
        if(e.v == p)
            continue;

        dfs(e.v, u, c+(ll)e.c);
    }

    stop[u] = id;
}

void reroot(ll root, ll c)
{
    upd(1, n, 1, n, c, 0, 1);
    upd(1, n, start[root], stop[root], -2*c, 0, 1);
}

void solve_dfs(ll u, ll p)
{
    for(Qry &qr : qry[u])
        ans[qr.id] = query(1, n, qr.l, qr.r, 1);

    for(node &e : g[u]) {
        if(e.v == p)
            continue;

        reroot(e.v, e.c);

        solve_dfs(e.v, u);

        reroot(e.v, -e.c);
    }
}

int main()
{
    cin >> n >> q;

    for1(i, n-1) {
        ll u, c;
        sl(u), sl(c);

        g[u].pb({i+1, c});
        g[i+1].pb({u, c});
    }

    for1(i, n) sort(all(g[i]));

    for1(i, 4*n) tr[i] = inf;

    dfs(1, -1, 0);

    for1(i, q) {
        ll v, l, r;
        sl(v), sl(l), sl(r);

        qry[v].pb({l, r, i});
    }

    solve_dfs(1, -1);

    for1(i, q)
        pf("%lld\n", ans[i]);

    return 0;
}
