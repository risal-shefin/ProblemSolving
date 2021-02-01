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

const ll sz = 1e5 + 10;
ll c[sz], t[sz];

int main()
{
    ll n; sl(n);
    vector <int> d1, d2;

    for1(i, n) {
        sl(c[i]);

        if(i != 1) d1.pb(c[i]-c[i-1]);
    }
    sort(all(d1));

    for1(i, n) {
        sl(t[i]);

        if(i != 1) d2.pb(t[i]-t[i-1]);
    }
    sort(all(d2));

    if(c[1] == t[1] && c[n] == t[n] && d1 == d2)
        cout << "Yes" << EL;
    else
        cout << "No" << EL;

    return 0;
}
