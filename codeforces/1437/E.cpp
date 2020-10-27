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

const ll sz = 5e5 + 10;
ll ara[sz], fix[sz], temp[sz];

ll LIS(ll l, ll r, ll lastVal, ll nextVal)
{
    ll len = r-l+1, ret = 0;
    for1(i, len) temp[i] = inf;

    for(ll i = l; i <= r; i++) {
        if(ara[i] < lastVal || ara[i] > nextVal)
            continue;

        ll pos = upper_bound(temp+1, temp+len+1, ara[i]) - temp;
        temp[pos] = ara[i];

        ret = max(ret, pos);
    }
    return ret;
}

int main()
{
    ll n, k;
    cin >> n >> k;

    for1(i, n) {
        sl(ara[i]);
        ara[i] -= i;
    }

    for1(i, k) {
        ll idx; sl(idx);

        fix[idx] = 1;
    }

    ll lastFixVal = -inf, ans = 0;
    ara[n+1] = inf;

    for1(i, n) {

        if(fix[i]) {
            if(ara[i] < lastFixVal) {
                cout << -1 << EL;
                return 0;
            }

            lastFixVal = ara[i];
            continue;
        }

        ll nextFix = n+1;
        for(ll j = i; j <= n; j++) {

            if(fix[j]) {
                nextFix = j;
                break;
            }
        }

        ll lis = LIS(i, nextFix-1, lastFixVal, ara[nextFix]);

        ans += (nextFix-i) - lis;

        i = nextFix-1;
    }

    cout << ans << EL;

    return 0;
}
