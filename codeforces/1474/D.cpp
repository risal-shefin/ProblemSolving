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
ll ara[sz], tr[4*sz][2], lazy[4*sz], n;

void prop(ll lo, ll hi, ll node)
{
    ll lft = node<<1, rgt = lft|1;

    tr[lft][1] += lazy[node], tr[rgt][1] += lazy[node];
    tr[lft][0] -= lazy[node], tr[rgt][0] -= lazy[node];

    lazy[lft] += lazy[node], lazy[rgt] += lazy[node];

    lazy[node] = 0;
}

void build(ll lo, ll hi, ll node)
{
    if(lo == hi) {
        if(lo & 1) {
            tr[node][0] = inf;
            tr[node][1] = 0;
        }
        else {
            tr[node][1] = inf;
            tr[node][0] = 0;
        }

        lazy[node] = 0;
        return;
    }

    ll mid = lo+hi>>1, lft = node<<1, rgt = lft|1;

    build(lo, mid, lft);
    build(mid+1, hi, rgt);

    tr[node][0] = min(tr[lft][0], tr[rgt][0]);
    tr[node][1] = min(tr[lft][1], tr[rgt][1]);

    lazy[node] = 0;
}

void upd(ll lo, ll hi, ll l, ll r, ll val, bool s, ll node)
{
    if(lo > r || hi < l)
        return;
    if(lo >= l && hi <= r) {
        tr[node][s] += val, tr[node][!s] -= val;
        lazy[node] += (s==1)? val : -val;
        return;
    }

    if(lazy[node] != 0) prop(lo, hi, node);

    ll mid = lo+hi>>1, lft = node<<1, rgt = lft|1;
    upd(lo, mid, l, r, val, s, lft);
    upd(mid+1, hi, l, r, val, s, rgt);

    tr[node][s] = min(tr[lft][s], tr[rgt][s]);
    tr[node][!s] = min(tr[lft][!s], tr[rgt][!s]);
}

void swp(ll i, ll j)
{
    upd(1, n, i, n, -ara[i]+ara[j], i&1, 1);
    upd(1, n, j, n, -ara[j]+ara[i], j&1, 1);

    swap(ara[i], ara[j]);
}

ll query(ll lo, ll hi, ll idx, ll s, ll node)
{
    if(lo > idx || hi < idx)
        return inf;
    if(lo == hi)
        return tr[node][s];

    if(lazy[node] != 0) prop(lo, hi, node);

    ll mid = lo+hi>>1, lft = node<<1, rgt = lft|1;

    return min(query(lo, mid, idx, s, lft),
               query(mid+1, hi, idx, s, rgt));
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        sl(n);
        for1(i, n)
            sl(ara[i]);

        ll ok = 0, idx = n;

        build(1, n, 1);

        for1(i, n)
            upd(1, n, i, n, ara[i], i&1, 1);

        if(tr[1][0] >= 0 && tr[1][1] >= 0 && query(1, n, n, n&1, 1) == 0)
            ok = 1;

        for1(i, n-1) {

            swp(i, i+1);
            //cout << tr[1][0] << " " << tr[1][1] << endl;

            if(tr[1][0] >= 0 && tr[1][1] >= 0 && query(1, n, n, n&1, 1) == 0) {
                ok = 1;
                break;
            }

            swp(i, i+1);
        }

        if(ok) pf("YES\n");
        else pf("NO\n");
    }

    return 0;
}
