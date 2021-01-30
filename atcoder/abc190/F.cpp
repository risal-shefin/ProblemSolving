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
ll BIT[sz], ara[sz], big[sz], small[sz], pbig[sz], psmall[sz];

void upd(ll idx, ll n)
{
    while(idx <= n) {
        BIT[idx]++;
        idx += idx&(-idx);
    }
}

ll query(ll idx)
{
    ll ret = 0;
    while(idx > 0) {
        ret += BIT[idx];
        idx -= idx&(-idx);
    }
    return ret;
}

inline ll qry(ll l, ll r)
{
    return query(r) - query(l-1);
}

int main()
{
    ll n;
    cin >> n;

    for1(i, n) {
        sl(ara[i]);
        ara[i]++;
    }

    ll tot = 0;

    rep1(i, n) {

        if(ara[i] == n) big[i] = 0;
        else big[i] = qry(ara[i]+1, n);

        upd(ara[i], n);

        small[i] = qry(1, ara[i]-1);
        tot += small[i];
    }

    ms(BIT, 0);

    for1(i, n) {

        if(ara[i] == n) pbig[i] = 0;
        else pbig[i] = qry(ara[i]+1, n);

        upd(ara[i], n);

        psmall[i] = qry(1, ara[i]-1);
    }

    pf("%lld\n", tot);

    for1(i, n-1) {
        tot -= small[i], tot -= psmall[i];
        tot += pbig[i], tot += big[i];

        pf("%lld\n", tot);
    }

    return 0;
}
