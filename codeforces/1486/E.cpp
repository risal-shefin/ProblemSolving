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

const ll sz = 1e5 + 10;
ll dist[sz][51], n, m;

struct Edge {
    int v, w, a;
};
vector <Edge> g[sz];

const bool operator <(const Edge &a, const Edge &b) {
    if(a.w == b.w)
        return a.a > b.a;
    return a.w > b.w;
}

inline ll sq(ll x) {return x*x;}

void dijkstra()
{
    for1(i, sz-1)
        for0(j, 51)
            dist[i][j] = inf;

    priority_queue <Edge> pq;
    pq.push({1, 0, 0});
    dist[1][0] = 0;

    while(!pq.empty()) {
        Edge got = pq.top();
        pq.pop();

        if(dist[got.v][got.a] != got.w)
            continue;

        for(Edge &edge : g[ got.v ]) {

            ll nxt = edge.w, cst = got.w;
            if(got.a != 0) {
                nxt = 0;
                cst += sq(got.a+edge.w);
            }

            if(dist[edge.v][nxt] > cst) {
                dist[edge.v][nxt] = cst;
                pq.push({edge.v, cst, nxt});
            }
        }
    }
}

int main()
{
    fastio;

    cin >> n >> m;

    for1(i, m) {
        ll u, v, w;
        cin >> u >> v >> w;

        g[u].pb({v, w});
        g[v].pb({u, w});
    }

    dijkstra();

    for1(i, n) {
        if(dist[i][0] == inf)
            cout << -1 << " ";
        else
            cout << dist[i][0] << " ";
    }
    cout << EL;

    return 0;
}


