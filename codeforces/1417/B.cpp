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
ll ara[sz];
unordered_map <int, bool> check;

int main()
{
    ll t;
    cin >> t;

    while(t--) {

        check.reserve((1<<15)+19);
        check.max_load_factor(0.25);

        ll n, k;
        sl(n), sl(k);

        for1(i, n) {
            sl(ara[i]);

            if(check.find(ara[i]) == check.end()) {
                check[ ara[i] ] = 0;
                check[ k-ara[i] ] = 1;
            }
        }

        ll half = 0;

        for1(i, n) {
            if(i != 1) pf(" ");

            if(2*ara[i] == k) {
                pf("%lld", half);
                half ^= 1;
            }
            else
                pf("%lld", (ll)check[ ara[i] ]);
        }
        pn;

        check.clear();
    }

    return 0;
}
