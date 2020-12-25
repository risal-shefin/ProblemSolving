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

const ll sz = 2e5 + 10, LN = 20;

struct info {
    ll u, v, d;

    const bool operator <(const info &b) {
        return d < b.d;
    }

} Edge[sz];

struct node {
    ll v, c;
};
vector <node> g[sz];

ll par[sz], mark[sz];

ll findp(ll u)
{
    if(u == par[u])
        return u;
    return par[u] = findp(par[u]);
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n, m, k;
        sl(n), sl(m), sl(k);

        for1(i, m) {
            sl(Edge[i].u), sl(Edge[i].v), sl(Edge[i].d);
            mark[i] = 0;
        }

        sort(Edge+1, Edge+m+1);

        for1(i, n) {
            par[i] = i;
            g[i].clear();
        }

        ll ans = 0, diff = inf, grt = 0;

        for1(i, m) {
            ll u = Edge[i].u, v = Edge[i].v, d = Edge[i].d;
            ll pu = findp(u), pv = findp(v);

            //cout << pu << " " << pv << " " << u << endl;
            if(pu == pv)
                continue;

            mark[i] = 1;

            diff = min(diff, abs(k-d));
            //cout << k << " ||  " << d << endl;
            if(d > k)
                grt += (d-k);

            par[pv] = pu;

            g[u].pb({v, d});
            g[v].pb({u, d});
        }

        if(grt != 0)
            ans = grt;
        else
            ans = diff;

        if(grt != 0) {
            pf("%lld\n", ans);
            continue;
        }

        ll ans2 = inf;
        for1(i, m) {
            if(mark[i])
                continue;

            ll d = Edge[i].d;

            ans2 = min(ans2, abs(k-d));
        }

        pf("%lld\n", min(ans, ans2));
    }

    return 0;
}

