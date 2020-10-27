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

ll a, b, c, d;

inline ll sumN(ll n) {

    if(n & 1)
        return (n+1)/2 * n;
    else
        return n/2 * (n+1);
}

inline ll check(ll k)
{
    ll tim = k*d, attack = a*(k+1), fullCnt = -1, fullHeal = 0;

    if(tim >= c) fullCnt = (tim-c)/d, fullHeal = (fullCnt+1)*b*c;

    ll rest = (k-fullCnt) - 1;

    ll restStart = (fullCnt+1)*d, restTim = tim-restStart;
    ll restHeal = b * (rest*restTim - d*sumN(rest-1));

    return attack - (fullHeal + restHeal);
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        sl(a), sl(b), sl(c), sl(d);

        if(a > b*c) {
            pf("-1\n");
            continue;
        }

        ll lo = 0, hi = 1e6, ret = 0;
        while(lo < hi) {
            ll mid = lo+hi >> 1;

            ll got1 = check(mid), got2 = check(mid+1);

            if(got1 > got2) {
                ret = max(ret, got1);
                hi = mid;
            }
            else {
                ret = max(ret, got2);
                lo = mid+1;
            }
        }
        ret = max(ret, check(lo));

        pf("%lld\n", ret);
    }

    return 0;
}
