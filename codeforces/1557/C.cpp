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

const ll sz = 2e5 + 10, mod = 1e9 + 7;
ll pw[sz], fac[sz], inv[sz], ev_way = 0;
ll dp[sz][2], n;

ll fastPow(ll x, ll n, ll MOD)
{
    ll ret = 1;
    while (n)
    {
        if (n & 1) ret = (ret * x) % MOD;
        x = (x * x) % MOD;
        n >>= 1;
    }
    return ret % MOD;
}

inline ll nCr(ll n, ll r)
{
    ll den = (inv[r] * inv[n-r]) % mod;
    return (fac[n] * den) % mod;
}

ll solve(ll k, bool isBig)
{
    if(k < 0)
        return 1;

    ll &ret = dp[k][isBig];
    if(ret != -1)
        return ret;

    if(isBig)
        return ret = (pw[n] * solve(k-1, isBig)) % mod;

    if(n & 1) ret = solve(k-1, isBig);
    else ret = solve(k-1, 1);

    ret += solve(k-1, isBig);
    if(ret >= mod) ret -= mod;

    if(n > 2) {
        ret += (ev_way * solve(k-1, isBig)) % mod;
        if(ret >= mod) ret -= mod;
    }

    return ret;
}

int main()
{
    fac[0] = 1;
    for1(i, sz-1) fac[i] = (fac[i-1] * i) % mod;

    inv[sz-1] = fastPow(fac[sz-1], mod-2, mod);
    rep0(i, sz-1) inv[i] = (inv[i+1] * (i+1)) % mod;

    pw[0] = 1;
    for1(i, sz-1) pw[i] = (pw[i-1] * 2) % mod;

    ll t;
    cin >> t;

    while(t--) {
        ms(dp, -1);

        ll k;
        sl(n), sl(k);

        if(k == 0) {
            pf("1\n");
            continue;
        }

        ev_way = 0;
        for(ll i = 2; i < n; i += 2) {
            ev_way += nCr(n, i);
            if(ev_way >= mod) ev_way -= mod;
        }
        //dbg(ev_way);

        pf("%lld\n", solve(k-1, 0));
    }

    return 0;
}
