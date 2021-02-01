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

const ll sz = 2e5 + 10, nsz = 1e6 + 10;
int par[nsz], tr[4*sz], idx;

ll findp(ll u) {
    if(par[u] == u)
        return u;
    return par[u] = findp(par[u]);
}

void build(ll lo, ll hi, ll node)
{
    if(lo == hi) {
        tr[node] = lo;
        return;
    }

    ll mid = lo+hi>>1, lft=node<<1, rgt=lft|1;

    build(lo, mid, lft);
    build(mid+1, hi, rgt);

    tr[node] = 0;
}

void upd(ll lo, ll hi, ll l, ll r, ll p, ll node)
{
    if(lo > r || hi < l)
        return;

    if(lo >= l && hi <= r && tr[node]) {
        ll pr = findp(tr[node]);
        par[pr] = tr[node] = p;
        return;
    }

    ll mid = lo+hi>>1, lft=node<<1, rgt=lft|1;

    upd(lo, mid, l, r, p, lft);
    upd(mid+1, hi, l, r, p, rgt);

    ll plft = findp(tr[lft]), prgt = findp(tr[rgt]);
    if(plft == prgt) tr[node] = plft;
    else tr[node] = 0;
}

int main()
{
    ll n, q;
    cin >> n >> q;

    for0(i, nsz) par[i] = i;
    build(1, n, 1);
    idx = n;

    while(q--) {
        ll typ, u, v;
        sl(typ), sl(u), sl(v);

        if(typ == 1) {
            u = findp(u), v = findp(v);
            par[v] = u;
        }
        else if(typ == 2) {
            upd(1, n, u, v, ++idx, 1);
        }
        else {
            u = findp(u), v = findp(v);
            if(u == v)
                pf("YES\n");
            else
                pf("NO\n");
        }
    }

    return 0;
}
