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

// === Debug macro starts here ===
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
// === Debug macro ends here ===

#define ff first
#define ss second

const ll sz = 1e5 + 10;
vector <ll> g[sz];
ll c[sz];
pll enp[sz];

struct info {
    int a, b, c, d;
};
vector <info> ans;

const bool cmp(const ll &a, const ll &b)
{
    return c[a] < c[b];
}

pll dfs(ll u, ll p)
{
    ll child = 0, rmv = 0;
    pll leaf;

    for(ll &v : g[u]) {
        if(v == p)
            continue;

        pll got = dfs(v, u);
        enp[v] = got;
    }
    sort(all(g[u]), cmp);

    for(ll &v : g[u]) {
        if(v == p)
            continue;

        child++;
        pll got = enp[v];
        if(child == 1) leaf = got;

        if(child-rmv <= 2) {
            if(c[v] >= 2) {
                if(child == 1) {
                    ans.pb({u, v, u, got.ff});
                    leaf.ff = got.ss;
                }
                else {
                    ans.pb({u, v, leaf.ss, got.ff});
                    rmv++;

                    if(leaf.ff == leaf.ss)
                        leaf.ff = leaf.ss = got.ss;
                    else
                        leaf.ss = got.ss;
                }
            }
            else
                leaf.ss = got.ss;
        }
        else {
            ans.pb({u, v, leaf.ss, got.ff});
            if(c[v] == 1) got.ss = v;

            if(leaf.ff == leaf.ss)
                leaf.ff = leaf.ss = got.ss;
            else
                leaf.ss = got.ss;

            rmv++;
        }
    }

    c[u] = child - rmv;

    if(g[u].size() == 1)
        return mp(u, u);

    return leaf;
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n;
        sl(n);

        for1(i, n-1) {
            ll u, v;
            sl(u), sl(v);

            g[u].pb(v);
            g[v].pb(u);
        }

        ans.clear();
        dfs(1, -1);

        pf("%lld\n", (ll)ans.size());

        for(info &x : ans)
            pf("%d %d %d %d\n", x.a, x.b, x.c, x.d);

        for1(i, n) g[i].clear();
    }

    return 0;
}

