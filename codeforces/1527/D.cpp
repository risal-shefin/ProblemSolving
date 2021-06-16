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

// === DEBUG MACRO STARTS HERE === //
#ifndef ONLINE_JUDGE
#define DEBUG
#define SYS_COL system("COLOR")
#endif

int recur_depth = 0;
#ifdef DEBUG
#define dbg(x) {++recur_depth; auto x_=x; --recur_depth; SYS_COL; \
                cerr<<string(recur_depth, '\t')<<"\e[91m"<<__func__<<":" \
                <<__LINE__<<"\t"<<#x<<" = "<<x_<<"\e[39m"<<endl;}

template<typename Ostream, typename Cont>
typename enable_if<is_same<Ostream,ostream>::value,
            Ostream&>::type operator<<(Ostream& os,  const Cont& v) {
	os<<"[";
	for(auto& x:v){os<<x<<", ";}
	return os<<"]";
}
template<typename Ostream, typename ...Ts>
Ostream& operator<<(Ostream& os,  const pair<Ts...>& p){
	return os<<"{"<<p.first<<", "<<p.second<<"}";
}
#else
#define dbg(x)
#endif
// === DEBUG MACRO ENDS HERE === //

#define ff first
#define ss second

const ll sz = 2e5 + 10;
vector <int> g[sz];
ll sub[sz], par[sz], vis[sz], start[sz], stop[sz], tim;

void dfs(ll u, ll p)
{
    start[u] = ++tim;
    sub[u] = 1, par[u] = p;

    for(int &v : g[u]) {
        if(v == p)
            continue;

        dfs(v, u);
        sub[u] += sub[v];
    }
    stop[u] = tim;
}

inline bool isPar(ll u, ll p) {
    return (start[p] <= start[u] && stop[p] >= stop[u]);
}

void goPar(ll u)
{
    vis[u] = 1;

    if(par[u] != -1 && !vis[ par[u] ])
        goPar(par[u]);
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n; sl(n);

        for1(i, n-1) {
            ll u, v;
            sl(u), sl(v);

            g[u].pb(v);
            g[v].pb(u);
        }

        tim = 0;
        dfs(0, -1);
        par[n] = -1;

        ll l = 0, r = 0, fp = -1, sp = -1, ok = 1, mexi;

        for(ll x = 0; x <= n; x++) {

            if(x == 0) {
                ll ans = 0;

                for(int &v : g[0])
                    ans += (sub[v]*(sub[v]-1))/2;

                pf("%lld ", ans);
                mexi = n*(n-1)/2 - ans, vis[0] = 1;
                continue;
            }

            if(vis[x] || !ok) {
                pf("0 ");
                continue;
            }

            if(x == n) {
                pf("%lld ", mexi);
                continue;
            }
            if(isPar(x, l)) l = x;
            else if(isPar(x, r)) r = x;
            else {
                pf("%lld ", mexi);
                ok = 0;
                continue;
            }

            goPar(x);

            if(fp==-1) {
                for(int &v : g[0]) {
                    if(vis[v]) {
                        fp = v;
                        break;
                    }
                }
            }

            if(sp == -1 && r != 0) {
                for(int &v : g[0]) {
                    if(vis[v] && v != fp) {
                        sp = v;
                        break;
                    }
                }

                if(sp == -1) {
                    pf("%lld ", mexi);
                    ok = 0;
                    continue;
                }
            }

            ll ans = 0;
            if(r != 0) {
                ans = mexi - sub[l]*sub[r];
                mexi = sub[l]*sub[r];
            }
            else {
                ll rest = n-sub[fp];
                ans = mexi - sub[l]*rest;
                mexi = sub[l]*rest;
            }
            pf("%lld ", ans);
        }
        pn;

        for0(i, n) g[i].clear(), vis[i] = 0;
    }

    return 0;
}
