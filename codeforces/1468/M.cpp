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

const ll sz = 3e5 + 10, ssz = 1e5+10;
vector <ll> g[sz], g2[sz], st[ssz];
ll deg[sz], mark[sz];

struct info {
    ll u, v;
} check[sz];

int main()
{
    fastio;

    ll t;
    cin >> t;
    while(t--) {
        ll n; cin >> n;

        vector <int> num;

        for1(i, n) {
            ll k; cin >> k;

            st[i].clear();
            st[i].reserve(k);

            for1(j, k) {
                ll x; cin >> x;
                st[i].pb(x);

                num.pb(x);
            }
        }
        sort(all(num));
        num.erase(unique(all(num)), num.end());

        ll tot = n+num.size();

        for1(i, tot) {
            g[i].clear(), g2[i].clear();
            deg[i] = mark[i] = 0;
            check[i].u = check[i].v = -1;
        }

        for1(i, n) {

            for(ll &x : st[i]) {
                ll p = lower_bound(all(num), x) - num.begin();
                p++;

                g[i].pb(n+p);
                g[n+p].pb(i);

                deg[i]++, deg[n+p]++;
            }
        }

        for1(i, n) {

            for(ll &v : g[i]) {

                if(deg[i] >= deg[v])
                    g2[i].pb(v);
                else
                    g2[v].pb(i);
            }
        }

        info ans = {-1, -1};

        for1(u, tot) {

            for(ll &v : g2[u]) {

                for(ll &w : g[v]) {

                    if(w == v || w == u)
                        continue;
                    //cout << u << " " << v << " " << w << endl;

                    if(check[w].u == u) {

                        if(u <= n) ans.u = u;
                        else if(v <= n) ans.u = v;
                        else ans.u = w;

                        if(check[w].v <= n) ans.v = check[w].v;
                        else if(w <= n) ans.v = w;
                        else ans.v = v;

                        break;
                    }

                    if(ans.u != -1)
                        break;

                    check[w].u = u, check[w].v = v;
                }

                if(ans.u != -1)
                    break;
            }

            if(ans.u != -1)
                break;
        }

        if(ans.u == -1) cout << -1 << EL;
        else cout << ans.u << " " << ans.v << EL;
    }

    return 0;
}
