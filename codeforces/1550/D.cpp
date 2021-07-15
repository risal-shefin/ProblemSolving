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
#ifndef ONLINE_JUDGE
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
ll fac[sz], inv[sz], n, l, r;

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

ll check(ll l, ll h, ll r)
{
    ll h2 = (n-h);
    ll rng = r-l-1, need1 = h-l, need2 = h2 - (n-r+1);
    if(need1 + need2 > rng || need1 > rng || need2 > rng) return 0;

    //cerr << l << " " << h << " " << r << " " << nCr(rng, need1) << endl;
    return nCr(rng, need1);
}

ll solve(ll start)
{
    ll f = start, ret = 0;

    while(1) {

        ll lo = 1, hi = n, inc = min(n, r-f), dec = max(1LL, l+f);

        if(inc < 1 || dec>n || dec > inc+1) break;

        ll finc = dec-1, fdec = inc+1;

        ll got1 = check(finc, n/2, fdec), got2 = got1;
        ret += got1;
        if(ret >= mod) ret -= mod;

        if(n & 1) {
            got2 = check(finc, n/2+1, fdec);
            ret += got2;
            if(ret >= mod) ret -= mod;
        }

        if(got1 == 0 && got2 == 0) break;
        //dbg(mp(inc, dec));
        f++;
    }

    return ret;
}

int main()
{
    fac[0] = 1;
    for1(i, sz-1) fac[i] = (fac[i-1]*i) % mod;

    inv[sz-1] = fastPow(fac[sz-1], mod-2, mod);
    rep0(i, sz-1) inv[i] = (inv[i+1]*(i+1)) % mod;

    ll t;
    cin >> t;

    while(t--) {
        sl(n), sl(l), sl(r);

        ll lo = 1, hi = 1e9, safe = 0, h = n/2;

        while(lo <= hi) {
            ll mid = lo+hi>>1;

            if(1-mid < l || n + mid > r)
                hi = mid - 1;
            else {
                safe = mid;
                lo = mid+1;
            }
        }

        ll ans = 0;
        if(n & 1) {
            ll tot = (2 * nCr(n, h)) % mod;
            ans = (safe*tot) % mod;
        }
        else {
            ans = (safe*nCr(n, h)) % mod;
        }

        ans += solve(safe+1);
        if(ans >= mod) ans -= mod;

        pf("%lld\n", ans);
    }

    return 0;
}

