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

const ll sz = 2e5 + 10;
ll premn[sz], premx[sz], preSum[sz];
ll sufmn[sz], sufmx[sz];

int main()
{
    fastio;
    ll t;
    cin >> t;

    while(t--) {
        ll n, m;
        cin >> n >> m;

        string s;
        cin >> s;

        ll sum = 0;

        premn[0] = sufmn[n+1] = inf;
        premx[0] = sufmx[n+1] = -inf;

        for(ll i = 1; i <= n; i++) {
            ll id = i-1;

            if(s[id] == '+') sum++;
            else sum--;

            premn[i] = min(premn[i-1], sum);
            premx[i] = max(premx[i-1], sum);
            preSum[i] = sum;
        }

        rep1(i, n) {
            sufmn[i] = min(sufmn[i+1],preSum[i]);
            sufmx[i] = max(sufmx[i+1], preSum[i]);
        }

        while(m--) {
            ll l, r;
            cin >> l >> r;

            ll lft = 0, rgt = 0;
            if(l != 1) lft = min(lft, premn[l-1]), rgt = max(rgt, premx[l-1]);

            ll now = (l != 1)? preSum[l-1] : 0;

            if(r != n) {
                ll mn = sufmn[r+1] - preSum[r], mx = sufmx[r+1] - preSum[r];
                lft = min(lft, now+mn), rgt = max(rgt, now+mx);
            }

            cout << (rgt-lft+1) << EL;
        }
    }

    return 0;
}
