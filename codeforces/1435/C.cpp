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
ll b[sz], a[10], need[sz][10], n, maxx[sz*6];

vector <int> lst;

int main()
{
    for1(i, 6) sl(a[i]);

    sl(n);

    ll minMax = inf;

    for1(i, n) {
        sl(b[i]);

        for1(j, 6) {
            ll cst = b[i] - a[j];
            need[i][j] = cst;

            lst.pb(cst);
        }
        sort(need[i]+1, need[i]+6+1);

        minMax = min(minMax, need[i][6]);
    }

    sort(all(lst));
    lst.erase(unique(all(lst)), lst.end());

    for1(i, n) {
        for1(j, 6) {

            ll now = lower_bound(all(lst), need[i][j]) - lst.begin(), prv = -1;

            if(j != 1) prv = lower_bound(all(lst), need[i][j-1]) - lst.begin();

            if(prv < now) maxx[prv+1] = max(maxx[prv+1], need[i][j]);
        }
    }

    ll ans = inf, mx = 0;

    for(int idx = 0; idx < lst.size(); idx++) {

        if(lst[idx] > minMax) break;

        mx = max(mx, maxx[idx]);
        ans = min(ans, mx - lst[idx]);
    }

    cout << ans << EL;

    return 0;
}
