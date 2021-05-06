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

const ll sz = 2e5 + 10;
ll par[sz], siz[sz], ans[sz];
pii qry[sz];
vector <pii> edge[sz];

ll findp(ll u)
{
    if(par[u] == u)
        return u;
    return par[u] = findp(par[u]);
}

int main()
{
    ll n, q;
    cin >> n >> q;

    for1(i, n-1) {
        ll u, v, w;
        sl(u), sl(v), sl(w);

        edge[w].pb(mp(u, v));
    }

    for1(i, n) par[i] = i, siz[i] = 1;

    for1(i, q) {
        si(qry[i].ff);
        qry[i].ss = i;
    }
    sort(qry+1, qry+q+1);

    ll way = 0, prv = 0;

    for1(i, q) {
        ll w = qry[i].ff, id = qry[i].ss;

        for(ll j = prv+1; j <= w; j++) {
            for(pii &e : edge[j]) {
                ll u = findp(e.ff), v = findp(e.ss);

                way = way - siz[u]*(siz[u]-1)/2 - siz[v]*(siz[v]-1)/2;

                par[v] = u;
                siz[u] += siz[v];

                way = way + siz[u]*(siz[u]-1)/2;
            }
        }

        ans[id] = way;
        prv = w;
    }

    for1(i, q) pf("%lld ", ans[i]);
    pn;

    return 0;
}
