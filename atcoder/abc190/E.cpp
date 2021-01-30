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

const ll sz = 1e5 + 10, bsz = 17;
bool stone[sz];
ll dp[(1<<bsz)][bsz], ara[bsz], pos[sz], lim, reach[bsz][bsz], lev[sz], k;

vector <ll> g[sz];

void bfs(ll u, ll gp)
{
    queue <ll> q;
    q.push(u);
    lev[u] = 0;

    while(!q.empty()) {
        ll u = q.front();
        q.pop();

        for(ll &v : g[u]) {
            if(lev[v] != -1)
                continue;

            lev[v] = lev[u] + 1;
            if(stone[v])
                reach[gp][ pos[v] ] = lev[v];

            q.push(v);
        }
    }
}

ll solve(ll msk, ll pos)
{
    if(msk == lim) {
        return 0;
    }

    ll &ret = dp[msk][pos];
    if(ret != -1)
        return ret;

    ret = inf;

    for0(i, k) {
        if((msk>>i) & 1)
            continue;

        if(msk == 0)
            ret = min(ret, 1 + solve(msk|(1<<i), i));
        else {
            if(reach[pos][i] != -1)
                ret = min(ret, reach[pos][i] + solve(msk|(1<<i), i));
        }
    }

    return ret;
}

int main()
{
    ll n, m;
    cin >> n >> m;

    for1(i, m) {
        ll u, v;
        sl(u), sl(v);
        u--, v--;

        g[u].pb(v);
        g[v].pb(u);
    }

    sl(k);

    for0(i, k) {
        sl(ara[i]);
        ara[i]--;
        stone[ ara[i] ] = 1;
        pos[ ara[i] ] = i;
    }

    ms(reach, -1);

    for0(i, k) {
        ms(lev,-1);
        bfs(ara[i], i);
    }

    lim = (1<<k) - 1;
    ms(dp, -1);
    ll ans = solve(0, 0);

    if(ans >= inf)
        cout << -1 << EL;
    else
        cout << ans << EL;

    return 0;
}
