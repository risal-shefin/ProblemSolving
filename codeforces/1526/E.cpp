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

// === Debug macro starts here ===
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
// === Debug macro ends here ===

#define ff first
#define ss second

const ll sz = 2e5 + 10, fsz = 2*sz, mod = 998244353;
ll ara[sz], pos[sz], fact[fsz], inv[fsz];

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
    return (fact[n]*den) % mod;
}

// n objects, k bins (empty bins are valid)
inline ll starsBars(ll n, ll k)
{
    return nCr(n+k-1, k-1);
}

int main()
{
    fact[0] = 1;
    for1(i, fsz-1) fact[i] = (fact[i-1]*i) % mod;

    inv[fsz-1] = fastPow(fact[fsz-1], mod-2, mod);
    rep0(i, fsz-1) inv[i] = (inv[i+1]*(i+1)) % mod;

    ll n, k;
    cin >> n >> k;

    for1(i, n) {
        sl(ara[i]);
        pos[ ara[i] ] = i;
    }
    pos[n] = -1;

    ll big = 0;
    for1(i, n-1) {
        ll id1 = ara[i], id2 = ara[i+1];
        if(pos[id1+1] > pos[id2+1])
            big++;
    }

    if(big >= k) {
        pf("0\n");
        return 0;
    }

    cout << starsBars(k-1-big, n+1) << EL;

    return 0;
}
