#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma")

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
#define inf (1LL << 62)
#define loop(i, start, stop, inc) for(ll i = start; i <= stop; i += inc)
#define for1(i, stop) for(ll i = 1; i <= stop; i++)
#define for0(i, stop) for(ll i = 0; i < stop; i++)
#define rep1(i, start) for(ll i = start; i >= 1; i--)
#define rep0(i, start) for(ll i = (start-1); i >= 0; i--)
#define ms(n, i) memset(n, i, sizeof(n))
#define casep(n) printf("Case %lld:", ++n)
#define pn printf("\n")
#define pf printf
#define EL '\n'
#define fastio std::ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

const ll sz = 2e5 + 10, tot = 2*sz;
ll ara[sz], cnt[tot];

int tree[4*tot], lazy[4*tot];

void build(ll lo, ll hi, ll node)
{
    if(lo == hi) {
        tree[node] = lazy[node] = 0;
        return;
    }

    ll mid = (lo+hi) >> 1;
    build(lo, mid, node<<1);
    build(mid+1, hi, node<<1 | 1);

    tree[node] = lazy[node] = 0;
}

void prop(ll lo, ll hi, ll node)
{
    if(lo == hi)
        return;

    ll lft = node << 1, rgt = node << 1 | 1;
    lazy[lft] += lazy[node], lazy[rgt] += lazy[node];

    ll mid = (lo+hi) >> 1;
    tree[lft] += ((mid - lo + 1) * lazy[node]);
    tree[rgt] += ((hi - mid) * lazy[node]);

    lazy[node] = 0;
}

void update(ll lo, ll hi, ll l, ll r, ll node)
{
    if(lazy[node]) prop(lo, hi, node);

    if(lo > r || hi < l)
        return;
    if(lo >= l && hi <= r) {
        tree[node] += (hi - lo + 1);
        lazy[node]++;
        return;
    }

    ll mid = lo+hi >> 1;
    update(lo, mid, l, r, node<<1);
    update(mid+1, hi, l, r, node<<1|1);

    tree[node] = tree[(node<<1)] + tree[(node << 1 | 1)];
}

ll query(ll lo, ll hi, ll idx, ll node)
{
    if(lazy[node]) prop(lo, hi, node);

    if(lo > idx || hi < idx)
        return 0;

    if(lo == hi)
        return tree[node];

    ll mid = lo+hi >> 1;
    return query(lo, mid, idx, node<<1)
         + query(mid + 1, hi, idx, node<<1 | 1);
}

int main()
{
    ll t;
    cin >> t;
    while(t--) {
        ll n, k;
        si(n), si(k);

        build(1, 2*k, 1);

        for1(i, n) {
            si(ara[i]);
        }

        ll last = 2*k;
        for(ll i = 1, j = n; i <= n / 2; i++, j--) {
            ll sum = ara[i] + ara[j];

            cnt[sum]++;

            ll mn = min(ara[i], ara[j]);
            ll mx = max(ara[i], ara[j]);

            ll minSum = mn+1, maxSum = mx+k;
            update(1, last, minSum, maxSum, 1);
        }

        ll h = n / 2, ans = 1e9;
        for(ll i = 2; i <= last; i++) {
            ll zero = cnt[i];
            ll one = query(1, last, i, 1);
            one -= zero;

            ll need = one + (h - (zero + one)) * 2;
            ans = min(ans, need);
        }

        pf("%d\n", ans);

        for1(i, last) cnt[i] = 0;
    }

    return 0;
}
