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
vector <ll> g[sz];
vector < vector <int> > sub2;
unordered_set <int> track[sz];

struct info {
    int u, cnt;
};
const bool operator <(const info &a, const info &b) {
    if(a.cnt == b.cnt)
        return a.u < b.u;
    return a.cnt < b.cnt;
}

set <info> sub1;
ll cnt[sz];

void clr(ll n) {
    for1(i, n) g[i].clear(), track[i].clear();
    sub1.clear(), sub2.clear();
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n, m, k;
        sl(n), sl(m), sl(k);

        for1(i, m) {
            ll u, v;
            sl(u), sl(v);

            g[u].pb(v);
            g[v].pb(u);

            track[u].insert(v);
            track[v].insert(u);
        }
        for1(i, n) cnt[i] = g[i].size(), sub1.insert({i, cnt[i]});

        while(!sub1.empty()) {
            info got = *sub1.begin();
            if(got.cnt >= k)
                break;

            sub1.erase(got);

            vector <int> tmp;
            if(got.cnt == k-1)  tmp.pb(got.u);

            for(ll &v : g[got.u]) {

                auto it = sub1.find({v, cnt[v]});
                if(it == sub1.end())
                    continue;

                sub1.erase(it);
                cnt[v]--;
                sub1.insert({v, cnt[v]});

                if(got.cnt == k-1) tmp.pb(v);
            }

            if(!tmp.empty() && tmp.size() <= 500) sub2.pb(tmp);
        }

        if(!sub1.empty()) {
            pf("1 %lld\n", (ll)sub1.size());
            for(const info &got : sub1)
                pf("%d ", got.u);
            pn;

            clr(n);
            continue;
        }

        bool done = 0;
        for(vector <int> &lst : sub2) {

            bool ok = 1;

            for(int &u : lst) {

                for(int &v : lst) {

                    if(u == v)
                        continue;

                    if(track[u].find(v) == track[u].end()) {
                        ok = 0;
                        break;
                    }
                }
                if(!ok) break;
            }

            if(ok) {
                done = 1;
                pf("2\n");
                for(int &u : lst) pf("%d ", u);
                pn;

                break;
            }
        }

        if(!done) pf("-1\n");
        clr(n);
    }

    return 0;
}
