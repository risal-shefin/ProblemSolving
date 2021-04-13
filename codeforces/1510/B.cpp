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
#else
#define dbg(x)
#endif
// === Debug macro ends here ===

#define ff first
#define ss second

const ll maxnodes = 3000;

ll nodes = maxnodes, src, dest;
ll dist[maxnodes], enq[maxnodes];
pll par[maxnodes];

struct Edge {
    ll to, rev;
    ll f, cap, cst;
};

vector <Edge> g[maxnodes];

void addEdge(ll s, ll t, ll cap, ll cst)
{
    Edge a = {t, g[t].size(), 0, cap, cst};
    Edge b = {s, g[s].size(), 0, 0, -cst};
    g[s].pb(a);
    g[t].pb(b);
}

bool spfa()
{
    for0(i, maxnodes) dist[i] = inf, enq[i] = 0;

    queue <ll> q;
    q.push(src);
    dist[src] = 0, enq[src] = 1;

    while(!q.empty()) {
        ll u = q.front();
        enq[u] = 0;
        q.pop();

        for(ll i = 0; i < g[u].size(); i++)
        {
            Edge &e = g[u][i];
            if(dist[e.to] > dist[u] + e.cst && e.f < e.cap)
            {
                dist[e.to] = dist[u] + e.cst;
                par[e.to] = mp(u, i);

                if(!enq[e.to])
                {
                    q.push(e.to);
                    enq[e.to] = 1;
                }
            }
        }
    }

    return dist[dest] != inf;
}

pll maxFlow(ll _src, ll _dest)
{
    src = _src, dest = _dest;
    pll res = mp(0, 0);

    while(spfa())
    {
        ll cur = dest, f = inf;
        while(cur != src)
        {
            pll &pr = par[cur];
            Edge &e = g[pr.ff][pr.ss];
            f = min(f, e.cap-e.f);

            cur = pr.ff;
        }

        cur = dest;
        while(cur != src)
        {
            pll &pr = par[cur];
            Edge &e = g[pr.ff][pr.ss];
            e.f += f;
            g[e.to][e.rev].f -= f;

            res.ss += e.cst*f;
            cur = pr.ff;
        }
        res.ff += f;
    }
    return res;
}

const ll sz = 1030;
ll ara[sz], nxt[sz], cnt[sz];

int main()
{
    fastio;

    ll d, n;
    cin >> d >> n;

    for1(i, n) {
        string s; cin >> s;

        for0(j, d) {
            if(s[j] == '1')
                ara[i] |= (1<<j);
        }
    }

    ll src = 0, dest = 2*n+1;
    for1(i, n) {
        ll c = __builtin_popcount(ara[i]);
        addEdge(src, i, 1, 0);
        addEdge(src, n+i, 1, c+1);

        for1(j, n) {
            if(i == j || (ara[i]|ara[j]) != ara[j])
                continue;

            ll c2 = __builtin_popcount(ara[j]);

            addEdge(i, n+j, 1, c2-c);
        }
        addEdge(n+i, dest, 1, 0);
    }
    pll got = maxFlow(src, dest);
    //dbg(got);

    for1(i, n) {
        for(Edge &e : g[i]) {
            if(e.cap == 0 || e.f == 0)
                continue;

            nxt[i] = e.to-n;
            cnt[e.to-n]++;
        }
    }

    bool f = 0;
    string ans = "";

    for1(i, n) {
        if(cnt[i] != 0)
            continue;

        if(f) ans.pb('R');
        else f = 1;

        ll cur = i, made = 0;

        while(cur != 0) {
            for0(j, d) {
                bool b1 = (ara[cur]>>j) & 1, b2 = (made>>j) & 1;
                if(!b1 || b1==b2)
                    continue;

                made |= (1<<j);
                ans.pb(j+'0');
            }
            //dbg(mp(cur, bitset<5>(ara[cur])));
            cur = nxt[cur];
        }
        //dbg(i);
    }

    cout << ans.size() << EL;
    for(char &ch : ans) cout << ch << " ";
    cout << EL;

    return 0;
}

