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
ll ara[sz], csum[sz], fact[20], start, n;
bool used[sz];

void gen(ll pos, ll p)
{
    if(pos > n) return;

    for(ll num = start, i = 1; num <= n; num++, i++) {

        if(used[num])
            continue;

        ll perm = fact[n-pos];
        if(perm < p)
            p -= perm;
        else {
            ara[pos] = num, used[num] = 1;
            gen(pos+1, p);

            return;
        }
    }
}

int main()
{
    fact[0] = 1;
    for1(i, 15) fact[i] = fact[i-1] * i;

    ll q, perm = 1;
    cin >> n >> q;

    for1(i, n) ara[i] = i, csum[i] = ara[i] + csum[i-1];

    start = max(1LL, n-14);

    for1(i, q) {
        ll op; sl(op);

        if(op == 1) {
            ll l, r;
            sl(l), sl(r);

            ll ans = 0;
            if(l < start) ans += csum[min(r,start-1)] - csum[l-1];

            for(ll j = max(start, l); j <= r; j++) ans += ara[j];

            pf("%lld\n", ans);
        }
        else {
            ll x; sl(x);

            perm += x;
            gen(start, perm);

            for(ll j = start; j <= n; j++) used[j] = 0;
        }
    }

    return 0;
}
