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
ll last[sz], gotMex[sz], tree[4*sz];

void upd(ll lo, ll hi, ll idx, ll v, ll node)
{
    if(lo > idx || hi < idx)
        return;
    if(lo == hi) {
        tree[node] = v;
        return;
    }

    ll mid = lo+hi >> 1, lft = node<<1, rgt = lft|1;

    upd(lo, mid, idx, v, lft);
    upd(mid+1, hi, idx, v, rgt);

    tree[node] = min(tree[lft], tree[rgt]);
}

ll query(ll lo, ll hi, ll l, ll r, ll node)
{
    if(lo > r || hi < l)
        return inf;
    if(lo >= l && hi <= r)
        return tree[node];

    ll mid = lo+hi >> 1, lft = node<<1, rgt = lft|1;

    return min(query(lo, mid, l, r, lft),
           query(mid+1, hi, l, r, rgt) );
}

int main()
{
    ll n; sl(n);

    for1(i, n) {
        ll v; sl(v);

        if(v == 1) {
            upd(1, n, 1, i, 1);
            continue;
        }

        ll got = query(1, n, 1, v-1, 1);

        if(got > last[v]) gotMex[v] = 1;

        upd(1, n, v, i, 1);

        last[v] = i, gotMex[1] = 1;
    }

    for1(v, n+1) {
        if(v == 1) continue;

        ll got = query(1, n, 1, v-1, 1);

        if(got > last[v]) gotMex[v] = 1;
    }

    ll mex = 1;
    while(gotMex[mex]) mex++;

    cout << mex << EL;

    return 0;
}
