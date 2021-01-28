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

vector <ll> lst, sob, yo[10];
ll dp[150];

bool check(ll d, ll num)
{
    while(num) {
        ll rem = num % 10;
        if(rem == d)
            return 1;
        num /= 10;
    }
    return 0;
}

void make(ll d, ll n)
{
    for1(i, n) if(check(d, i)) lst.pb(i);
}

void gen(ll sum, ll n)
{
    if(sum > n) return;
    if(dp[sum] != -1)
        return;

    sob.pb(sum);
    dp[sum] = 1;

    for(ll &v : lst) {
        gen(sum+v, n);
    }
}

int main()
{
    for(ll i = 1; i <= 9; i++) {

        lst.clear(), sob.clear();
        ms(dp, -1);

        ll d = i, n = 100;
        make(d, n);
        gen(0, n);

        sort(all(sob));
        sob.erase(unique(all(sob)), sob.end());

        yo[i] = sob;
    }

    ll t;
    cin >> t;
    while(t--) {
        ll q, d;
        sl(q), sl(d);

        for1(i, q) {
            ll x; sl(x);

            if(x >= 100) pf("YES\n");
            else {
                ll p = lower_bound(all(yo[d]), x) - yo[d].begin();

                if(p == yo[d].size() || yo[d][p] != x)
                    pf("NO\n");
                else
                    pf("YES\n");
            }
        }
    }

    return 0;
}

