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
#define inf (1LL << 62)
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

const ll sz = 2e5 + 10, block = 62;
ll pw1[sz], pw2[sz], dp[sz];
char s[sz];

ll calc(ll n)
{
    if(dp[n] != -1) return dp[n];
    if(n == 0) return 0;
    ll one = __builtin_popcount(n);

    return 1 + calc(n % one);
}

int main()
{
    ms(dp, -1);
    dp[0] = 0;
    for(ll i = 1; i < sz; i++) {
        dp[i] = calc(i);
    }

    ll n;
    cin >> n;
    scanf("%s", s);

    ll one = 0;
    for0(i, n) {
        ll v = s[i] - '0';
        one += v;
    }

    const ll mod1 = one + 1, mod2 = one - 1;

    ll val1 = 0, val2 = 0;

    if(mod1 != 0) pw1[0] = 1 % mod1;
    if(mod2 != 0) pw2[0] = 1 % mod2;

    for1(i, n) {
        if(mod1 != 0) pw1[i] = (pw1[i-1] * 2LL) % mod1;
        if(mod2 != 0) pw2[i] = (pw2[i-1] * 2LL) % mod2;
    }

    for0(i, n) {
        ll v = s[i] - '0';

        if(mod1 != 0) val1 = (val1 * 2 + v) % mod1;
        if(mod2 != 0) val2 = (val2 * 2 + v) % mod2;
    }

    for0(i, n) {

        ll pos = n - i -1, val = -1;
        if(s[i] == '0') {
            if(mod1 != 0) val = (val1 + pw1[pos]) % mod1;
        }
        else {
            if(mod2 != 0) {
                val = (val2 - pw2[pos]) % mod2;
                if(val < 0) val += mod2;
            }
        }

        if(val == -1) pf("0\n");
        else pf("%lld\n", 1 + dp[val]);
    }

    return 0;
}

