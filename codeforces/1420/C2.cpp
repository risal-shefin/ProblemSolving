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

const ll sz = 3e5 + 10;
ll ara[sz], n, ans;

inline bool peak(ll idx)
{
    if(ara[idx] > ara[idx-1] && ara[idx] > ara[idx+1])
        return 1;

    return 0;
}

inline bool down(ll idx)
{
    if(ara[idx] < ara[idx-1] && ara[idx] < ara[idx+1])
        return 1;

    return 0;
}

inline void add(ll idx)
{
    if(idx == 0 || idx == n+1) return;

    if(peak(idx)) ans += ara[idx];
    else if(down(idx)) ans -= ara[idx];
}

inline void rmv(ll idx)
{
    if(idx == 0 || idx == n+1) return;

    if(peak(idx)) ans -= ara[idx];
    else if(down(idx)) ans += ara[idx];
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll q;
        sl(n), sl(q);

        for1(i, n) sl(ara[i]);

        ara[0] = ara[n+1] = ans = 0;

        for1(i, n) {
            if(peak(i)) ans += ara[i];
            else if(down(i)) ans -= ara[i];
        }

        pf("%lld\n", ans);

        for1(i, q) {
            ll l, r;
            sl(l), sl(r);

            if(l == r) {
                pf("%lld\n", ans);
                continue;
            }

            rmv(l-1), rmv(l), rmv(l+1);
            if(l+1 < r) rmv(r);
            if(l+1 < r-1) rmv(r-1);
            rmv(r+1);

            swap(ara[l], ara[r]);

            add(l-1), add(l), add(l+1);
            if(l+1 < r) add(r);
            if(l+1 < r-1) add(r-1);
            add(r+1);

            pf("%lld\n", ans);
        }
    }

    return 0;
}

