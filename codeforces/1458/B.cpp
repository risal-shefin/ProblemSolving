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

const ll sz = 105;
ll cap[sz], w[sz], dp[2][sz][sz*sz];

int main()
{
    ll n, tot = 0, ase = 0;
    sl(n);

    for1(i, n) {
        sl(cap[i]), sl(w[i]);
        ase += w[i];
        tot += cap[i];
    }

    for0(i, 2)
        for0(k, sz)
            for0(c, sz*sz)
                dp[i][k][c] = -inf;

    dp[0][0][0] = 0;

    bool state = 0;

    for1(i, n) {

        state ^= 1;

        for(ll k = 0; k <= n; k++) {
            for(ll c = 0; c <= tot; c++) {

                dp[state][k][c] = dp[state^1][k][c];

                if(c >= cap[i] && k > 0)
                    dp[state][k][c] = max(dp[state][k][c], dp[state^1][k-1][c-cap[i]] + w[i]);
            }
        }
    }

    for1(k, n) {

        double ans = 0;

        for1(c, tot) {
            ll rest = ase - dp[state][k][c];
            ans = max(ans, min((dd)c, (dd)dp[state][k][c] + (dd)rest/2));
        }

        pf("%0.10f ", ans);
    }
    pn;

    return 0;
}
