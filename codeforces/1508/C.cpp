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

struct Edge {
    int u, v, w;
    const bool operator <(const Edge &rhs) {
        return w < rhs.w;
    }
} ed[sz];

unordered_set <int> lst[sz];
set <int> alive;
ll par[sz][2], extra, ans;

ll findp(ll u, bool f)
{
    if(par[u][f] == u)
        return u;
    return par[u][f] = findp(par[u][f], f);
}

bool Union(ll u, ll v, bool f)
{
    ll pu = findp(u, f), pv = findp(v, f);
    if(pu == pv)
        return false;

    par[pv][f] = pu;
    return true;
}

void dfs(ll u)
{
    alive.erase(u);

    for(ll v = 1; ; v++) {

        auto it = alive.lower_bound(v);
        if(it == alive.end())
            return;

        v = *it;

        if(lst[u].find(v) == lst[u].end()) {
            Union(u, v, 0);
            dfs(v);
            extra--;
        }
    }
}

int main()
{
    ll n, m, xr = 0;
    cin >> n >> m;

    for1(i, m) {
        si(ed[i].u), si(ed[i].v), si(ed[i].w);
        xr ^= ed[i].w;

        lst[ed[i].u].insert(ed[i].v);
        lst[ed[i].v].insert(ed[i].u);
    }
    sort(ed+1, ed+m+1);

    extra = n*(n-1)/2 - m;

    for1(i, n) {
        par[i][0] = par[i][1] = i;
        alive.insert(i);
    }

    while(!alive.empty()) {
        dfs(*alive.begin());
    }

    if(extra > 0) xr = 0;

    for1(i, m) {
        if(Union(ed[i].u, ed[i].v, 0)) {
            ans += ed[i].w;
            Union(ed[i].u, ed[i].v, 1);
        }
        else if(Union(ed[i].u, ed[i].v, 1))
            xr = min(xr, (ll)ed[i].w);
    }

    cout << ans+xr << EL;

    return 0;
}
