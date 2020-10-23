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

struct node {
    ll x, y, id;
} ara[sz], ara2[sz];

const bool cmpx(const node &a, const node &b) {
    return a.x < b.x;
}

const bool cmpy(const node &a, const node &b) {
    return a.y < b.y;
}

struct info {
    ll u, cst;
};
const bool operator <(const info &a, const info &b) {
    return a.cst > b.cst;
}
vector <info> g[sz];

ll dist[sz];

void dijkstra()
{
    for0(i, sz) dist[i] = inf;

    priority_queue <info> pq;
    pq.push({0, 0});
    dist[0] = 0;

    while(!pq.empty()) {
        info nd = pq.top();
        pq.pop();

        if(dist[nd.u] != nd.cst)
            continue;

        for(info &v : g[nd.u]) {

            if(dist[v.u] > nd.cst + v.cst) {
                dist[v.u] = nd.cst + v.cst;
                pq.push({v.u, dist[v.u]});
            }
        }
    }
}

int main()
{
    ll n, m;
    sl(n), sl(m);

    ll sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;
    ara[0] = {sx, sy, 0};

    for1(i, m) {
        sl(ara[i].x), sl(ara[i].y);
        ara[i].id = i;

        ara2[i] = ara[i];
    }

    sort(ara2+1, ara2+m+1, cmpx);

    for1(i, m-1) {
        ll id = ara2[i].id, nxt = ara2[i+1].id;
        ll cst = abs(ara2[i].x - ara2[i+1].x);

        g[id].pb({nxt, cst});
        g[nxt].pb({id, cst});
    }

    sort(ara2+1, ara2+m+1, cmpy);

    for1(i, m-1) {
        ll id = ara2[i].id, nxt = ara2[i+1].id;
        ll cst = abs(ara2[i].y - ara2[i+1].y);

        g[id].pb({nxt, cst});
        g[nxt].pb({id, cst});
    }

    for1(i, m) {
        ll cst = min(abs(sx-ara[i].x), abs(sy-ara[i].y));
        g[0].pb({i, cst});
    }

    dijkstra();

    ll ans = abs(sx-tx) + abs(sy-ty);

    for1(i, m) {
        ll cst = abs(ara[i].x - tx) + abs(ara[i].y - ty);
        ans = min(ans, dist[i] + cst);
    }

    cout << ans << EL;

    return 0;
}
