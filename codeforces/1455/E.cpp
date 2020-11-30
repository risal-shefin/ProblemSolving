// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
using namespace std;

#define ll int
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

#define LL long long

const ll MAX_X = 1e9+5, MAX_Y = 1e9+5;
ll xx[4], yy[4], cx[16], cy[16];
ll perm[4];

inline LL calc(const ll x, const ll y, const ll len)
{
    LL ret = 0;
    ll px = x, py = y, id = perm[0];
    ret += abs((LL)xx[id] - px) + abs((LL)yy[id] - py);

    px = x, py = y+len, id = perm[1];
    ret += abs((LL)xx[id] - px) + abs((LL)yy[id] - py);

    px = x+len, py = y+len, id = perm[2];
    ret += abs((LL)xx[id] - px) + abs((LL)yy[id] - py);

    px = x+len, py = y, id = perm[3];
    ret += abs((LL)xx[id] - px) + abs((LL)yy[id] - py);

    return ret;
}

inline LL selL(const ll x, const ll y, const ll st)
{
    ll lo = 0, hi = MAX_X;
    LL ret = inf;
    while(lo < hi) {
        ll mid = (lo+hi) >> 1;

        LL got1 = calc(x, y, st*mid), got2 = calc(x, y, st*(mid+1));

        if(got1 < got2) {
            hi = mid;
            ret = min(ret, got1);
        }
        else {
            lo = mid+1;
            ret = min(ret, got2);
        }
    }
    ret = min(ret, calc(x, y, lo));

    return ret;
}

int main()
{
    fastio;
    ll t;
    cin >> t;

    while(t--) {

        for0(i, 4) {
            cin >> xx[i] >> yy[i];
            perm[i] = i;
        }

        ll idx = 0, idy = 0;

        for0(i, 4)
            for0(j, 4)
                cx[idx++] = xx[i], cy[idy++] = yy[j];

        LL ans = inf;

        do {
            for0(i, 16) {
                ans = min(ans, selL(cx[i], cy[i], 1) );
                ans = min(ans, selL(cx[i], cy[i], -1) );
            }

        } while(next_permutation(perm, perm+4));

        cout << ans << EL;
    }

    return 0;
}

