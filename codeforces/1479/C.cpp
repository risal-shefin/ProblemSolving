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

struct info {
    ll u, v, c;
};

int main()
{
    ll a, b;
    cin >> a >> b;

    vector <info> edge;

    auto add = [&](ll u, ll v, ll c) {
        edge.pb({u, v, c});
    };

    function <ll (ll, ll)> solve = [&](ll l, ll r) {

        if(l != 1) {
            ll k = solve(1, r-l+1);
            add(k, k+1, l-1);

            return k+1;
        }

        ll bt = 0;
        rep0(i, 21) {
            if((r>>i) & 1) {
                bt = i;
                break;
            }
        }

        if((1 << bt) == r) {
            ll k = bt+2;

            for(ll i = 2; i <= k; i++) add(1, i, 1);

            for(ll i = 2; i <= k; i++)
                for(ll j = i+1; j <= k; j++)
                    add(i, j, 1<<(i-2));

            return k;
        }

        ll k = solve(l, 1<<bt);

        add(1, k+1, 1);

        r--;
        for0(i, 21) {
            if((r>>i) & 1) {
                r -= (1<<i);
                add(i+2, k+1, r+1);
            }
        }

        return k+1;
    };

    cout << "YES\n";

    cout << solve(a, b) << " " << edge.size() << EL;
    for(auto &[u, v, c] : edge)
        pf("%lld %lld %lld\n", u, v, c);

    return 0;
}
