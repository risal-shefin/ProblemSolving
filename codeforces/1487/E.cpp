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

const ll sz = 2e5 + 10, MAX_N = 6;
ll n[MAX_N], c[MAX_N][sz];
vector <ll> g[MAX_N][sz];

ll solve(ll p, ll q)
{
    multiset <ll> lst;
    for1(i, n[q])
        lst.insert(c[q][i]);

    ll mn = inf;

    for1(i, n[p]) {

        for(ll &v : g[p][i])
            lst.erase(lst.find(c[q][v]));

        if(lst.empty() || (*lst.begin()) == inf)
            c[p][i] = inf;
        else
            c[p][i] += *lst.begin();

        mn = min(mn, c[p][i]);

        for(ll &v : g[p][i])
            lst.insert(c[q][v]);
    }

    return mn;
}

int main()
{
    for1(i, 4) cin >> n[i];

    for1(i, 4) {
        for1(j, n[i])
            sl(c[i][j]);
    }

    for1(i, 3) {
        ll m; sl(m);

        for1(j, m) {
            ll u, v;
            sl(u), sl(v);

            g[i][u].pb(v);
        }
    }

    solve(3, 4);
    solve(2, 3);
    ll got =  solve(1, 2);

    if(got == inf) cout << -1 << EL;
    else cout << got << EL;

    return 0;
}
