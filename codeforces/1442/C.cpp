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

const ll sz = 2e5 + 10, mod = 998244353, mxb = 30;

struct node {
    ll v, k, x;
};
const bool operator <(const node &a, const node &b) {

    if(a.k == b.k)
        return a.x > b.x;

    if(a.k > 50 || b.k > 50)
        return a.k > b.k;

    register ll ta = 0, tb = 0;
    if(a.k != -1) ta = (1LL << (a.k+1)) - 1;
    if(b.k != -1) tb = (1LL << (b.k+1)) - 1;

    register const ll ca = ta + a.x, cb = tb + b.x;
    return ca > cb;
}

struct edge {
    int v, state;
};
vector <edge> g[sz];

pll dist[sz][mxb+5];

inline bool check(pll &a, pll &b)
{
    if(a.first == b.first)
        return a.second > b.second;

    if(a.first > 50 || b.first > 50)
        return a.first > b.first;

    register ll ta = 0, tb = 0;
    if(a.first != -1) ta = (1LL << (a.first+1)) - 1;
    if(b.first != -1) tb = (1LL << (b.first+1)) - 1;

    register const ll ca = ta + a.second, cb = tb + b.second;
    return ca > cb;
}

ll fastPow(ll x, ll n, ll MOD)
{
    ll ret = 1;
    while (n)
    {
        if (n & 1) ret = (ret * x) % MOD;
        x = (x * x) % MOD;
        n >>= 1;
    }
    return ret % MOD;
}

int main()
{
    ll n, m;
    cin >> n >> m;

    for1(i, m) {
        ll u, v;
        sl(u), sl(v);

        g[u].pb({v, 0});
        g[v].pb({u, 1});
    }

    for1(i, n)
        for0(j, mxb+5)
            dist[i][j] = {inf, inf};

    priority_queue <node> pq;
    pq.push({1, -1, 0});
    dist[1][0] = mp(-1, 0);

    while(!pq.empty()) {
        node u = pq.top();
        pq.pop();

        ll step = (u.k+1);
        if(step >= mxb) step = mxb + (u.k&1);

        if(pll(u.k, u.x) != dist[u.v][step])
            continue;

        for(edge &Edge : g[u.v]) {
            pll cst;
            ll step2 = step;

            if(Edge.state && (u.k&1)) cst.first = u.k+1, step2++;
            else if(!Edge.state && !(u.k&1)) cst.first = u.k+1, step2++;
            else cst.first = u.k;

            if(step2 >= mxb) step2 = mxb + (cst.first&1);

            cst.second = u.x + 1;

            if(check(dist[Edge.v][step2], cst)) {

                dist[Edge.v][step2] = cst;
                pq.push({Edge.v, cst.first, cst.second});
            }
        }
    }

    pll got = mp(inf, inf);

    for(ll i = 0; i <= mxb+1; i++) {

        if(check(got, dist[n][i])) got = dist[n][i];
    }

    ll tp = fastPow(2, got.first+1, mod);
    tp--;
    if(tp < 0) tp += mod;

    ll ans = (got.second + tp) % mod;

    cout << ans << EL;

    return 0;
}


