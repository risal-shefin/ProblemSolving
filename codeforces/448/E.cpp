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

const ll MAX_N = 1e5;
vector <ll> ans, dv;
ll x, k;

void solve(ll num, ll op)
{
    if(num == 1 || op == k) {
        ans.pb(num);
        return;
    }

    for(ll i = 0; i < dv.size() && dv[i] <= num && ans.size() < MAX_N; i++) {

        if(num % dv[i] == 0)
            solve(dv[i], op+1);
    }
}

int main()
{
    cin >> x >> k;

    for(ll i = 1; i * i <= x; i++) {
        if(x % i != 0)
            continue;

        dv.pb(i);

        if(x/i != i) dv.pb(x / i);
    }

    sort(all(dv));
    solve(x, 0);

    for(ll i = 0; i < ans.size(); i++) {
        if(i != 0) pf(" ");
        pf("%lld", ans[i]);
    }
    pn;

    return 0;
}
