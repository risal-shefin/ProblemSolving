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

const ll sz = 55, mod = 998244353;
ll mat[sz][sz], fact[sz], comp;
vector <ll> row[sz], col[sz];
bool vis[sz];

void dfs1(ll u)
{
    vis[u] = 1, comp++;

    for(ll &v : row[u])
        if(!vis[v])
            dfs1(v);
}

void dfs2(ll u)
{
    vis[u] = 1, comp++;

    for(ll &v : col[u])
        if(!vis[v])
            dfs2(v);
}

int main()
{
    fact[0] = 1;
    for1(i, sz-1) fact[i] = (fact[i-1] * i) % mod;

    ll n, k;
    cin >> n >> k;

    for1(i, n)
        for1(j, n)
            sl(mat[i][j]);

    for1(i, n) {

        for(ll j = i+1; j <= n; j++) {

            bool ok = 1;

            for1(jj, n) {
                if(mat[i][jj] + mat[j][jj] > k) {
                    ok = 0;
                    break;
                }
            }

            if(ok) {
                row[i].pb(j);
                row[j].pb(i);
            }
        }
    }

    for1(jj, n) {

        for(ll j = jj+1; j <= n; j++) {

            bool ok = 1;

            for1(i, n) {
                if(mat[i][jj] + mat[i][j] > k) {
                    ok = 0;
                    break;
                }
            }

            if(ok) {
                col[jj].pb(j);
                col[j].pb(jj);
            }
        }
    }

    ll ans = 1;
    for1(i, n) {
        if(vis[i])
            continue;

        comp = 0;
        dfs1(i);

        ans = (ans * fact[comp]) % mod;
    }

    ms(vis, 0);

    for1(i, n) {
        if(vis[i])
            continue;

        comp = 0;
        dfs2(i);

        ans = (ans * fact[comp]) % mod;
    }

    cout << ans << EL;

    return 0;
}