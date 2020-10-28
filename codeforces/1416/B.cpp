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

const ll sz = 1e4 + 10;
ll ara[sz];

struct info {
    int i, j, x;
};
vector <info> ans;

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ans.clear();

        ll n; sl(n);

        ll sum = 0;
        for1(i, n) {
            sl(ara[i]);
            sum += ara[i];
        }

        if(sum % n != 0) {
            pf("-1\n");
            continue;
        }

        for(ll i = 2; i <= n; i++) {

            if(ara[i] % i != 0) {
                ll need = i-(ara[i] % i);
                ara[i] += need, ara[1] -= need;
                ans.pb({1, i, need});
            }

            ll x = ara[i] / i;

            ara[i] -= x*i, ara[1] += x*i;
            ans.pb({i, 1, x});
        }

        ll eq = sum / n;
        for(ll i = 2; i <= n; i++) {
            if(ara[i] == eq)
                continue;

            ll need = eq - ara[i];
            ans.pb({1, i, need});
        }

        pf("%lld\n", (ll)ans.size());
        for(info &Info : ans)
            pf("%d %d %d\n", Info.i, Info.j, Info.x);
    }

    return 0;
}
