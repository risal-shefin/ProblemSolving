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

const ll sz = 3009;
vector <ll> g[sz];
ll dist[sz][sz];

void bfs(ll src)
{
    dist[src][src] = 0;
    queue <ll> q;
    q.push(src);

    while(!q.empty()) {
        ll u = q.front();
        q.pop();

        for(ll &v : g[u]) {
            if(dist[src][v] == -1) {
                dist[src][v] = dist[src][u] + 1;
                q.push(v);
            }
        }
    }
}

int main()
{
    ll n, m;
    cin >> n >> m;

    for1(i, m) {
        ll u, v;
        sl(u), sl(v);

        g[u].pb(v);
        g[v].pb(u);
    }

    ms(dist, -1);
    for1(i, n) bfs(i);

    ll s1, t1, l1, s2, l2, t2;
    cin >> s1 >> t1 >> l1;
    cin >> s2 >> t2 >> l2;

    if(dist[s1][t1] > l1 || dist[s2][t2] > l2) {
        cout << -1 << EL;
        return 0;
    }

    ll ans = m - (dist[s1][t1] + dist[s2][t2]);

    for1(i, n) {
        for1(j, n) {

            ll del1 = 0, del2 = 0;

            if(dist[s1][i]+dist[i][j]+dist[j][t1] <= l1 && dist[s2][i]+dist[i][j]+dist[j][t2] <= l2)
                del1 = m - (dist[s1][i] + dist[s2][i] + dist[i][j] + dist[j][t1] + dist[j][t2]);

            if(dist[t1][i]+dist[i][j]+dist[j][s1] <= l1 && dist[s2][i]+dist[i][j]+dist[j][t2] <= l2)
                del2 = m - (dist[t1][i] + dist[s2][i] + dist[i][j] + dist[j][s1] + dist[j][t2]);

            ans = max({ans, del1, del2});
        }
    }

    cout << ans << EL;

    return 0;
}
