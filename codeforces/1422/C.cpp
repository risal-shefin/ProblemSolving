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

const ll sz = 1e5 + 10, mod = 1e9 + 7;
char s[sz];
ll sum[sz], pw[sz];

int main()
{
    pw[0] = 1;
    for1(i, sz-1) pw[i] = (pw[i-1] * 10) % mod;

    scanf("%s", s+1);
    ll len = strlen(s+1);

    ll now = 0, ans = 0;
    for1(i, len) {
        now = (now * 10 + (s[i] - '0')) % mod;
        sum[i] = (sum[i-1] + now) % mod;

        if(i < len) ans = (ans + now) % mod;
    }

    now = 0;
    rep1(i, len) {
        if(i == 1) break;

        ll take = len-i+1;
        now = ( ((s[i]-'0') * pw[take-1]) + now) % mod;

        ll totPre = (sum[i-2] * pw[take]) % mod;
        ll tot = (totPre + now*(i-1)) % mod;

        //cout << i << " " << totPre << " " << tot << EL;

        ans = (ans + tot) % mod;
    }

    cout << ans << EL;

    return 0;
}
