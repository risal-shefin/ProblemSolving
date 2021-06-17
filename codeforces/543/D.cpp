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

const ll mod = 1e9 + 7, sz = 2e5 + 10;
vector <ll> g[sz];
ll dp[sz][2], dp2[sz][2], ans[sz], pre[sz][2], suf[sz][2], bad[sz][2];
ll extr[sz][2];

void calc_pre(ll u, ll p)
{
    for0(i, g[u].size()) {
        ll v = g[u][i];

        if(v == p) {
            if(i>0) pre[i][0] = pre[i-1][0], pre[i][1] = pre[i-1][1];
            else pre[i][0] = pre[i][1] = 1;

            continue;
        }

        if(i == 0) {
            pre[i][0] = dp[v][0];
            pre[i][1] = (dp[v][0] + dp[v][1]) % mod;
        }
        else {
            pre[i][0] = (pre[i-1][0] * dp[v][0]) % mod;
            pre[i][1] = (pre[i-1][1] * (dp[v][0] + dp[v][1])) % mod;
        }
    }
}

void calc_suf(ll u, ll p)
{
    rep0(i, g[u].size()) {
        ll v = g[u][i];

        if(v == p) {
            if(i+1 < g[u].size()) suf[i][0] = suf[i+1][0], suf[i][1] = suf[i+1][1];
            else suf[i][0] = suf[i][1] = 1;

            continue;
        }

        if(i+1 == g[u].size()) {
            suf[i][0] = dp[v][0];
            suf[i][1] = (dp[v][0] + dp[v][1]) % mod;
        }
        else {
            suf[i][0] = (suf[i+1][0] * dp[v][0]) % mod;
            suf[i][1] = (suf[i+1][1] * (dp[v][0] + dp[v][1])) % mod;
        }
    }
}

void calc_bad(ll u, ll p)
{
    bad[u][0] = bad[u][1] = 1;
    if(g[u].size()==1) return;

    for0(i, g[u].size()) {
        ll v = g[u][i];
        if(v == p)
            continue;

        if(i == 0)
            bad[v][0] = suf[i+1][0], bad[v][1] = suf[i+1][1];
        else if(i+1 == g[u].size())
            bad[v][0] = pre[i-1][0], bad[v][1] = pre[i-1][1];
        else {
            bad[v][0] = (pre[i-1][0] * suf[i+1][0]) % mod;
            bad[v][1] = (pre[i-1][1] * suf[i+1][1]) % mod;
        }
    }
}

void dfs(ll u, ll p)
{
    dp[u][0] = 1, dp[u][1] = 1;
    extr[u][0] = 1, extr[u][1] = 1;

    for(ll &v : g[u]) {
        if(v == p)
            continue;

        dfs(v, u);

        dp[u][0] = (dp[u][0] * dp[v][0]) % mod;
        dp[u][1] = (dp[u][1] * (dp[v][0] + dp[v][1])) % mod;
    }
    dp2[u][0] = dp[u][0], dp2[u][1] = dp[u][1];

    calc_pre(u, p), calc_suf(u, p);
    calc_bad(u, p);
}

void rootChild(ll u, ll p)
{
    dp[p][0] = (bad[u][0]*extr[p][0])%mod, dp[p][1] = (bad[u][1]*extr[p][1]) % mod;

    dp[u][0] = (dp[u][0] * dp[p][0]) % mod;
    dp[u][1] = (dp[u][1] * (dp[p][0] + dp[p][1])) % mod;

    extr[u][0] = dp[p][0], extr[u][1] = (dp[p][0] + dp[p][1]) % mod;
}

void rootPar(ll u, ll p)
{
    dp[p][0] = (dp[p][0] * dp2[u][0]) % mod;
    dp[p][1] = (dp[p][1] * (dp2[u][0]+dp2[u][1])) % mod;

    dp[u][0] = dp2[u][0], dp[u][1] = dp2[u][1];
    extr[u][0] = 1, extr[u][1] = 1;
}

void ans_dfs(ll u, ll p)
{
    for(ll &v : g[u]) {
        if(v == p)
            continue;

        rootChild(v, u);
        ans_dfs(v, u);
        rootPar(v, u);
    }

    ans[u] = (dp[u][0] + dp[u][1] - 1) % mod;
}

int main()
{
    ll n; sl(n);

    for(ll i = 2; i <= n; i++) {
        ll p; sl(p);

        g[p].pb(i);
        g[i].pb(p);
    }

    dfs(1, -1);
    ans_dfs(1, -1);

    for1(i, n) pf("%lld ", ans[i]);
    pn;

    return 0;
}

