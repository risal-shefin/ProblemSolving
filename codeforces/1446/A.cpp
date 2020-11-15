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
struct info {
    ll num, id;
} ara[sz];

const bool operator <(const info &a, const info &b)
{
    return a.num < b.num;
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n, w; sl(n), sl(w);

        for1(i, n) {
            sl(ara[i].num);
            ara[i].id = i;
        }

        sort(ara+1, ara+n+1);

        vector <int> ans;

        ll h = w/2 + (w&1), sum = 0, ok = -1;

        rep1(i, n) {
            if(ara[i].num > w)
                continue;

            sum += ara[i].num;
            ans.pb(ara[i].id);

            if(sum > w) break;

            if(sum >= h) {
                ok = 1;
                break;
            }
        }
        sort(all(ans));

        if(ok == -1) pf("-1\n");
        else {

            pf("%lld\n", (ll)ans.size());

            for(int &v : ans) pf("%d ", v);
            pn;
        }
    }

    return 0;
}
