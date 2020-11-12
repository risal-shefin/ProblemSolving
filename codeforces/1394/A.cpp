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

const ll sz = 1e5 + 10;
ll ara[sz], d;
vector <int> Norm, over;

ll solve(ll cnt)
{
    ll ret = 0;
    for(ll i = 0; i < cnt; i++) ret += over[i];

    ll need = (cnt-1)*d;
    need -= ((ll)over.size() - cnt);
    need = max(0LL, need);

    if(need > Norm.size()) return -inf;

    for(ll i = need; i < Norm.size(); i++) ret += Norm[i];

    return ret;
}

int main()
{
    ll n, m, ans = 0;
    cin >> n >> d >> m;

    for1(i, n) sl(ara[i]);

    if(n == 1) {
        cout << ara[1] << EL;
        return 0;
    }

    sort(ara+1, ara+n+1);

    if(ara[n-1] <= m) {
        for1(i, n) ans += ara[i];
        cout << ans << EL;

        return 0;
    }

    for1(i, n) {
        if(ara[i] <= m) Norm.pb(ara[i]);
        else break;
    }

    rep1(i, n) {
        if(ara[i] > m) over.pb(ara[i]);
        else break;
    }

    ll lo = 1, hi = over.size(), ret = 0;

    while(lo < hi) {
        ll mid = (lo+hi)>>1;

        ll got1 = solve(mid), got2 = solve(mid+1);

        if(got1 >= got2) {
            ret = max(ret, got1);
            hi = mid;
        }
        else {
            ret = max(ret, got2);
            lo = mid+1;
        }
    }
    ret = max(ret, solve(lo));

    cout << ret << EL;

    return 0;
}

