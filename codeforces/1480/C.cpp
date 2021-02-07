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

ll n;

ll getVal(ll pos)
{
    ll ret;
    cout << "? " << pos << endl;
    cin >> ret;
    return ret;
}

ll ask(ll pos)
{
    ll v0 = inf, v1, v2 = inf;

    if(pos-1 >= 1)
        v0 = getVal(pos-1);
    if(pos+1 <= n)
        v2 = getVal(pos+1);

    v1 = getVal(pos);

    if(v0 > v1 && v1 < v2)
        return 0;
    if(v0 > v1 && v1 > v2)
        return -1;
    if(v0 < v1 && v1 < v2)
        return 1;
    if(v0 < v1 && v1 > v2)
        return 1;
}

int main()
{
    fastio;
    cin >> n;

    if(ask(1) == 0) {
        cout << "! 1" << endl;
        return 0;
    }
    if(ask(n) == 0) {
        cout << "! " << n << endl;
        return 0;
    }

    ll lo = 1, hi = n, ret;
    while(lo <= hi) {
        ll mid = lo+hi >> 1;

        ll got = ask(mid);

        if(got == 1) {
            hi = mid-1;
        }
        else if(got == -1) {
            lo = mid+1;
        }
        else {
            ret = mid;
            break;
        }
    }

    cout << "! " << ret << endl;

    return 0;
}
