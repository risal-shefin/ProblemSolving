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

const ll sz = 5009;
ll ara[sz];
unordered_map <int, int> cnt;
unordered_map <int, vector <int> > city;

const bool cmp(const int &a, const int &b) {
    return cnt[a] < cnt[b];
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        cnt.clear(), city.clear();

        ll n; sl(n);

        vector <int> lst;
        vector <pii> ans;

        for1(i, n) {
            sl(ara[i]);

            city[ ara[i] ].pb(i);

            if(cnt.find( ara[i]) == cnt.end())
                lst.pb(ara[i]);

            ++cnt[ ara[i] ];
        }
        sort(all(lst), cmp);

        if(lst.size() == 1) {
            pf("NO\n");
            continue;
        }

        for(ll i = lst.size()-1; i >= 1; i--) {
            vector <int> &v = city[ lst[i] ];
            int prv = city[ lst[i-1] ][0];

            for(int &c : v)
                ans.pb(mp(c, prv));
        }

        vector <int> &v = city[ lst[0] ];
        for(ll i = 1; i < v.size(); i++) {
            int nxt = city[ lst[1] ][0];
            ans.pb(mp(v[i], nxt));
        }

        pf("YES\n");
        for(pii &p : ans)
            pf("%d %d\n", p.first, p.second);
    }

    return 0;
}