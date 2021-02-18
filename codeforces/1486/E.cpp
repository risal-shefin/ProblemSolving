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

const ll sz = 1e5 + 10;
ll dist[sz][2];

struct Edge {
    ll v, w;
};
vector <Edge> g[sz];

struct info {
    ll v, w, ext;
};
const bool operator <(const info &a, const info &b) {
    return a.w+a.ext > b.w+b.ext;
}

inline ll sq(ll x) {return x*x;}

void dijkstra(ll n)
{
    for1(i, n)
        for0(j, 2)
            dist[i][j] = inf;

    priority_queue <info> pq;
    pq.push({1, 0, 0});
    dist[1][0] = 0;

    while(!pq.empty()) {
        info got = pq.top();
        pq.pop();

        ll state = 1;
        if(got.ext == 0) state = 0;

        if(state == 0 && dist[got.v][state] != got.w+got.ext)
            continue;

        for(Edge &edge : g[ got.v ]) {

            ll now = state^1;

            if(!state) {
                ll cst = got.w + sq(edge.w), cst2 = 2*edge.w;
                pq.push({edge.v, cst, cst2});

//                if(dist[edge.v][now] > cst+cst2) {
//                    dist[edge.v][now] = cst+cst2;
//                    pq.push({edge.v, cst, cst2});
//                }
            }
            else {
                ll cst = got.w + sq(edge.w) + got.ext*edge.w;

                if(dist[edge.v][now] > cst) {
                    dist[edge.v][now] = cst;
                    pq.push({edge.v, cst, 0});
                }
            }
        }
    }
}

int main()
{
    ll n, m;
    cin >> n >> m;

    for1(i, m) {
        ll u, v, w;
        sl(u), sl(v), sl(w);

        g[u].pb({v, w});
        g[v].pb({u, w});
    }

    dijkstra(n);

    for1(i, n) {
        if(dist[i][0] == inf)
            pf("-1 ");
        else
            pf("%lld ", dist[i][0]);
    }
    pn;

    return 0;
}
