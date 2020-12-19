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

const ll MAX_N = sqrtl(1e10) + 10;
bool mark[MAX_N];
vector <int> prime;

int main()
{
    for(ll i = 2; i < MAX_N; i++) {
        if(!mark[i]) {
            for(ll j = i*i; j < MAX_N; j += i)
                mark[j] = 1;

            prime.pb(i);
        }
    }

    ll t;
    cin >> t;

    while(t--) {
        ll n; sl(n);

        ll ap, cnt = 0;

        vector <ll> lst;
        for(int &p : prime) {

            if((ll)p*p > n)
                break;

            if(n % p != 0)
                continue;

            ll ase = 0, mul = 1;
            while(n % p == 0) ase++, n /= p, mul *= p;

            if(ase > cnt)
                ap = p, cnt = ase;

            lst.pb(mul);
        }
        if(n > 1) {
            if(1 > cnt)
                ap = n, cnt = 1;

            lst.pb(n);
        }

        pf("%lld\n", cnt);
        for1(i, cnt) {
            if(i != cnt) {
                pf("%lld ", ap);
                continue;
            }

            ll mul = ap;
            for(ll &f : lst) {
                if(f % ap != 0)
                    mul *= f;
            }

            pf("%lld\n", mul);
        }
    }

    return 0;
}