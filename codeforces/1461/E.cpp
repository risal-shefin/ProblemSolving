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

const ll sz = 1e6 + 10;
bool vis[sz];

int main()
{
    ll k, l, r, t, x, y;
    cin >> k >> l >> r >> t >> x >> y;

    if(k+y <= r) k += y;
    k -= x;

    if(k < l) {
        pf("No\n");
        return 0;
    }

    if(t == 1 || x == y) {
        pf("Yes\n");
        return 0;
    }

    t--;

    if(y < x) {
        ll decr = x-y;
        ll day = (k-l) / decr;
        day++;

        if(day > t)
            pf("Yes\n");
        else
            pf("No\n");

        return 0;
    }

    ll now = 1;

    while(now <= t) {
        ll day = (k-l)/x;
        k -= day*x, now += day;

        if(now > t || vis[k-l]) {
            pf("Yes\n");
            return 0;
        }

        vis[k-l] = 1;

        if(k+y > r) {
            pf("No\n");
            return 0;
        }

        k += y, k -= x, now++;
    }

    pf("Yes\n");

    return 0;
}
