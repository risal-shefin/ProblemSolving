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

const ll sz = 105;
vector <int> g[sz], path[sz][sz][2], yo[sz][2];
ll dp[sz][sz][2], tmp[sz][2], n, k;

struct info {
    int u1, k1, u2, k2;
} way1[sz], way2[sz];

void dfs(ll u)
{
    dp[u][1][0] = dp[u][1][1] = 0;
    for(ll i = 2; i <= k; i++) dp[u][i][0] = dp[u][i][1] = inf;

    path[u][1][0].pb(u);
    path[u][1][1].pb(u);

    for(int &v : g[u]) {
        dfs(v);

        for1(i, k) {
            tmp[i][0] = dp[u][i][0], tmp[i][1] = dp[u][i][1];
            way1[i] = way2[i] = {-1, -1, -1, -1};

            yo[i][0] = path[u][i][0];
            yo[i][1] = path[u][i][1];
        }

        for1(i, k) {
            for1(j, k) {

                ll tot = i+j;
                if(tot > k) continue;

                if(tmp[tot][0] > dp[u][i][1] + 1+dp[v][j][0]) {
                    way1[tot] = {u, i, v, j};
                    tmp[tot][0] = dp[u][i][1] + 1+dp[v][j][0];
                }

                if(tmp[tot][0] > dp[u][i][0] + 2+dp[v][j][1]) {
                    way1[tot] = {v, j, u, i};
                    tmp[tot][0] = dp[u][i][0] + 2+dp[v][j][1];
                }

//                tmp[tot][0] = min(tmp[tot][0], dp[u][i][1] + 1+dp[v][j][0]);
//                tmp[tot][0] = min(tmp[tot][0], dp[u][i][0] + 2+dp[v][j][1]);

                if(tmp[tot][1] > dp[u][i][1] + 2+dp[v][j][1]) {
                    way2[tot] = {u, i, v, j};
                    tmp[tot][1] = dp[u][i][1] + 2+dp[v][j][1];
                }

//                tmp[tot][1] = min(tmp[tot][1], dp[u][i][1] + 2+dp[v][j][1]);
            }
        }

        for1(i, k) {

            if(dp[u][i][0] > tmp[i][0]) {
                dp[u][i][0] = tmp[i][0];

                ll u1 = way1[i].u1, u2 = way1[i].u2, k1 = way1[i].k1, k2 = way1[i].k2;

                if(u1 == u) {

                    yo[i][0] = path[u][k1][1];
                    yo[i][0].insert(yo[i][0].end(), all(path[u2][k2][0]));
                }
                else {
                    vector <int> temp;

                    temp.pb(u);
                    temp.insert(temp.end(), all(path[u1][k1][1]));

                    temp.insert(temp.end(), all(path[u2][k2][0]));
                    yo[i][0] = temp;
                }
            }

            if(dp[u][i][1] > tmp[i][1]) {
                dp[u][i][1] = tmp[i][1];

                ll u1 = way2[i].u1, u2 = way2[i].u2, k1 = way2[i].k1, k2 = way2[i].k2;

                yo[i][1] = path[u1][k1][1];
                yo[i][1].insert(yo[i][1].end(), all(path[u2][k2][1]));
                yo[i][1].pb(u);
            }
        }

        for1(i, k) {
            path[u][i][0] = yo[i][0];
            path[u][i][1] = yo[i][1];
        }
        //if(u == 8) dbg(path[u][8][0]);
    }

    //if(u == 8) dbg(path[u][6][1]);
}

int main()
{
    fastio;

    ll t;
    cin >> t;

    while(t--) {
        cin >> n >> k;

        for(ll i = 2; i <= n; i++) {
            ll p; cin >> p;
            g[p].pb(i);
        }

        dfs(1);

        ll ans;
        vector <int> res;

        if(dp[1][k][0] < dp[1][k][1]) {
            ans = dp[1][k][0];
            res = path[1][k][0];
        }
        else {
            ans = dp[1][k][1];
            res = path[1][k][1];
        }

        cout << ans << EL;
        for(ll i = 0; i < res.size(); i++) {
            if(i != 0) cout << " ";
            cout << res[i];
        }
        cout << EL;

        for1(i, n) {
            g[i].clear();

            for1(j, n)
                for0(j2, 2)
                    path[i][j][j2].clear();
        }
    }

    return 0;
}

