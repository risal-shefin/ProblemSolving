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

struct info {
    ll a, h, l, r;
} ara[sz];

struct info2 {
    ll b, z;
} magic[sz];

const bool operator <(const info2 &a, const info2 &b) {
    return a.b < b.b;
}

ld tree[4*sz], lazy[4*sz];
bool chk[4*sz];

void prop(ll lo, ll hi, ll node)
{
    ll lft = node<<1, rgt = lft|1;

    tree[lft] *= lazy[node], tree[rgt] *= lazy[node];
    lazy[lft] *= lazy[node], lazy[rgt] *= lazy[node];
    chk[lft] = chk[rgt] = 1;

    lazy[node] = 1, chk[node] = 0;
}

void upd(ll lo, ll hi, ll l, ll r, ld v, ll node)
{
    if(lo > r || hi < l)
        return;
    if(lo >= l && hi <= r) {
        tree[node] *= v;
        lazy[node] *= v, chk[node] = 1;
        return;
    }
    if(chk[node]) prop(lo, hi, node);

    ll mid = lo+hi>>1;
    upd(lo, mid, l, r, v, node<<1);
    upd(mid+1, hi, l, r, v, node<<1|1);
}

ld query(ll lo, ll hi, ll idx, ll node)
{
    if(lo > idx || hi < idx)
        return 1;
    if(lo == hi)
        return tree[node];

    if(chk[node]) prop(lo, hi, node);

    ll mid = lo+hi>>1;
    return query(lo, mid, idx, node<<1)
        *  query(mid+1, hi, idx, node<<1|1);
}

int main()
{
    for0(i, 4*sz) tree[i] = lazy[i] = 1;

    ll n, m;
    cin >> n >> m;

    for1(i, n)
        sl(ara[i].a), sl(ara[i].h), sl(ara[i].l), sl(ara[i].r);

    for1(i, m)
        sl(magic[i].b), sl(magic[i].z);

    sort(magic+1, magic+m+1);

    for1(i, n) {

        ll x = ara[i].a, l = x - ara[i].h, r = x + ara[i].h;
        info2 tx = {x, 0}, tl = {l, 0}, tr = {r, 0};

        ld leftSave = (1 - ara[i].l/100.0), rightSave = (1 - ara[i].r/100.0);

        ll lftEnd = lower_bound(magic+1, magic+m+1, tx) - magic;
        lftEnd--;

        ll lftStart = lower_bound(magic+1, magic+m+1, tl) - magic;

        ll rightStart = upper_bound(magic+1, magic+m+1, tx) - magic;

        ll rightEnd = upper_bound(magic+1, magic+m+1, tr) - magic;
        rightEnd--;

        if(lftStart <= lftEnd)
            upd(1, m, lftStart, lftEnd, leftSave, 1);

        if(rightStart <= rightEnd)
            upd(1, m, rightStart, rightEnd, rightSave, 1);
    }

    ld ans = 0;
    for1(i, m)
        ans += magic[i].z * query(1, m, i, 1);

    cout << setprecision(5) << fixed << ans << EL;

    return 0;
}
