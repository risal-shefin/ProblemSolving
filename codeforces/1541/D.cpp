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

const ll sz = 210, LN = 12, mod = 1e9 + 7;

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

ll BIT[sz], depth[sz], pa[12][sz], fac[sz], inv[sz], n, prob[sz][sz];
vector <int> g[sz];

ll LCA(ll u, ll v)
{
    if(depth[u] < depth[v]) swap(u,v);
    ll diff = depth[u] - depth[v];
    for(ll i = 0; i < LN; i++) if( (diff>>i)&1 ) u = pa[i][u];
    if(u == v) return u;
    for(ll i = LN-1; i >= 0; i--) {
        if(pa[i][u] != pa[i][v]) {
            u = pa[i][u];
            v = pa[i][v];
        }
    }
    return pa[0][u];
}

void dfs(ll u, ll p, ll d)
{
    depth[u] = d, pa[0][u] = p;

    for(auto &v : g[u]) {
        if(v == p)
            continue;

        dfs(v, u, d+1);
    }
}

inline ll nCr(ll n, ll r)
{
    ll den = (inv[r] * inv[n-r]) % mod;
    return (fac[n] * den) % mod;
}

ll solve(ll root)
{
    ms(pa, -1);
    dfs(root, -1, 1);

    for(int i=1; i<LN; i++)
        for(int j=1; j<=n; j++)
            if(pa[i-1][j] != -1)
                pa[i][j] = pa[i-1][pa[i-1][j]];


    ll ret = 0;
    for1(i, n) {
        for(ll j = i+1; j <= n; j++) {
            ll lca = LCA(i, j);
            if(lca == j) {
                ret++;
                continue;
            }
            if(lca == i) continue;

            ll left = depth[i]-depth[lca], right = depth[j]-depth[lca];
            ret += prob[left][right];
            if(ret >= mod) ret -= mod;
        }
    }

    return ret;
}

ll calc_prob(ll l, ll r)
{
    if(r == 0) return 1;
    if(l == 0) return 0;

    ll &ret = prob[l][r];
    if(ret != -1)
        return ret;

    ll inv2 = fastPow(2, mod-2, mod);

    ret = (inv2 * calc_prob(l-1, r)) % mod;
    ret += (inv2 * calc_prob(l, r-1)) % mod;
    if(ret >= mod) ret -= mod;

    return ret;
}

int main()
{
    fac[0] = 1;
    for1(i, sz-1) fac[i] = (fac[i-1]*i) % mod;

    inv[sz-1] = fastPow(fac[sz-1], mod-2, mod);
    rep0(i, sz-1) inv[i] = (inv[i+1] * (i+1)) % mod;

    cin >> n;

    for1(i, n-1) {
        ll u, v;
        sl(u), sl(v);

        g[u].pb(v);
        g[v].pb(u);
    }

    ms(prob, -1);
    for1(i, n)
        for1(j, n)
            prob[i][j] = calc_prob(i, j);

    ll ans = 0;
    //dbg(solve(1));
    for1(i, n) {
        ans += (fastPow(n, mod-2, mod) * solve(i)) % mod;
        if(ans >= mod) ans -= mod;
    }

    pf("%lld\n", ans);

    return 0;
}
