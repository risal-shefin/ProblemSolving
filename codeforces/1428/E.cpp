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

struct info {
    ll saved, siz, cut;
};
const bool operator <(const info &a, const info &b) {
    return a.saved < b.saved;
}
priority_queue <info> pq;

inline ll sq(ll num) {return num*num;}

inline ll tim(ll siz, ll cut)
{
    ll nsiz = siz / cut, rem = siz%cut;
    ll tim1 = (cut - rem) * sq(nsiz);
    ll tim2 = rem * sq(nsiz+1);
    return tim1 + tim2;
}

inline ll calc_saved(ll siz, ll cut, ll nxtCut) {
    return tim(siz, cut) - tim(siz, nxtCut);
}

int main()
{
    ll n, k, ans = 0;
    cin >> n >> k;

    for1(i, n) {
        ll inp; sl(inp);
        ans += sq(inp);
        pq.push({calc_saved(inp, 1, 2), inp, 2});
    }

    for(ll j = n+1; j <= k; j++) {
        info u = pq.top();
        pq.pop();

        ans -= u.saved;
        pq.push({calc_saved(u.siz, u.cut, u.cut+1), u.siz, u.cut+1});
    }

    cout << ans << EL;

    return 0;
}
