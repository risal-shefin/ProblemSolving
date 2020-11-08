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

int main()
{
    ll t;
    cin >> t;

    while(t--) {

        ll n; sl(n);

        stack <int> odd, even;
        vector <pii> lst;

        for(ll i = 1; i <= n; i += 2) odd.push(i);
        for(ll i = 2; i <= n; i += 2) even.push(i);

        while(odd.size() > 1 || even.size() > 1) {

            ll o = -inf, e = -inf;
            if(odd.size() > 1) o = odd.top();
            if(even.size() > 1) e = even.top();

            if(o > e) {
                ll v1 = odd.top(); odd.pop();
                ll v2 = odd.top(); odd.pop();

                lst.pb(mp(v1, v2));

                ll h = (v1+v2) / 2;
                if(h & 1) odd.push(h);
                else even.push(h);
            }
            else {
                ll v1 = even.top(); even.pop();
                ll v2 = even.top(); even.pop();

                lst.pb(mp(v1, v2));

                ll h = (v1+v2) / 2;
                if(h & 1) odd.push(h);
                else even.push(h);
            }
        }

        ll ans = 0;

        if(odd.size() == 1 && even.size() == 1) {
            lst.pb(mp(odd.top(), even.top()));
            ans = (odd.top() + even.top() + 1) / 2;
        }
        else if(odd.size() == 1)
            ans = odd.top();
        else
            ans = even.top();

        pf("%lld\n", ans);
        for(pii &p : lst) pf("%d %d\n", p.first, p.second);
    }

    return 0;
}
