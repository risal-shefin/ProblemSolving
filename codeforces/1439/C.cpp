// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
using namespace std;

#define ll int
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
#define inf (1LL << 30)
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

#define LL long long

const ll sz = 2e5 + 10;

struct tre {
    LL sum;
    ll mn;
} tree[4*sz];

ll lazy[4*sz], ara[sz];

void prop(ll lo, ll hi, ll node)
{
    ll mid = lo+hi>>1, lft = node<<1, rgt = lft|1;

    tree[lft].mn = tree[rgt].mn = lazy[node];

    tree[lft].sum = (LL)(mid-lo+1) * lazy[node];
    tree[rgt].sum = (LL)(hi - mid) * lazy[node];

    lazy[lft] = lazy[rgt] = lazy[node];
    lazy[node] = 0;
}

void build(ll lo, ll hi, ll node)
{
    if(lo == hi) {
        tree[node] = {ara[lo], ara[lo]};
        return;
    }

    ll mid = lo+hi>>1, lft = node<<1, rgt = lft|1;

    build(lo, mid, node<<1);
    build(mid+1, hi, node<<1 | 1);

    tree[node].mn = min(tree[lft].mn, tree[rgt].mn);
    tree[node].sum = tree[lft].sum + tree[rgt].sum;
}

void upd(ll lo, ll hi, ll l, ll r, ll v, ll node)
{
    if(lo > r || hi < l)
        return;
    if(lo >= l && hi <= r) {
        tree[node].mn = lazy[node] = v;
        tree[node].sum = (LL)(hi-lo+1)*v;
        return;
    }

    if(lazy[node]) prop(lo, hi, node);

    ll mid = lo+hi>>1, lft = node<<1, rgt = lft|1;

    upd(lo, mid, l, r, v, lft);
    upd(mid+1, hi, l, r, v, rgt);

    tree[node].mn = min(tree[lft].mn, tree[rgt].mn);
    tree[node].sum = tree[lft].sum + tree[rgt].sum;
}

ll qmn(ll lo, ll hi, ll l, ll r, ll v, ll node)
{
    if(lo > r || hi < l)
        return inf;

    if(lo == hi)
        return lo;

    if(lazy[node]) prop(lo, hi, node);

    ll mid = lo+hi>>1, lft = node<<1, rgt = lft|1, ret = inf;

    if(tree[lft].mn <= v)
        ret = qmn(lo, mid, l, r, v, lft);
    if(ret == inf && tree[rgt].mn <= v)
        ret = qmn(mid+1, hi, l, r, v, rgt);

    return ret;
}

pll query(ll lo, ll hi, ll l, ll r, ll v, ll node)
{
    if(lo > r || hi < l || tree[node].mn > v)
        return mp(v, inf);

    if(lo >= l && hi <= r && tree[node].sum <= v)
        return mp(v-tree[node].sum, hi);

    if(lazy[node]) prop(lo, hi, node);

    ll mid = lo+hi>>1, lft = node<<1, rgt = lft|1;

    pll got = query(lo, mid, l, r, v, lft), got2 = mp(inf, inf);
    if((l <= mid && got.second == mid) || l > mid)
        got2 = query(mid+1, hi, l, r, got.first, rgt);

    if(got2.second != inf)
        return got2;
    else
        return got;
}

int main()
{
    ll n, q;
    cin >> n >> q;
    for1(i, n) si(ara[i]);

    build(1, n, 1);

    while(q--) {
        ll typ, x, y;
        si(typ), si(x), si(y);

        if(typ == 1) {
            ll idx = qmn(1, n, 1, n, y, 1);
            if(idx <= x) upd(1, n, idx, x, y, 1);
        }
        else {

            ll ans = 0, start = x;

            while(start <= n) {
                ll idx = qmn(1, n, start, n, y, 1);
                if(idx > n) break;

                pll got = query(1, n, idx, n, y, 1);
                ans += got.second-idx+1;
                y = got.first, start = got.second+1;
            }

            pf("%d\n", ans);
        }
    }

    return 0;
}
