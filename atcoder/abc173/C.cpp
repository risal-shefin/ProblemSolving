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
#define inf (1LL << 62)
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

char grid[10][10];
ll h, w, k, ans;

void solve(ll r, ll c, ll msk1, ll msk2)
{
    if(r == 0 && c == 0) {
        ll b = 0;
        for1(i, h) {
            for1(j, w) {
                bool br = (msk1 >> (i-1)) & 1;
                bool bc = (msk2 >> (j-1)) & 1;

                if(br == 1 || bc == 1)
                    continue;

                if(grid[i][j] == '#') b++;
            }
        }
        if(b == k) ans++;
        return;
    }

    if(r == 0) {
        ll lim = 1 << w;
        for0(i, lim)
            solve(0, 0, msk1, i);
    }
    else {
        ll lim = 1 << h;
        for0(i, lim)
            solve(0, 1, i, msk2);
    }
}

int main()
{
    cin >> h >> w >> k;

    for1(i, h)
        scanf("%s", grid[i]+1);

    solve(1, 0, 0, 0);
    cout << ans << EL;

    return 0;
}
