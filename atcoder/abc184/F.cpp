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

const ll sz = 50;
ll n, h, t, ara[sz], ans;
vector <int> lst;

void solve1(ll pos, ll tim)
{
    if(pos > h) {
        if(tim <= t) {
            ans = max(ans, tim);
            lst.pb(tim);
        }
        return;
    }

    solve1(pos+1, tim);
    solve1(pos+1, tim+ara[pos]);
}

void solve2(ll pos, ll tim)
{
    if(pos > n) {
        if(tim <= t) {
            ans = max(ans, tim);

            ll need = t-tim;
            ll idx = upper_bound(all(lst), need) - lst.begin();
            idx--;

            ans = max(ans, tim+lst[idx]);
        }
        return;
    }

    solve2(pos+1, tim);
    solve2(pos+1, tim+ara[pos]);
}

int main()
{
    cin >> n >> t;
    for1(i, n) sl(ara[i]);

    h = n / 2;

    solve1(1, 0);
    sort(all(lst));

    solve2(h+1, 0);

    cout << ans << EL;

    return 0;
}
