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

const ll MAX_N = 1e7 + 10, MAX_P = 665000, sz = 1e6 + 10;
ll prime[MAX_P], ara[sz], exist[MAX_N];
bool chk[MAX_N];

int main()
{
    ll idp = 0;
    for(ll i = 2; i < MAX_N; i++) {
        if(!chk[i]) {
            for(ll j = i*i; j < MAX_N; j += i)
                chk[j] = 1;

            prime[++idp] = i;
        }
    }

    ll k, ans = 0;
    sl(k);

    for1(i, k) {
        sl(ara[i]);
        exist[ ara[i] ]++;
    }

    rep1(i, MAX_N-2) exist[i] += exist[i+1];

    for1(i, idp) {
        ll p = prime[i], pwr = 0;

        while(p < MAX_N) {

            ll mxd = (MAX_N-1) / p;
            for(ll j = mxd; j >= 1; j--) {

                if(j == mxd)
                    pwr += j * exist[p*j];
                else
                    pwr += j * ( exist[p*j] - exist[p*(j+1)] );
            }

            p *= prime[i];
        }

        ll lo = 1, hi = 1e13 + 10, pwr2, ret = 0;
        while(lo <= hi) {
            ll mid = (lo+hi) >> 1;

            p = prime[i], pwr2 = 0;
            while(p <= mid) {
                pwr2 += (mid / p);
                p *= prime[i];
            }

            if(pwr2 >= pwr) {
                ret = mid;
                hi = mid - 1;
            }
            else
                lo = mid + 1;
        }
        ans = max(ans, ret);
    }

    cout << ans << EL;

    return 0;
}
