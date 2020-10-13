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

const ll sz = 2009;
ll mat[sz][sz];
vector <int> lst[2][10];

int main()
{
    ll n, m, k, s;
    cin >> n >> m >> k >> s;

    for1(i, n) {
        for1(j, m) {
            ll inp; sl(inp);

            lst[0][inp].pb(i+j);
            lst[1][inp].pb(i-j);
        }
    }

    for1(i, k) sort(all(lst[0][i])), sort(all(lst[1][i]));

    ll ans = 0, prv = -1;

    for1(i, s) {
        ll inp; sl(inp);

        if(prv == -1) {
            prv = inp;
            continue;
        }

        ll d1 = lst[0][inp].back() - lst[0][prv][0], d2 = lst[1][inp].back() - lst[1][prv][0];
        d1 = max(d1, (ll)lst[0][prv].back() - lst[0][inp][0]);
        d2 = max(d2, (ll)lst[1][prv].back() - lst[1][inp][0]);

        ans = max({ans, d1, d2});
        prv = inp;
    }

    cout << ans << EL;

    return 0;
}
