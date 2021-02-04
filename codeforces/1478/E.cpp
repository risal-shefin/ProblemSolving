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

const ll sz = 2e5 + 10;

struct info {
    ll l, r;
} qry[sz];

string s1, s2;
ll one[4*sz], lazy[4*sz];

void prop(ll lo, ll hi, ll node)
{
    ll mid = lo+hi>>1, lft = node<<1, rgt = lft|1;

    one[lft] = (lazy[node] == 1)? (mid-lo+1) : 0;
    one[rgt] = (lazy[node] == 1)? (hi-mid) : 0;
    lazy[lft] = lazy[node], lazy[rgt] = lazy[node];

    lazy[node] = -1;
}

void build(ll lo, ll hi, ll node)
{
    if(lo == hi) {
        one[node] = s2[lo-1]-'0';
        lazy[node] = -1;
        return;
    }

    ll mid = lo+hi>>1, lft = node<<1, rgt = lft|1;

    build(lo, mid, lft);
    build(mid+1, hi, rgt);

    one[node] = one[lft] + one[rgt];
    lazy[node] = -1;
}

void upd(ll lo, ll hi, ll l, ll r, ll v, ll node)
{
    if(lo > r || hi < l)
        return;
    if(lo >= l && hi <= r) {
        one[node] = (v==1)? (hi-lo+1) : 0;
        lazy[node] = v;
        return;
    }

    if(lazy[node] != -1) prop(lo, hi, node);

    ll mid = lo+hi>>1, lft = node<<1, rgt = lft|1;

    upd(lo ,mid, l, r, v, lft);
    upd(mid+1, hi, l, r, v, rgt);

    one[node] = one[lft] + one[rgt];
}

ll query(ll lo, ll hi, ll l, ll r, ll node)
{
    if(lo > r || hi < l)
        return 0;
    if(lo >= l && hi <= r)
        return one[node];

    if(lazy[node] != -1) prop(lo, hi, node);

    ll mid = lo+hi>>1, lft = node<<1, rgt = lft|1;

    return query(lo, mid, l, r, lft)
        +  query(mid+1, hi, l, r, rgt);
}

bool check(ll lo, ll hi, ll node)
{
    if(lo == hi) {
        ll now = s1[lo-1] - '0';
        return one[node] == now;
    }
    if(lazy[node] != -1) prop(lo, hi, node);

    ll mid = lo+hi>>1, lft = node<<1, rgt = lft|1;

    return check(lo, mid, lft) & check(mid+1, hi, rgt);
}

int main()
{
    fastio;

    ll t;
    cin >> t;

    while(t--) {
        ll n, q, ok = 1;
        cin >> n >> q;
        cin >> s1 >> s2;

        for1(i, q) {
            ll l, r;
            cin >> qry[i].l >> qry[i].r;
        }

        build(1, n, 1);

        rep1(i, q) {
            ll rng = qry[i].r - qry[i].l + 1;
            ll o = query(1, n, qry[i].l, qry[i].r, 1);

            if(rng % 2 == 0 && rng/2 == o) {
                ok = 0;
                break;
            }

            ll z = rng-o;

            if(z > o) upd(1, n, qry[i].l, qry[i].r, 0, 1);
            else upd(1, n, qry[i].l, qry[i].r, 1, 1);
        }

        ok &= check(1, n, 1);

        if(!ok)
            cout << "NO\n";
        else
            cout << "YES\n";
    }

    return 0;
}
