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

ll ask(ll l, ll r)
{
    cout << "? " << l << " " << r << endl;
    ll ret; cin >> ret;
    return ret;
}

int main()
{
    fastio;
    ll n; cin >> n;

    ll p = ask(1, n);

    ll rgt = 1, ret;
    if(p != 1 && ask(1, p) == p)
        rgt = 0;

    if(!rgt) {
        ll lo = 1, hi = p-1;

        while(lo <= hi) {
            ll mid = lo+hi >> 1;

            ll got = ask(mid, p);
            if(got != p)
                hi = mid-1;
            else {
                ret = mid;
                lo = mid+1;
            }
        }
    }
    else {
        ll lo = p+1, hi = n;

        while(lo <= hi) {
            ll mid = lo+hi >> 1;

            ll got = ask(p, mid);
            if(got != p)
                lo = mid+1;
            else {
                ret = mid;
                hi = mid-1;
            }
        }
    }

    cout << "! " << ret << endl;

    return 0;
}
