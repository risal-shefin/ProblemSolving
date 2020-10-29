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
#define pn printf("\n")
#define pf printf
#define EL '\n'
#define fastio std::ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

const ll sz = 2e5+10, esz = 3e5+10, qsz = 5e5+10;
int p[sz], erased[esz], par[sz], siz[sz];

struct info {
    ll a, b;
} edge[esz], qry[qsz];

struct rollback {
    int par, node, siz;
} chng[qsz];

ll findp(ll u)
{
    if(par[u] == u)
        return u;
    return findp(par[u]);
}

vector <int> lst[sz];

const bool cmp(int &a, int &b) {
    return p[a] < p[b];
}

void dsu_uni(int u, int v, int id=0)
{
    int pu = findp(u), pv = findp(v);

    if(pu == pv)
        return;

    if(siz[pu] < siz[pv]) swap(pu, pv);

    if(id != 0)
        chng[id] = {pu, pv, siz[pu]};

    par[pv] = pu;
    lst[pu].insert(lst[pu].end(), all(lst[pv]));
    siz[pu] += siz[pv];
}

int main()
{
    ll n, m, q;
    cin >> n >> m >> q;

    for1(i, n) si(p[i]);

    for1(i, m) sl(edge[i].a), sl(edge[i].b);

    for1(i, q) {
        sl(qry[i].a), sl(qry[i].b);

        if(qry[i].a == 2)
            erased[ qry[i].b ] = 1;
    }

    for1(i, n) par[i] = i, siz[i] = 1, lst[i].pb(i);

    for1(i, m) {
        if(erased[i])
            continue;

        dsu_uni(edge[i].a, edge[i].b);
    }

    rep1(i, q) {
        if(qry[i].a == 1)
            continue;

        ll id = qry[i].b;
        dsu_uni(edge[id].a, edge[id].b, i);
    }

    for1(i, n) sort(all(lst[i]), cmp);

    for1(i, q) {

        if(qry[i].a == 1) {

            ll pu = findp(qry[i].b);

            while(!lst[pu].empty()) {

                ll now = lst[pu].back(), pnow = findp(now);

                if(pnow != pu || p[now] == 0) {
                    lst[pu].pop_back();
                    continue;
                }
                break;
            }

            ll ans = 0;
            if(!lst[pu].empty()) ans = p[lst[pu].back()], p[ lst[pu].back() ] = 0;

            pf("%lld\n", ans);
        }
        else {
            par[ chng[i].node ] = chng[i].node;
            siz[ chng[i].par ] = chng[i].siz;
        }
    }

    return 0;
}

