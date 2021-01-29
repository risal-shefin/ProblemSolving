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

const ll sz = 3e5 + 10;
ll vis[sz][2], cnt[sz], id;
char ara[sz];
ll n;
set <int> lst;

void dfs(ll u, bool s)
{
    lst.insert(u);
    vis[u][s] = id;

    if(u != n) {
        if((s == 0 && ara[u] == 'R') || (s == 1 && ara[u] == 'L')) {
            if(vis[u+1][s^1] == 0)
                dfs(u+1, s^1);
        }
    }
    if(u != 0) {
        if((s == 0 && ara[u] == 'L') || (s == 1 && ara[u] == 'R')) {
            if(vis[u-1][s^1] == 0)
                dfs(u-1, s^1);
        }
    }
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        sl(n);

        scanf("%s", ara);

        for(ll i = 0; i <= n; i++)
            for(ll j = 0; j < 2; j++)
                vis[i][j] = 0;

        id = 0;
        for(ll i = 0; i <= n; i++) {

            for(ll j = 0; j < 2; j++) {
                if(vis[i][j] != 0)
                    continue;

                lst.clear();
                ++id;
                dfs(i, j);

                cnt[id] = lst.size();
            }
        }

        for(ll i = 0; i <= n; i++) {
            ll now = vis[i][0];
            pf("%lld ", cnt[now]);
        }
        pn;
    }

    return 0;
}
