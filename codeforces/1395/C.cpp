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

const ll sz = 205;
ll a[sz], b[sz], dp[sz][512], n, m;

ll solve(ll pos, ll prv)
{
    if(pos > n)
        return 0;

    ll &ret = dp[pos][prv];
    if(ret != -1)
        return ret;

    ret = inf;
    for1(i, m) {
        ll now = a[pos] & b[i];
        ll val = prv | now;
        ret = min(ret, val | solve(pos+1, val));
    }

    return ret;
}

int main()
{
    cin >> n >> m;

    for1(i, n) sl(a[i]);
    for1(i, m) sl(b[i]);

    ms(dp, -1);
    ll ans = solve(1, 0);

    cout << ans << EL;

    return 0;
}
