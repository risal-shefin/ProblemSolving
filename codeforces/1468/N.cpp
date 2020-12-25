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

int main()
{
    fastio;
    ll t;
    cin >> t;

    while(t--) {
        ll c1, c2, c3;
        cin >> c1 >> c2 >> c3;

        ll a1, a2, a3, a4, a5;
        cin >> a1 >> a2 >> a3 >> a4 >> a5;

        c1 -= a1, c2 -= a2, c3 -= a3;

        if(c1 < 0 || c2 < 0 || c3 < 0) {
            cout << "NO" << EL;
            continue;
        }

        a4 -= min(c1, a4);
        a5 -= min(c2, a5);

        if(a4+a5 > c3)
            cout << "NO" << EL;
        else
            cout << "YES" << EL;
    }

    return 0;
}
