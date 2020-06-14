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
#define inf (1LL << 62)
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
vector <int> g[sz], ans;

struct node {
    int con, u;
};
const bool operator <(const node &a, const node &b) {
    if(a.con != b.con)
        return a.con < b.con;
    return a.u < b.u;
}
set <node> lst;

ll n, m, k, vis[sz], cyc = inf, par[sz], lev[sz], cnt[sz];
pii cycle;

void cycle_dfs(ll u, ll p, ll d)
{
    if(vis[u] == 1) {
        ll len = lev[p] - lev[u] + 1;
        if(len >= 3 && len < cyc) {
            cyc = len;
            cycle = mp(p, u);
        }
        return;
    }

    lev[u] = d, par[u] = p, vis[u] = 1;
    for(int &v : g[u]) {
        if(v == p || vis[v] == 2)
            continue;

        cycle_dfs(v, u, d+1);
    }
    vis[u] = 2;
}

int main()
{
    cin >> n >> m >> k;
    for1(i, m) {
        ll u, v;
        sl(u), sl(v);

        g[u].pb(v);
        g[v].pb(u);
    }

    for1(i, n) cnt[i] = g[i].size(), lst.insert({cnt[i], i});

    while(!lst.empty() && ans.size() < (k+1)/2) {
        node now = *lst.begin();
        lst.erase(now);
        ans.pb(now.u);

        for(int &v : g[now.u]) {
            if(lst.find({cnt[v], v}) != lst.end()) lst.erase({cnt[v], v});

            for(int &w : g[v]) {
                auto it = lst.find({cnt[w], w});
                if(it == lst.end())
                    continue;

                lst.erase(it);
                lst.insert({--cnt[w], w});
            }
        }
    }

    if(ans.size() == (k+1)/2) {
        pf("1\n");
        for0(i, (ll)ans.size()) {
            if(i != 0) pf(" ");
            pf("%d", ans[i]);
        }
        pn;
        return 0;
    }

    cycle_dfs(1, -1, 0);

    pf("2\n%lld\n%lld", cyc, cycle.first);

    ll now = cycle.first;
    while(now != cycle.second) {
        now = par[now];
        pf(" %lld", now);
    }
    pn;

    return 0;
}
