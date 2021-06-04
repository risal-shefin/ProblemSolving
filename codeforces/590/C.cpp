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

const ll sz = 1009, inf = 1e9;
char mat[sz][sz];
ll n, m, dist[4][sz][sz];

ll dr[] = {1, -1, 0, 0};
ll dc[] = {0, 0, 1, -1};

void bfs(ll x)
{
    deque <pii> q;
    char ch = x + '0';

    for1(i, n) {
        for1(j, m) {
            if(mat[i][j] == ch) {
                dist[x][i][j] = 0;
                q.pb({i, j});
            }
        }
    }

    while(!q.empty()) {
        pii u = q.front();
        q.pop_front();

        for0(i, 4) {
            ll nr = u.ff+dr[i], nc = u.ss+dc[i];

            if(nr < 1 || nc < 1 || nr > n || nc > m || dist[x][nr][nc] != inf || mat[nr][nc] == '#')
                continue;

            if(mat[nr][nc] == '.') {
                dist[x][nr][nc] = dist[x][u.ff][u.ss] + 1;
                q.pb(mp(nr, nc));
            }
            else if(mat[nr][nc] != ch) {
                dist[x][nr][nc] = dist[x][u.ff][u.ss];
                q.push_front(mp(nr, nc));
            }
        }
    }
}

int main()
{
    cin >> n >> m;

    for1(i, n) scanf("%s", mat[i]+1);

    for1(i, n)
        for1(j, m)
            for1(k, 3)
                dist[k][i][j] = inf;

    for1(i, 3) bfs(i);

    ll ans = inf;

    for1(i, n)
        for1(j, m)
            ans = min(ans, dist[1][i][j] + dist[2][i][j] + dist[3][i][j] - 2*(mat[i][j] == '.'));

    if(ans == inf) pf("-1\n");
    else pf("%lld\n", ans);

    return 0;
}

