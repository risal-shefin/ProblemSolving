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
#else
#define dbg(x)
#endif
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

// === Debug macro ends here ===

#define ff first
#define ss second

const ll sz = 5009, mod = 998244353;
ll dp[sz][sz], temp[sz], h[sz], n, k;

vector <ll> g[sz];

void dfs(ll u, ll p)
{
    h[u] = 0, dp[u][0] = 1;

    for(ll &v : g[u]) {
        if(v == p)
            continue;

        dfs(v, u);

        for(ll i = 0; i <= h[u]; i++) {
            for(ll j = 0; j <= h[v]; j++) {

                // If u-v edge is cut
                if(max(i, j) <= k)
                    temp[i] = (temp[i] + dp[u][i]*dp[v][j]) % mod;

                // If u-v edge is not cut
                if(i + j+1 <= k)
                    temp[max(i, j+1)] = (temp[max(i,j+1)] + dp[u][i]*dp[v][j]) % mod;
            }
        }

        h[u] = max(h[u], h[v]+1);

        for(ll i = 0; i <= h[u]; i++) {
            dp[u][i] = temp[i];
            temp[i] = 0;
        }
    }
}

int main()
{
    fastio;
    cin >> n >> k;

    for1(i, n-1) {
        ll u, v;
        cin >> u >> v;

        g[u].pb(v);
        g[v].pb(u);
    }

    dfs(1, -1);

    ll ans = 0;

    for(ll i = 0; i <= k; i++) {
        ans += dp[1][i];
        if(ans >= mod)
            ans -= mod;
    }

    cout << ans << EL;

    return 0;
}
