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

vector <bool> lst;

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll k;
        sl(k);

        if(k & 1) {
            pf("-1\n");
            continue;
        }

        ll now = 0;
        while(now < k) {

            ll lim;

            for1(i, 60) {
                ll v = (1LL << i);
                if(now + v > k)
                    break;

                now += v, lim = i;
            }

            for1(i, lim) {
                if(i==1) lst.pb(1);
                else lst.pb(0);
            }
        }

        pf("%lld\n", (ll)lst.size());
        for(const bool &b : lst)
            pf("%lld ", (ll)b);
        pn;

        lst.clear();
    }

    return 0;
}
