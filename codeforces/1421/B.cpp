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

const ll sz = 205;
char s[sz][sz];

vector <pii> ans;
ll n;

ll make_zero()
{
    ll need = 0;
    need += (s[n-1][n] != '1'), need += (s[n][n-1] != '1');
    need += (s[2][1] != '0'), need += (s[1][2] != '0');

    return need;
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        sl(n);

        for1(i, n)
            scanf("%s", s[i]+1);

        ll need = make_zero();
        if(need <= 2) {
            if(s[1][2] != '0') ans.pb(mp(1, 2));
            if(s[2][1] != '0') ans.pb(mp(2, 1));

            if(s[n-1][n] != '1') ans.pb(mp(n-1, n));
            if(s[n][n-1] != '1') ans.pb(mp(n, n-1));
        }
        else {
            if(s[1][2] != '1') ans.pb(mp(1, 2));
            if(s[2][1] != '1') ans.pb(mp(2, 1));

            if(s[n-1][n] != '0') ans.pb(mp(n-1, n));
            if(s[n][n-1] != '0') ans.pb(mp(n, n-1));
        }

        pf("%lld\n", (ll)ans.size());
        for(pii &pr : ans) pf("%d %d\n", pr.first, pr.second);

        ans.clear();
    }

    return 0;
}
