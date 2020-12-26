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

const ll sz = 3e5 + 10;
vector <ll> g[sz], g2[sz], st[sz];
ll lst[sz], deg[sz], mark[sz];
pll check[sz];

bool cmp(const ll &a, const ll &b) {
    return deg[a] > deg[b];
}

int main()
{
    ll t;
    cin >> t;
    while(t--) {
        ll n; sl(n);

        vector <int> num;

        for1(i, n) {
            ll k; sl(k);

            st[i].clear();
            st[i].reserve(k);

            for1(j, k) {
                ll x; sl(x);
                st[i].pb(x);

                num.pb(x);
            }
        }
        sort(all(num));
        num.erase(unique(all(num)), num.end());

        ll tot = n+num.size();

        for1(i, tot) {
            g[i].clear(), g2[i].clear();
            deg[i] = mark[i] = 0, lst[i] = i;
            check[i] = {-1, -1};
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
        sort(lst+1, lst+tot+1, cmp);

        for1(i, tot) {
            ll u = lst[i];
            mark[u] = 1;

            for(ll &v : g[u]) {
                if(mark[v])
                    continue;

                g2[u].pb(v);
            }
        }

        pll ans = {-1, -1};

        for1(i, tot) {
            ll u = lst[i];
            //cout << u << endl;

            for(ll &v : g2[u]) {

                for(ll &w : g[v]) {

                    if(w == v || w == u)
                        continue;
                    //cout << u << " " << w << endl;

                    if(check[w].first == u) {

                        if(u <= n) ans.first = u;
                        else if(v <= n) ans.first = v;
                        else ans.first = w;

                        if(check[w].second <= n) ans.second = check[w].second;
                        else if(w <= n) ans.second = w;
                        else ans.first = v;

                        break;
                    }

                    if(ans.first != -1)
                        break;

                    check[w] = {u, v};
                }

                if(ans.first != -1)
                        break;
            }

            if(ans.first != -1)
                break;
        }

        if(ans.first == -1) pf("-1\n");
        else pf("%lld %lld\n", ans.first, ans.second);
    }

    return 0;
}
