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
#ifdef LOCALXOX
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

const ll sz = 505;
char mat[sz][sz];
int vis[sz][sz];

ll dr[] = {1, -1, 0, 0};
ll dc[] = {0, 0, 1, -1};

int main()
{
    ll h, w;
    cin >> h >> w;

    for1(i, h)
        scanf("%s", mat[i]+1);

    for1(i, h)
        for1(j, w)
            vis[i][j] = 1e9;

    deque <pii> dq;
    dq.pb(mp(1, 1));
    vis[1][1] = 0;

    while(!dq.empty()) {
        pii u = dq.front();
        dq.pop_front();

        for0(i, 4) {
            ll nr = u.ff + dr[i], nc = u.ss+dc[i];

            if(nr < 1 || nc < 1 || nr > h || nc > w)
                continue;

            if(mat[nr][nc] != '#' && vis[nr][nc] > vis[u.ff][u.ss]) {
                dq.push_front(mp(nr, nc));
                vis[nr][nc] = vis[u.ff][u.ss];
            }
            else if(mat[nr][nc] == '#') {

                for(int x = nr-1; x <= nr+1; x++) {
                    for(int y = nc-1; y <= nc+1; y++) {

                        if(x < 1 || y < 1 || x > h || y > w)
                            continue;

                        if(vis[x][y] > vis[u.ff][u.ss]+1) {
                            dq.pb(mp(x, y));
                            vis[x][y] = vis[u.ff][u.ss]+1;
                        }
                    }
                }
            }
        }
    }

    cout << vis[h][w] << EL;

    return 0;
}
