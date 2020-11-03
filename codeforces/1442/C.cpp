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
#define inf (1LL << 29)
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
    int v, k, x;
};

inline bool large(const pii &a, const pii &b)
{
    if(a.first == b.first)
        return a.second > b.second;

    if(a.first > 50 || b.first > 50)
        return a.first > b.first;

    register ll ta = (1LL << (a.first+1)) - 1;
    register ll tb = (1LL << (b.first+1)) - 1;

    register const ll ca = ta + a.second, cb = tb + b.second;
    return ca > cb;
}

const bool operator <(const node &a, const node &b)
{
    register const pii f = mp(a.k, a.x), s = mp(b.k, b.x);
    return large(f, s);
}

struct edge {
    int v, state;
};
vector <edge> g[sz];

pii dist[sz][mxb+5];

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

        if(pii(u.k, u.x) != dist[u.v][step])
            continue;

        for(edge &Edge : g[u.v]) {
            pii cst;
            ll step2 = step;

            if(Edge.state && (u.k&1)) cst.first = u.k+1, step2++;
            else if(!Edge.state && !(u.k&1)) cst.first = u.k+1, step2++;
            else cst.first = u.k;

            if(step2 >= mxb) step2 = mxb + (cst.first&1);

            cst.second = u.x + 1;

            if(large(dist[Edge.v][step2], cst)) {

                dist[Edge.v][step2] = cst;
                pq.push({Edge.v, cst.first, cst.second});
            }
        }
    }

    pii got = mp(inf, inf);

    for(ll i = 0; i <= mxb+1; i++) {

        if(large(got, dist[n][i])) got = dist[n][i];
    }

    ll tp = fastPow(2, got.first+1, mod);
    tp--;
    if(tp < 0) tp += mod;

    ll ans = (got.second + tp) % mod;

    cout << ans << EL;

    return 0;
}


