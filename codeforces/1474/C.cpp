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

const ll sz = 2e3 + 10;

struct info {
    int idx, val;
    const bool operator <(const info &b) {
        return val < b.val;
    }
} ara[sz];
bool take[sz];

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n; sl(n);
        n = 2*n;

        for1(i, n) {
            si(ara[i].val);
            ara[i].idx = i;
        }
        sort(ara+1, ara+n+1);

        bool ok = 0;
        ll d;

        for(ll i = n-1; i >= 1; i--) {

            multiset <int> lst;

            for1(j, n) {
                if(j != i && j != n)
                    lst.insert(ara[j].val);
            }

            ll now = ara[n].val, done = 1;

            while(!lst.empty()) {

                ll val = *lst.rbegin();
                lst.erase(lst.find(val));
//                if(i == 1)
//                    cout << val << endl;

                auto it = lst.find(now-val);

                if(it == lst.end()) {
                    done = 0;
                    break;
                }

                lst.erase(it);
                now = val;
            }

            if(done) {
                ok = 1, d = i;
                break;
            }
        }

        if(!ok) {
            pf("NO\n");
            continue;
        }

        pf("YES\n%d\n", ara[d].val + ara[n].val);

        for1(i, n) take[i] = 0;
        pf("%d %d\n", ara[d].val, ara[n].val);

        take[n] = take[d] = 1;
        ll now = ara[n].val;

        rep1(i, n) {
            if(take[i])
                continue;

            ll got;
            for(ll j = i-1; j >= 1; j--) {

                if(take[j])
                    continue;

                if(ara[i].val + ara[j].val == now) {
                    got = ara[j].val;
                    take[j] = 1;
                    break;
                }
            }

            pf("%d %d\n", ara[i].val, got);
            now = ara[i].val;
        }
    }

    return 0;
}
