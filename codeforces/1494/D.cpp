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

const ll sz = 4*505;
ll par[sz], sal[sz];

struct info {
    ll sal, u, v;
    const bool operator <(const info &b) {
        if(sal == b.sal) {
            if(u == b.u)
                return v < b.v;
            return u < b.u;
        }
        return sal < b.sal;
    }
};
vector <info> lst;

ll findp(ll u)
{
    if(par[u] == u)
        return u;
    return par[u] = findp(par[u]);
}

int main()
{
    vector <pii> ans;

    for1(i, sz-1) par[i] = i;

    ll n; sl(n);

    for1(i, n) {
        for1(j, n) {
            ll v; sl(v);

            if(i == j)
                sal[i] = v;
            else if(i < j)
                lst.pb({v, i, j});
        }
    }
    sort(all(lst));
    ll idx = n;

    for(info &yo : lst) {
        ll pu = findp(yo.u), pv = findp(yo.v);
        if(pu == pv)
            continue;

        if(yo.sal == sal[pu]) {
            ans.pb(mp(pv, pu));
            par[pv] = pu;
        }
        else if(yo.sal == sal[pv]) {
            ans.pb(mp(pu, pv));
            par[pu] = pv;
        }
        else {
            ll newPar = ++idx;
            ans.pb(mp(pu, newPar));
            ans.pb(mp(pv, newPar));

            sal[newPar] = yo.sal;
            par[pu] = par[pv] = newPar;
        }
    }

    cout << idx << EL;
    for1(i, idx) pf("%lld ", sal[i]);
    pn;

    cout << idx << EL;
    for(pii &p : ans)
        pf("%d %d\n", p.first, p.second);

    return 0;
}
