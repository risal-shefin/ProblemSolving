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

#define ff first
#define ss second

const ll sz = 2e5 + 10;
vector <int> g[sz], ase[sz];
bool fib[sz];
ll sub[sz], done;

void subdfs(ll u, ll p)
{
    sub[u] = 1;

    for(int i = 0; i < g[u].size(); i++) {

        int v = g[u][i];

        if(v == p || !ase[u][i])
            continue;

        subdfs(v, u);
        sub[u] += sub[v];
    }
}

pll fiboPart(ll u, ll p, ll full)
{
    for(int i = 0; i < g[u].size(); i++) {

        int v = g[u][i];

        if(v == p || !ase[u][i])
            continue;

        if(fib[ sub[v] ] && fib[full - sub[v] ]) {

            ase[u][i] = 0;

            for(int j = 0; j < g[v].size(); j++) {
                if(g[v][j] == u) {
                    ase[v][j] = 0;
                    break;
                }
            }

            return mp(u, v);
        }

        pll got = fiboPart(v, u, full);

        if(got.ff != -1)
            return got;
    }

    return mp(-1, -1);
}

bool check(ll u, ll siz)
{
    if(siz <= 3) return 1;
    subdfs(u, -1);

    pll got = fiboPart(u, -1, siz);
    if(got.ff == -1)
        return 0;

    return check(got.ff, siz-sub[got.ss]) & check(got.ss, sub[got.ss]);
}

int main()
{
    ll f1 = 1, f2 = 1;
    fib[1] = fib[2] = 1;
    while(1) {
        ll f3 = f1+f2;
        if(f3 >= sz)
            break;

        fib[f3] = 1;
        f1 = f2, f2 = f3;
    }

    ll n;
    sl(n);

    for1(i, n-1) {
        ll u, v;
        sl(u), sl(v);

        g[u].pb(v), g[v].pb(u);

        ase[u].pb(1), ase[v].pb(1);
    }

    if(!fib[n]) {
        pf("NO\n");
        return 0;
    }

    bool got = check(1, n);

    if(got) pf("YES\n");
    else pf("NO\n");

    return 0;
}

