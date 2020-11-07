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

const ll sz = 5e5 + 10;

struct node {
    int v, typ;
};
vector <node> g[sz];

ll dp[sz], b[sz], w[sz], col[sz];

int main()
{
    ll n, m;
    cin >> n >> m;

    for1(i, m) {
        ll u, v, t;
        sl(u), sl(v), sl(t);

        g[v].pb({u, t});
    }

    for1(i, n) dp[i] = b[i] = w[i] = inf;

    queue <ll> q;
    q.push(n);
    dp[n] = b[n] = w[n] = col[n] = 0;

    while(!q.empty()) {
        ll u = q.front();
        q.pop();

        for(node &nd : g[u]) {

            if(nd.typ == 1) w[nd.v] = min(w[nd.v], dp[u]+1);
            else b[nd.v] = min(b[nd.v], dp[u]+1);

            ll mx = max(w[nd.v], b[nd.v]);

            if(w[nd.v] >= b[nd.v]) col[nd.v] = 1;
            else col[nd.v] = 0;

            if(dp[nd.v] == inf && mx != inf)
                q.push(nd.v);

            dp[nd.v] = mx;
        }
    }

    if(dp[1] == inf) cout << -1 << EL;
    else cout << dp[1] << EL;

    for1(i, n) pf("%lld", col[i]);
    pn;

    return 0;
}
