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
ll d, far, b, dist;

void dfs(ll u, ll p, ll lv = 0)
{
    if(lv > d) d = lv, far = u;
    if(u == b) dist = lv;

    for(ll &v: g[u]) {
        if(v != p)
            dfs(v, u, lv+1);
    }
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n, a, da, db;
        sl(n), sl(a), sl(b), sl(da), sl(db);

        for1(i, n-1) {
            ll u, v;
            sl(u), sl(v);

            g[u].pb(v);
            g[v].pb(u);
        }

        d = 0;
        dfs(a, -1);
        ll dis = dist;

        dfs(far, -1);

        if(dis <= da || d <= 2*da || db <= 2*da)
            pf("Alice\n");
        else
            pf("Bob\n");

        for1(i, n) g[i].clear();
    }

    return 0;
}
