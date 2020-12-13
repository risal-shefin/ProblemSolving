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

const ll sz = 3e5 + 10;
ll ara[sz], tr[4*sz];

void build(ll lo, ll hi, ll node)
{
    if(lo == hi) {
        tr[node] = ara[lo];
        return;
    }

    ll mid = lo+hi >> 1, lft = node<<1, rgt = lft|1;

    build(lo, mid, lft);
    build(mid+1,hi, rgt);

    tr[node] = tr[lft] ^ tr[rgt];
}

void upd(ll lo, ll hi, ll idx, ll v, ll node)
{
    if(lo > idx || hi < idx)
        return;
    if(lo == hi) {
        tr[node] ^= v;
        return;
    }

    ll mid = lo+hi >> 1, lft = node<<1, rgt = lft|1;

    upd(lo, mid, idx, v, lft);
    upd(mid+1,hi, idx, v, rgt);

    tr[node] = tr[lft] ^ tr[rgt];
}

ll query(ll lo, ll hi, ll l, ll r, ll node)
{
    if(lo > r || hi < l)
        return 0;
    if(lo >= l && hi <= r)
        return tr[node];

    ll mid = lo+hi >> 1, lft = node<<1, rgt = lft|1;

    return query(lo, mid, l, r, lft) ^
        query(mid+1,hi, l, r, rgt);
}

int main()
{
    ll n, q;
    cin >> n >> q;
    for1(i, n) sl(ara[i]);

    build(1, n, 1);

    while(q--) {
        ll typ, x, y;
        sl(typ), sl(x), sl(y);

        if(typ == 1)
            upd(1, n, x, y, 1);
        else
            pf("%lld\n", query(1, n, x, y, 1));
    }

    return 0;
}
