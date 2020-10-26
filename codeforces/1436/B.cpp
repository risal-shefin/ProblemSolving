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

bool isPrime(ll n) {
    for(ll i = 2; i *i <= n; i++) {
        if(n % i == 0)
            return 0;
    }
    return 1;
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n; sl(n);

        ll val;
        for(ll i = 2; ; i++) {
            if(!isPrime(i))
                continue;

            if(i <= n-1)
                continue;

            val = i - (n-1);
            if(!isPrime(val)) break;
        }

        for1(i, n) {
            for1(j, n) {
                if(j != 1) pf(" ");

                if(i == j) pf("%lld", val);
                else pf("1");
            }
            pn;
        }
    }

    return 0;
}
