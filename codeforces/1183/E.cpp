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

vector <int> pos[26];
ll dp[105][105];
string s;

ll solve(ll p1, ll p2)
{
    if(p2 == 0)
        return 1;
    if(p1 == s.size())
        return 0;

    ll &ret = dp[p1][p2];
    if(ret != -1)
        return ret;

    ret = 0;
    for0(i, 26) {
        ll nxt = lower_bound(all(pos[i]), p1) - pos[i].begin();
        if(nxt == pos[i].size())
            continue;

        ret += solve(pos[i][nxt]+1, p2-1);
    }

    return ret;
}

int main()
{
    fastio;

    ll n, k;
    cin >> n >> k;

    cin >> s;

    ms(dp, -1);

    for(ll i = 0; i < s.size(); i++)
        pos[ s[i] - 'a' ].pb(i);

    ll ans = 0, ok = 0;
    for(ll i = s.size(); i >= 0 && k > 0; i--) {
        ll got = solve(0, i);
        //cout << i << " " << got << EL;

        if(got >= k)
            ok = 1;

        ll mn = min(got, k);
        ans += mn*(n-i);
        k -= mn;
    }

    if(ok) cout << ans << EL;
    else cout << -1 << EL;

    return 0;
}
