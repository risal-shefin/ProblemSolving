// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
using namespace std;

#define ll int
#define ull unsigned long long
#define dd double
#define ld long double
#define sl(n) scanf("%d", &n)
#define si(n) scanf("%d", &n)
#define sd(n) scanf("%lf", &n)
#define pll pair <ll, ll>
#define pii pair <int, int>
#define mp make_pair
#define pb push_back
#define all(v) v.begin(), v.end()
#define inf (1LL << 30)
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

const ll sz = 5e5 + 10;
char s[sz];
ll len[sz], nxt[sz], tree[4*sz];

void upd(ll lo, ll hi, ll idx, ll v, ll node)
{
    if(lo > idx || hi < idx)
        return;
    if(lo == hi) {
        tree[node] = v;
        return;
    }

    ll mid = lo+hi>>1, lft=node<<1, rgt=lft|1;

    upd(lo, mid, idx, v, lft);
    upd(mid+1, hi, idx, v, rgt);

    tree[node] = min(tree[lft], tree[rgt]);
}

ll query(ll lo, ll hi, ll l, ll r, ll node)
{
    if(lo > r || hi < l || l > r)
        return inf;
    if(lo >= l && hi <= r)
        return tree[node];

    ll mid = lo+hi>>1, lft=node<<1, rgt=lft|1;
    return min(query(lo, mid, l, r, lft),
               query(mid+1, hi, l, r, rgt));
}

inline LL sumOneN(LL l, LL r) {
    return (r * (r+1)) / 2 - (l * (l+1)) / 2;
}

int main()
{
    for0(i, 4*sz) tree[i] = inf;

    ll n; sl(n);
    scanf("%s", s+1);

    rep1(i, n) {

        if(s[i] == '0') {
            len[i] = 0, nxt[i] = tree[1];
            continue;
        }

        ll start = i, stop = i, now = 0;

        for(ll j = i; j >= 1; j--) {

            if(s[j] == '0')
                break;

            start = j, len[j] = ++now;
            nxt[j] = query(1, n, len[j]+1, n, 1);
        }

        upd(1, n, len[start], start, 1);
        i = start;
    }

    LL ans = 0;

    for1(i, n) {
        ll mx = len[i];
        ans += sumOneN(0, mx);

        ll now = i, ptr = i+mx;

        while(1) {

            ll nxtStart = min(n+1, nxt[now]);
            ans += (LL)(nxtStart - ptr) * mx;

            if(nxtStart > n) break;

            ans += (LL)mx*mx + sumOneN(mx, len[nxtStart]), mx = len[nxtStart];
            now = nxtStart, ptr = nxtStart + mx;
        }
    }

    cout << ans << EL;

    return 0;
}
