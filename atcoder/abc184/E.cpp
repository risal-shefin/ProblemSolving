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

const ll sz = 2009;

struct info {
    int r, c;
} s, g;

vector <info> tel[26];
char grid[sz][sz];
ll lev[sz][sz];

ll dr[] = {1, -1, 0, 0};
ll dc[] = {0, 0, 1, -1};

int main()
{
    ll h, w;
    cin >> h >> w;

    for1(i, h) {
        for1(j, w) {
            scanf(" %c", &grid[i][j]);

            if(grid[i][j] == '#')
                continue;

            if(grid[i][j] == 'S')
                s = {i, j};
            else if(grid[i][j] == 'G')
                g = {i, j};
            else if(grid[i][j] != '.') {
                ll now = grid[i][j] - 'a';
                tel[now].pb({i, j});
            }
        }
    }

    ms(lev, -1);

    queue <info> q;
    q.push({s.r, s.c});
    lev[s.r][s.c] = 0;

    while(!q.empty()) {
        info u = q.front();
        q.pop();

        for0(i, 4) {
            ll nr = u.r + dr[i], nc = u.c + dc[i];
            if(nr < 1 || nc < 1 || nr > h || nc > w || lev[nr][nc] != -1 || grid[nr][nc] == '#')
                continue;

            lev[nr][nc] = lev[u.r][u.c] + 1;
            q.push({nr, nc});
        }

        if(grid[u.r][u.c] >= 'a' && grid[u.r][u.c] <= 'z') {
            ll now = grid[u.r][u.c] - 'a';

            for(info &Info : tel[now]) {

                if(lev[Info.r][Info.c] != -1)
                    continue;

                lev[Info.r][Info.c] = lev[u.r][u.c] + 1;
                q.push({Info.r, Info.c});
            }
            tel[now].clear();
        }
    }

    cout << lev[g.r][g.c] << EL;

    return 0;
}
