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

const ll sz = 1e6 + 10;
ll p[sz], pos[sz], exist[sz], erased[sz], n, k;
set <int> posLst;

void upd(ll idx)
{
    while(idx <= n) {
        erased[idx]++;
        idx += (idx&-idx);
    }
}

ll query(ll idx)
{
    ll ret = 0;
    while(idx > 0) {
        ret += erased[idx];
        idx -= (idx&-idx);
    }
    return ret;
}

int main()
{
    sl(n), sl(k);

    for1(i, n) {
        sl(p[i]);
        pos[ p[i] ] = i;
    }

    for1(i, k) {
        ll inp; sl(inp);
        exist[inp] = 1;
    }

    ll ans = 0;
    posLst.insert(0), posLst.insert(n+1);

    for1(i, n) {

        if(exist[i]) {
            posLst.insert(pos[i]);
            continue;
        }

        auto it = posLst.lower_bound(pos[i]);
        ll rgt = *it, lft = *(--it);

        ans += (rgt-lft-1) - (query(rgt-1) - query(lft));

        upd(pos[i]);
    }

    cout << ans << EL;

    return 0;
}
