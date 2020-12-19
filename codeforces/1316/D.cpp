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

const ll sz = 1e3 + 10;

struct info {
    ll r, c;
} mat[sz][sz];

struct info2 {
    ll r, c, gr, gc;
};
bool vis[sz][sz];

ll dr[] = {1, -1, 0, 0};
ll dc[] = {0, 0, 1, -1};

char mov[] = {'D', 'U', 'R', 'L'};
char rmov[] = {'U', 'D', 'L', 'R'};

char ans[sz][sz];

int main()
{
    ll n, ok = 1;
    sl(n);

    queue <info2> q;

    for1(i, n)
        for1(j, n)
            sl(mat[i][j].r), sl(mat[i][j].c);

    for1(i, n) {
        for1(j, n) {
            ll row = mat[i][j].r, col = mat[i][j].c;

            if(ans[i][j] == 'X' && (row != i || col != j)) {
                ok = 0;
                break;
            }

            if(row == -1)
                continue;

            if(mat[row][col].r != row || mat[row][col].c != col) {
                ok = 0;
                break;
            }

            if(ans[row][col] != 'X') {
                ans[row][col] = 'X', vis[row][col] = 1;
                q.push({row, col, row, col});
            }
        }
    }

    if(!ok) {
        pf("INVALID\n");
        return 0;
    }

    while(!q.empty()) {
        info2 u = q.front();
        q.pop();

        for0(k, 4) {
            ll nr = u.r + dr[k], nc = u.c + dc[k];

            if(nr < 1 || nc < 1 || nr > n || nc > n || vis[nr][nc] || mat[nr][nc].r != u.gr || mat[nr][nc].c != u.gc)
                continue;

            vis[nr][nc] = 1;

            ans[nr][nc] = rmov[k];

            q.push({nr, nc, u.gr, u.gc});
        }
    }

    for1(i, n) {
        for1(j, n) {

            if(ans[i][j] != '\0')
                continue;

            if(mat[i][j].r != -1) {
                ok = 0;
                break;
            }

            bool got = 0;

            for0(k, 4) {
                ll nr = i+dr[k], nc = j+dc[k];

                if(nr < 1 || nc < 1 || nr > n || nc > n)
                    continue;

                if(mat[nr][nc].r == -1) {
                    ans[i][j] = mov[k];
                    got = 1;
                    break;
                }
            }

            if(!got) {
                ok = 0;
                break;
            }
        }

        if(!ok)
            break;
    }

    if(!ok) pf("INVALID\n");
    else {
        pf("VALID\n");
        for1(i, n) {
            for1(j, n)
                pf("%c", ans[i][j]);
            pn;
        }
    }

    return 0;
}