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

const ll sz = 105, tsz = sz*sz*2;
ll n, k, l;

ll d[sz], p[2*sz], dp[sz][tsz];

ll solve(ll pos, ll tim)
{
    if(pos > n) return 1;
    if(tim > tsz) return 0;

    ll &ret = dp[pos][tim];
    if(ret != -1)
        return ret;

    ll asi = d[pos] + p[tim % (2*k)];
    if(pos == 0) asi = 0;

    //cout << pos << " " << asi << " " << tim << endl;
    if(asi > l) return 0;

    ret = 0;

    ret |= solve(pos, tim+1);
    ret |= solve(pos+1, tim+1);

    return ret;
}

int main()
{
    ll t;
    cin >> t;
    while(t--) {
        sl(n), sl(k),sl(l);

        for1(i, n) sl(d[i]);

        ll now = 0, incr = 1;
        for(ll i = 0; i < 2*k; i++) {
            p[i] = now;

            if(now == k) incr = 0;

            if(incr) now++;
            else now--;
        }

        for(ll i = 0; i <= n; i++)
            for0(j, tsz) dp[i][j] = -1;

        bool got = solve(0, 0);

        if(got) pf("YES\n");
        else pf("NO\n");
    }

    return 0;
}

