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
#define inf (1<<30)
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

const ll sz = 1e5 + 50*1e5 + 10;
ll dist[sz], n, m;
set <int> wlst[100009];

struct info {
    ll u, v, w;
} ara[sz];

struct Edge {
    int v, w;
};
vector <Edge> g[sz];

const bool operator <(const Edge &a, const Edge &b) {
    return a.w > b.w;
}

inline ll sq(ll x) {return x*x;}

void dijkstra()
{
    for1(i, sz-1) dist[i] = inf;

    priority_queue <Edge> pq;
    pq.push({1, 0});
    dist[1] = 0;

    while(!pq.empty()) {
        Edge got = pq.top();
        pq.pop();

        if(dist[got.v] != got.w)
            continue;

        for(Edge &edge : g[ got.v ]) {

            if(dist[edge.v] > got.w + edge.w) {
                dist[edge.v] = got.w + edge.w;
                pq.push({edge.v, dist[edge.v]});
            }
        }
    }
}

void addEdge(ll u, ll v, ll w)
{
    ll vw = n+50*(v-1) + w;
    g[u].pb({vw, 0});

    for(const int &i : wlst[u]) {
        ll cst = sq(i+w), ui = n+50*(u-1) + i;
        g[ui].pb({v, cst});
    }
}

int main()
{
    fastio;

    cin >> n >> m;

    for1(i, m) {
        ll u, v, w;
        cin >> u >> v >> w;

        ara[i] = {u, v, w};

        wlst[u].insert(w);
        wlst[v].insert(w);
    }

    for1(i, m) {
        addEdge(ara[i].u, ara[i].v, ara[i].w);
        addEdge(ara[i].v, ara[i].u, ara[i].w);
    }

    dijkstra();

    for1(i, n) {
        if(dist[i] == inf)
            cout << -1 << " ";
        else
            cout << dist[i] << " ";
    }
    cout << EL;

    return 0;
}

