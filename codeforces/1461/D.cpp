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
vector <ll> lst;

void solve(ll l, ll r)
{
    if(l > r)
        return;
    if(l == r) {
        lst.pb(ara[l]);
        return;
    }

    ll sum = 0, ptr = l, mid = (ara[l] + ara[r]) >> 1;

    for(ll i = l; i <= r; i++) {
        sum += ara[i];

        if(ara[i] <= mid)
            ptr = i;
    }

    lst.pb(sum);
    if(ptr == r) return;

    solve(l, ptr), solve(ptr+1, r);
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n, q;
        sl(n), sl(q);

        for1(i, n)
            sl(ara[i]);

        sort(ara+1, ara+n+1);

        lst.clear();
        lst.reserve(n*20);

        solve(1, n);
        sort(all(lst));

        while(q--) {
            ll s; sl(s);
            ll pos = lower_bound(all(lst), s) - lst.begin();

            if(pos == lst.size() || lst[pos] != s)
                pf("No\n");
            else
                pf("Yes\n");
        }
    }

    return 0;
}
