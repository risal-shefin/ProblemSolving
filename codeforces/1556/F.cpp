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

const ll sz = 14, isz = 2e6 + 10, mod = 1e9 + 7;
ll p[sz], win[sz][sz], scc[(1<<sz)], n;

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

inline ll inv(ll x)
{
    return fastPow(x, mod-2, mod);
}

ll prob(ll from, ll to)
{
    ll ret = 1;

    for0(i, n) {
        for0(j, n) {
            if((from>>i & 1) && (to>>j & 1))
                ret = (ret * win[i][j]) % mod;
        }
    }

    return ret;
}

int main()
{
    fastio;
    cin >> n;

    for0(i, n)
        cin >> p[i];


    for0(i, n)
        for0(j, n)
            win[i][j] = (p[i] * inv(p[i]+p[j])) % mod;

    ll ans = 0, lim = (1<<n)-1;

    // SOS-DP: Suboptimal Bruteforce Method O(3^n):
    // iterate over all the masks
    for (int mask = 0; mask <= lim; mask++) {
        scc[mask] = 1;

        // iterate over all the subsets of the mask
        for(int i = mask; i > 0; i = (i-1) & mask) {
            if(i == mask)
                continue;

            scc[mask] -= (scc[i] * prob(i, mask^i)) % mod;
            if(scc[mask] < 0)
                scc[mask] += mod;
        }

        ll win_prob = (scc[mask] * __builtin_popcount(mask)) % mod;
        win_prob = (win_prob * prob(mask, lim^mask)) % mod;

        ans += win_prob;
        if(ans >= mod) ans -= mod;
    }

    cout << ans << EL;

    return 0;
}
