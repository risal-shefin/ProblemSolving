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

const ll sz = 2e5 + 10, mod = 998244353;
ll ara[sz], b[sz], pos[sz], mark[sz];

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n, k;
        sl(n), sl(k);

        set <int> lst;

        for1(i, n) {
            sl(ara[i]);
            pos[ ara[i] ] = i, mark[i] = 0;

            lst.insert(i);
        }

        for1(i, k) {
            sl(b[i]);

            mark[ pos[ b[i] ] ] = 1;
        }

        ll way = 1;

        for1(i, k) {

            ll now = b[i];

            auto it = lst.find(pos[now]);
            auto it1 = it, it2 = it;

            ll p = 0, f = -1, s = -1;

            if(it != lst.begin()) {
                it1--;

                if(!mark[*it1]) {
                    p++;
                    f = *it1;
                }
            }

            it2++;
            if(it2 != lst.end()) {

                if(!mark[*it2]) {
                    p++;
                    s = *it2;
                }
            }

            if(p == 0) {
                way = 0;
                break;
            }

            way = (way * p) % mod;

            mark[ pos[now] ] = 0;
            if(f != -1) lst.erase(f);
            else lst.erase(s);
        }

        pf("%lld\n", way);
    }

    return 0;
}
