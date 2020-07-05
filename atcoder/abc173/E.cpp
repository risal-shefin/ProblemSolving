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
#define inf (1LL << 62)
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

const ll sz = 2e5 + 10, mod = 1e9 + 7;
ll ara[sz];

int main()
{
    ll n, k;
    cin >> n >> k;
    for1(i, n) sl(ara[i]);

    sort(ara+1, ara+n+1);

    if(ara[n] == 0 && k % 2 != 0) {
        cout << 0 << endl;
        return 0;
    }

    if(ara[n] < 0 && k % 2 != 0) {
        ll mul = 1;
        for(ll i = n, j = 1; i >= 1 && j <= k; i--, j++) mul = (mul * ara[i]) % mod;

        mul += mod;
        cout << mul << endl;
        return 0;
    }

    ll ptr1 = 1, ptr2 = n, done = 0, mul = 1;
    if(k & 1) {
        mul = (mul * ara[ptr2]) % mod;
        ptr2--, done++;
    }

    while(done < k) {
        ll mul1 = ara[ptr1] * ara[ptr1 + 1], mul2 = ara[ptr2] * ara[ptr2-1];

        if(mul2 >= mul1) {
            mul2 %= mod;
            mul = (mul * mul2) % mod;
            done += 2, ptr2 -= 2;
        }
        else {
            mul1 %= mod;
            mul = (mul * mul1) % mod;
            done += 2, ptr1 += 2;
        }
    }

    if(mul < 0) mul += mod;
    cout << mul << endl;

    return 0;
}
