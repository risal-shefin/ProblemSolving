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
#ifdef LOCALXOX
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

const ll sz = 1e5 + 10;
vector <pll> g[sz];
unordered_set <int> track[sz];
unordered_map <int, vector<int>> g2[sz];
ll dist[sz], enq[sz];
queue <int> q;

void go_with_free(ll u, ll com, ll cst)
{
    if(!enq[u]) {
        q.push(u);
        enq[u] = 1;
    }

    vector <int> &lst = g2[u][com];
    for(auto &v: lst) {

        if(dist[v] == -1) {
            dist[v] = cst;

            track[v].insert(com);
            go_with_free(v, com, cst);
        }
        else if(dist[v] == cst && track[v].find(com) == track[v].end()) {
            track[v].insert(com);
            go_with_free(v, com, cst);
        }
    }
}

int main()
{
    ll n, m;
    cin >> n >> m;

    for1(i, m) {
        ll u, v, c;
        sl(u), sl(v), sl(c);

        g[u].pb({v, c});
        g[v].pb({u, c});

        g2[u][c].pb(v);
        g2[v][c].pb(u);
    }

    ms(dist, -1);

    q.push(1);
    dist[1] = 0;

    while(!q.empty()) {
        ll u = q.front();
        q.pop();

        for(auto &[v, c] : g[u]) {
            if(track[u].find(c) != track[u].end())
                continue;

            if(dist[v] == -1) {
                dist[v] = dist[u] + 1;

                track[v].insert(c);
                go_with_free(v, c, dist[v]);
            }
            else if(dist[u] + 1 == dist[v] && track[v].find(c) == track[v].end()) {

                track[v].insert(c);
                go_with_free(v, c, dist[v]);
            }
        }
    }

    cout << dist[n] << EL;

    return 0;
}
