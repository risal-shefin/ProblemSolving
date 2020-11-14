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
ll ara[sz];
set <int> taken[sz];

int main()
{
    ll n, ans = 0;
    sl(n);

    for1(i, n) sl(ara[i]);

    for1(i, n) {

        ll b;
        rep0(j, 30) {
            if((ara[i] >> j) & 1) {
                b = j;
                break;
            }
        }

        ll sum = ara[i+1], lim = (1LL << (b+1));

        for(ll j = i+2; j <= n; j++) {

            if((ara[j] ^ ara[i]) == sum) {

                if(taken[i].find(j) == taken[i].end())
                    ans++;

                taken[i].insert(j);
            }

            sum += ara[j];
            if(sum >= lim)
                break;
        }
    }

    rep1(i, n) {

        ll b;
        rep0(j, 30) {
            if((ara[i] >> j) & 1) {
                b = j;
                break;
            }
        }

        ll sum = ara[i-1], lim = (1LL << (b+1));
        for(ll j = i-2; j >= 1; j--) {

            if((ara[j] ^ ara[i]) == sum) {

                if(taken[j].find(i) == taken[j].end())
                    ans++;

                taken[j].insert(i);
            }

            sum += ara[j];
            if(sum >= lim)
                break;
        }
    }

    cout << ans << EL;

    return 0;
}
