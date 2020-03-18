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
#define fastio std::ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

const ll sz = 1e5 + 10;
ll sqt, cyc, par[sz], vis[sz], lev[sz];
vector <ll> g[sz], ans;
pll cycle;
ll ctot = 0;

void cycle_dfs(ll u, ll p, ll d)
{
    if(vis[u] == 1) {
        ll len = lev[p] - lev[u] + 1;
        if(len > cyc) {
            cyc = len;
            cycle = mp(p, u);
        }
        return;
    }

    par[u] = p, lev[u] = d, vis[u] = 1;
    for(ll v : g[u]) {
        ctot++;
        assert(ctot <= (ll)1e7);

        if(v == p || v == par[u] || vis[v] == 2)
            continue;

        cycle_dfs(v, u, d+1);
    }
    vis[u] = 2;
}

ll con[sz];
set <pll> lst;

int main()
{
    ll n, m;
    cin >> n >> m;
    for1(i, m) {
        ll u, v;
        sl(u), sl(v);

        g[u].pb(v);
        g[v].pb(u);
    }
    sqt = sqrtl(n);
    if(sqt * sqt < n) sqt++;

    cycle_dfs(1, -1, 0);

    if(cyc >= sqt) {
        pf("2\n%lld\n", cyc);
        pf("%lld", cycle.first);

        ll cur = cycle.first;
        while(cur != cycle.second) {
            ctot++;
            assert(ctot <= (ll)1e7);

            cur = par[cur];
            pf(" %lld", cur);
        }
        pn;
        return 0;
    }

    for1(i, n) {
        con[i] = g[i].size();
        lst.insert(mp(con[i], i));
    }

    ll tot = 0;
    while(ans.size() < sqt) {
        assert(lst.size() > 0);

        pll p = *lst.begin();
        lst.erase(p);
        ans.push_back(p.second);

        tot++;
        assert(tot <= (ll)3e6);

        for(ll v : g[p.second]) {
            tot++;
            assert(tot <= (ll)3e6);

            auto it = lst.find(mp(con[v], v));
            if(it == lst.end()) continue;
            lst.erase(it);

            for(ll w : g[v]) {
                tot++;
                assert(tot <= (ll)3e6);

                it = lst.find(mp(con[w], w));
                if(it == lst.end()) continue;

                lst.erase(it);
                con[w]--;
                lst.insert(mp(con[w], w));
            }
        }
    }

    pf("1\n");
    for0(i, sqt) {
        if(i != 0)
            pf(" ");
        pf("%lld", ans[i]);
    }
    pn;

    return 0;
}
