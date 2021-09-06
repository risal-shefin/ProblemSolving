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
ll cnt[sz][sz], ans[sz][sz];
vector <pii> g[sz][sz];

const ll dr[] = {1, -1, 0, 0};
const ll dc[] = {0, 0, 1, -1};

void bicolor(ll r, ll c)
{
    queue <pii> q;
    q.push({r, c});
    ans[r][c] = 1;

    while(!q.empty()) {
        pii u = q.front();
        q.pop();

        for(pii &v : g[u.ff][u.ss]) {
            if(ans[v.ff][v.ss] != -1)
                continue;

            ans[v.ff][v.ss] = 5-ans[u.ff][u.ss];
            q.push(v);
        }
    }
}

int main()
{
    ll n, m;
    cin >> n >> m;

    for1(i, n)
        scanf("%s", mat[i]+1);


    for1(i, n) {
        for1(j, m) {
            if(mat[i][j] != 'X')
                continue;

            vector <pii> v;

            for0(k, 4) {
                ll nr = i+dr[k], nc = j+dc[k];

                if(nr < 1 || nr > n || nc < 1 || nc > m || mat[nr][nc] == 'X')
                    continue;

                cnt[i][j]++;
                v.pb({nr, nc});
            }
            //dbg(v);

            if(cnt[i][j] & 1) {
                cout << "NO\n";
                return 0;
            }

            if(v.size() == 2) {
                g[v[0].ff][v[0].ss].pb({v[1].ff, v[1].ss});
                g[v[1].ff][v[1].ss].pb({v[0].ff, v[0].ss});
            }
            else if(v.size() == 4) {
                g[i-1][j].pb({i, j+1});
                g[i][j+1].pb({i-1, j});

                g[i+1][j].pb({i, j-1});
                g[i][j-1].pb({i+1, j});
            }
        }
    }

    ms(ans, -1);

    for1(i, n) {
        for1(j, m) {

            if(mat[i][j] == 'X') {
                if(cnt[i][j] == 0) ans[i][j] = 0;
                else if(cnt[i][j] == 2) ans[i][j] = 5;
                else ans[i][j] = 10;

                continue;
            }

            if(ans[i][j] != -1)
                continue;

            bicolor(i, j);
        }
    }

    cout << "YES\n";
    for1(i, n) {
        for1(j, m)
            pf("%lld ", ans[i][j]);
        pn;
    }

    return 0;
}
