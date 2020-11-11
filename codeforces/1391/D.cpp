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

const ll sz = 1e6 + 10, lim = 8;

vector <char> grid[sz];
ll n, m, dp[sz][8];

inline bool isValid(ll msk1, ll msk2)
{
    ll ase = 0;
    for(ll i = 0; i <= 1; i++) {
        ll b1 = (msk1 >> i) & 1, b2 = (msk2 >> i) & 1;
        ase += b1, ase += b2;
    }
    if(!(ase & 1)) return 0;

    if(n > 2) {
        ase = 0;
        for(ll i = 1; i <= 2; i++) {
            ll b1 = (msk1 >> i) & 1, b2 = (msk2 >> i) & 1;
            ase += b1, ase += b2;
        }
        if(!(ase & 1)) return 0;
    }
    return 1;
}

ll solve(ll pos, ll prv)
{
    if(pos > m)
        return 0;

    ll &ret = dp[pos][prv];
    if(ret != -1)
        return ret;

    ret = inf;

    for0(msk, lim) {

        ll cst = 0;
        for1(i, n) {
            ll now = i-1, v = grid[i][pos] - '0';
            ll b = (msk >> now) & 1;

            if(v != b) cst++;
        }

        if(isValid(prv, msk)) ret = min(ret, cst + solve(pos+1, msk));
    }

    return ret;
}

int main()
{
    cin >> n >> m;

    if(n <= m) {

        for1(i, n) {
            grid[i].resize(m+1);

            for1(j, m)
                scanf(" %c", &grid[i][j]);
        }
    }
    else {

        for1(i, m) grid[i].resize(n+1);

        for1(i, n)
            for1(j, m)
                scanf(" %c", &grid[j][i]);

        swap(n, m);
    }

    if(n == 1 || m == 1) {
        cout << "0" << endl;
        return 0;
    }
    if(n >= 4 && m >= 4) {
        cout << -1 << endl;
        return 0;
    }

    ll ans = inf;

    ms(dp, -1);

    for0(msk, lim) {

        ll cst = 0;
        for1(i, n) {
            ll now = i-1, v = grid[i][1] - '0';
            ll b = (msk >> now) & 1;

            if(v != b) cst++;
        }

        ans = min(ans, cst + solve(2, msk));
        //cout << bitset<3>(msk) << "  " << ans << " " << cst << endl;
    }

    if(ans == inf) cout << -1 << EL;
    else cout << ans << EL;

    return 0;
}
