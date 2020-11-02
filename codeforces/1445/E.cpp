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

const ll sz = 5e5 + 10;

vector <int> g[sz], gsame[sz], lst[sz];
vector <int> gnew[2*sz], clr, g2[2*sz];

ll col[sz], group[sz], compid[sz];
ll checker, col2[2*sz], invalid[sz];

void dfs_same(ll u, ll c, ll cid)
{
    col[u] = c, compid[u] = cid;

    for(int &v : gsame[u]) {

        if(col[v] != -1) {
            if(col[v] == c) checker = -1;
            continue;
        }

        dfs_same(v, c^1, cid);
    }
}

void dfs(ll u, ll c)
{
    col2[u] = c, clr.pb(u);

    for(int &v : gnew[u]) {

        if(col2[v] != -1) {
            if(col2[v] == c) checker = -1;
            continue;
        }

        dfs(v, c^1);
    }
}

int main()
{
    ll n, m, k;
    cin >> n >> m >> k;

    for1(i, n) {
        ll gp; sl(gp);

        group[i] = gp;
        lst[gp].pb(i);
    }

    for1(i, m) {
        ll u, v;
        sl(u), sl(v);

        if(group[u] == group[v]) {
            gsame[u].pb(v);
            gsame[v].pb(u);
        }

        g[u].pb(v);
        g[v].pb(u);

    }

    ll cid = 0, ans = 0, invTot = 0;
    ms(col, -1), ms(col2, -1);

    for1(i, k) {

        for(int &u : lst[i]) {
            if(col[u] != -1)
                continue;

            checker = 0;
            dfs_same(u, 0, ++cid);

            if(checker == -1) {
                invalid[i] = 1, invTot++;
                break;
            }
        }
    }

    for1(i, k) {
        if(invalid[i])
            continue;

        vector <int> clst;
        vector <pii> glst;

        for(int &u : lst[i]) {

            for(int &v : g[u]) {

                ll gp = group[v];
                if(invalid[gp] || gp == group[u])
                    continue;

                ll cv = 2*compid[v] + col[v];
                g2[cv].pb(u);

                glst.pb(mp(gp, cv));
                clst.pb(cv);
            }
        }

        sort(all(glst));
        glst.erase(unique(all(glst)), glst.end());

        ll bad = 0;

        for(ll i = 0; i < glst.size(); i++) {

            ll start = i, stop = i;

            for(ll j = i; j < glst.size(); j++) {

                if(glst[j].first != glst[i].first)
                    break;

                stop = j;
            }

            for(ll j = start; j <= stop; j++) {

                ll u = glst[j].second;

                for(int &v : g2[u]) {

                    ll cv = 2*compid[v] + col[v];

                    gnew[u].pb(cv);
                    gnew[cv].pb(u);

                    gnew[cv].pb(cv^1);
                    gnew[cv^1].pb(cv);
                }

                gnew[u].pb(u^1);
                gnew[u^1].pb(u);
            }

            for(ll j = start; j <= stop; j++) {

                ll u = glst[j].second;

                if(col2[u] != -1)
                    continue;

                checker = 0;
                dfs(u, 0);

                if(checker == -1) {
                    bad++;
                    break;
                }
            }

            for(ll j = start; j <= stop; j++) {

                ll u = glst[j].second;

                for(int &v : g2[u]) {

                    ll cv = 2*compid[v] + col[v];

                    gnew[cv].clear(), gnew[cv^1].clear();
                }

                gnew[u].clear(), gnew[u^1].clear();
            }

            for(int &u : clr) col2[u] = -1;
            clr.clear();

            i = stop;
        }

        ans += ((k-invTot) - bad - 1);

        for(int &cid : clst) g2[cid].clear();
    }

    cout << ans/2 << EL;

    return 0;
}


