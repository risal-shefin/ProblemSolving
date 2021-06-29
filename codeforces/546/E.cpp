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

const ll maxnodes = 250;

ll nodes = maxnodes, src, dest;
ll dist[maxnodes], q[maxnodes], work[maxnodes];

struct Edge
{
    ll to, rev;
    ll f, cap;
};

vector<Edge> g[maxnodes];

void addEdge(ll s, ll t, ll cap)
{
    Edge a = {t, g[t].size(), 0, cap};
    Edge b = {s, g[s].size(), 0, 0};
    g[s].push_back(a);
    g[t].push_back(b);
}

bool dinic_bfs()
{
    fill(dist, dist + nodes, -1);

    dist[src] = 0;
    ll index = 0;
    q[index++] = src;

    for (ll i = 0; i < index; i++)
    {
        ll u = q[i];
        for (ll j = 0; j < (ll) g[u].size(); j++)
        {
            Edge &e = g[u][j];
            if (dist[e.to] < 0 && e.f < e.cap)
            {
                dist[e.to] = dist[u] + 1;
                q[index++] = e.to;
            }
        }
    }
    return dist[dest] >= 0;
}

ll dinic_dfs(ll u, ll f)
{
    if (u == dest)
        return f;

    for (ll &i = work[u]; i < (ll) g[u].size(); i++)
    {
        Edge &e = g[u][i];

        if (e.cap <= e.f) continue;

        if (dist[e.to] == dist[u] + 1)
        {
            ll flow = dinic_dfs(e.to, min(f, e.cap - e.f));
            if (flow > 0)
            {
                e.f += flow;
                g[e.to][e.rev].f -= flow;
                return flow;
            }
        }
    }
    return 0;
}

ll maxFlow(ll _src, ll _dest)
{
    src = _src;
    dest = _dest;
    ll result = 0;
    while (dinic_bfs())
    {
        fill(work, work + nodes, 0);
        while (ll delta = dinic_dfs(src, INT_MAX))
            result += delta;
    }
    return result;
}
// addEdge(u, v, C); edge from u to v. Capacity=C
// maxFlow(s, t); max flow from s to t

const ll sz = 105;
ll a[sz], b[sz], ans[sz][sz];

int main()
{
    ll n, m, sa = 0, sb = 0;
    cin >> n >> m;

    for1(i, n) sl(a[i]), sa+=a[i];
    for1(i, n) sl(b[i]), sb+=b[i];

    for1(i, m) {
        ll u, v;
        sl(u), sl(v);

        addEdge(u, n+v, 1e9);
        addEdge(v, n+u, 1e9);
    }

    for1(i, n) {
        addEdge(0, i, a[i]), addEdge(n+i, 2*n+1, b[i]);
        addEdge(i, n+i, 1e9);
    }

    ll got = maxFlow(0, 2*n+1);

    if(got != sa || got != sb) {
        cout << "NO\n";
        return 0;
    }

    for1(i, n) {
        for(Edge &e : g[i]) {
            if(e.to == 0 || e.f == 0)
                continue;

            ans[i][e.to-n] = e.f;
        }
    }

    cout << "YES\n";
    for1(i, n) {
        for1(j, n)
            pf("%lld ", ans[i][j]);
        pn;
    }

    return 0;
}
