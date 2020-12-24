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

const ll sz = 1e5 + 10, offset = 1e5 + 10;
ll val[sz], ara[sz], csum[sz], BIT[sz+offset];

inline void upd(ll idx, ll n)
{
    while(idx <= n) {
        BIT[idx]++;
        idx += idx&(-idx);
    }
}

inline ll getSum(ll idx)
{
    ll ret = 0;

    while(idx > 0) {
        ret += BIT[idx];
        idx -= idx&(-idx);
    }
    return ret;
}

inline ll query(ll l, ll r)
{
    return getSum(r) - getSum(l-1);
}

int main()
{
    ll n;
    cin >> n;

    for1(i, n) {
        sl(ara[i]);

        val[i] = ara[i];
    }
    sort(ara+1, ara+n+1);

    ll len = n*(n+1)/2, h = len/2 + (len&1);

    ll lo = 1, hi = n, ret;

    while(lo <= hi) {

        ms(BIT, 0);

        ll mid = lo+hi >> 1;

        ll sum = 0, x = ara[mid];

        for1(i, n) {
            if(val[i] >= x)
                csum[i] = 1;
            else
                csum[i] = -1;

            csum[i] += csum[i-1];
        }

        ll eqlarge = 0;

        rep1(i, n) {

            upd(csum[i]+offset, n+offset);

            ll start;
            if(val[i] < x) start = csum[i]+1;
            else start = csum[i]-1;

            eqlarge += query(start+offset, n+offset);
        }

        if(eqlarge >= h) {
            lo = mid+1;
            ret = x;
        }
        else
            hi = mid-1;
    }

    cout << ret << EL;

    return 0;
}

