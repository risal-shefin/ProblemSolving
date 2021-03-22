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
#define dbg(x) {++recur_depth; auto x_=x; --recur_depth; SYS_COL; cerr<<string(recur_depth, '\t')<<"\e[91m"<<__func__<<":"<<__LINE__<<"\t"<<#x<<" = "<<x_<<"\e[39m"<<endl;}
#else
#define dbg(x)
#endif
template<typename Ostream, typename Cont>
typename enable_if<is_same<Ostream,ostream>::value, Ostream&>::type operator<<(Ostream& os,  const Cont& v){
	os<<"[";
	for(auto& x:v){os<<x<<", ";}
	return os<<"]";
}
template<typename Ostream, typename ...Ts>
Ostream& operator<<(Ostream& os,  const pair<Ts...>& p){
	return os<<"{"<<p.first<<", "<<p.second<<"}";
}

// === Debug macro ends here ===

#define ff first
#define ss second

const ll sz = 605, esz = sz*sz;
ll d[sz][sz], f[sz], ini[sz], n, m, q;
bitset <esz> useful;

struct Edge {
    int u, v, w;
} edge[esz], qry[esz];

void solve(ll src)
{
    for1(i, n) f[i] = ini[i] = inf;

    for1(i, q) {
        ll u = qry[i].u, v = qry[i].v, l = qry[i].w;
        if(v == src)
            swap(u, v);

        if(u != src)
            continue;

        ini[v] = min(ini[v], -l);
    }

    for1(i, n) {
        if(ini[i] == inf)
            continue;

        for1(j, n)
            f[j] = min(f[j], ini[i] + d[j][i]);
    }

    for1(i, m) {
        if(f[ edge[i].v ] <= -d[src][edge[i].u]-edge[i].w)
            useful[i] = 1;
    }
    //dbg(mp(src,f[4]));
}

int main()
{
    fastio;

    cin >> n >> m;

    for1(i, n)
        for1(j, n)
            d[i][j] = (i==j)? 0 : inf;

    for1(i, m) {
        ll u, v, w;
        cin >> u >> v >> w;

        edge[i] = {u, v, w};

        d[u][v] = d[v][u] = min(d[u][v], w);
    }

    for1(w, n)
        for1(u, n)
            for1(v, n)
                d[u][v] = min(d[u][v], d[u][w] + d[w][v]);

    cin >> q;
    for1(i, q)
        cin >> qry[i].u >> qry[i].v >> qry[i].w;

    for1(i, n)
        solve(i);

    cout << useful.count() << EL;

    return 0;
}
