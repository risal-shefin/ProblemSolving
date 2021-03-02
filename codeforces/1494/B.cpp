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

ll n;

bool solve(ll u, ll r, ll d, ll l, ll op)
{
    if((op>>0) & 1)
        u--, l--;
    if((op>>1) & 1)
        u--, r--;

    if((op>>2)&1)
        d--, l--;
    if((op>>3)&1)
        d--, r--;

    if(u < 0 || r < 0 || d < 0 || l < 0)
        return 0;

    if(u>=n-1 || d>= n-1 || l >= n-1 || r >= n-1)
        return 0;

    return 1;
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll u, r, d, l;
        sl(n), sl(u), sl(r), sl(d), sl(l);

        ll lim = 1<<4, got = 0;
        for0(i, lim)
            got |= solve(u, r, d, l, i);

        if(got) pf("YES\n");
        else pf("NO\n");
    }

    return 0;
}
