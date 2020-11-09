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
ll cst[sz][sz][2], en[sz][sz][2], dp[sz][2], n, k;

struct info {
    ll l, r, a;
} ara[sz];

ll solve(ll pos, bool lateStart)
{
    if(pos > n)
        return 0;

    ll &ret = dp[pos][lateStart];
    if(ret != -1)
        return ret;

    ret = inf;
    for(ll i = pos; i <= n; i++) {

        if(cst[pos][i][lateStart] == -1)
            break;

        ll nxtLate = 0;
        if(en[pos][i][lateStart] == ara[i+1].l) nxtLate = 1;

        ret = min(ret, cst[pos][i][lateStart] + solve(i+1, nxtLate));
    }

    return ret;
}

int main()
{
    cin >> n >> k;

    for1(i, n) sl(ara[i].l), sl(ara[i].r), sl(ara[i].a);

    ms(cst, -1);

    for1(i, n) {

        ll has = k, used = k, spent = 0;

        for(ll j = i; j <= n; j++) {

            ll ase = ara[j].a;

            ll mn = min(has, ase);
            ase -= mn, has -= mn, spent += mn;

            ll need = ase / k;
            if(ase % k != 0) need++;

            if(ara[j].l+need > ara[j].r) break;

            if(need != 0) has = k*need - ase;
            used += (k*need), spent += ase;

            if(j != n) cst[i][j][0] = used;
            else cst[i][j][0] = spent;

            en[i][j][0] = ara[j].l+need;
        }

        has = k, used = k, spent = 0;

        for(ll j = i; j <= n; j++) {

            ll tim = ara[j].r - ara[j].l + 1, ase = ara[j].a;
            if(j == i) tim--;
            if(tim == 0) break;

            ll mn = min(has, ase);
            ase -= mn, has -= mn, spent += mn;

            ll need = ase / k;
            if(ase % k != 0) need++;

            if(1+need > tim) break;

            if(need != 0) has = k*need - ase;
            used += (k*need), spent += ase;

            if(j != n) cst[i][j][1] = used;
            else cst[i][j][1] = spent;

            en[i][j][1] = ara[j].l+need;
            if(j == i) en[i][j][1]++;
        }
    }

    ms(dp, -1);
    ll ans = solve(1, 0);

    if(ans == inf) cout << -1 << EL;
    else cout << ans << EL;

    return 0;
}
