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

const ll sz = 1e3+10, mod = 1e9 + 7;
ll dp[sz][sz], cnt[sz][sz];
ll nCr[sz][sz], inv[sz], ans[sz];

ll fastPow(ll x, ll n)
{
    ll ret = 1;
    while (n)
    {
        if (n & 1) ret = (ret * x) % mod;
        x = (x * x) % mod;
        n >>= 1;
    }
    return ret % mod;
}

ll way(ll n, ll r)
{
    ll res = 1;
    if( r > n - r ) r = n - r;
    for0(i, r) {
        res = (res * (n - i)) % mod;
        res = (res * inv[i+1]) % mod;
    }
    return res;
}

int main()
{
    ll n, k;
    cin >> n >> k;

    ll mxn = min(n, 2*k);
    nCr[0][0] = 1;

    for1(i, mxn) {
        dp[i][0] = 1;
        nCr[i][0] = 1;

        for1(j, i) {
            if(i == 1) dp[i][j] = 0;
            else dp[i][j] = (dp[i-1][j] + (i-1)*dp[i-1][j-1]) % mod;

            nCr[i][j] = (nCr[i-1][j-1] + nCr[i-1][j]) % mod;
        }
        inv[i] = fastPow(i, mod-2);
    }

    for1(i, mxn) {

        for1(j, i) {
            cnt[i][j] = dp[i][j];

            for1(m, i) {

                if(m & 1) {
                    cnt[i][j] = (cnt[i][j] - nCr[i][m]*dp[i-m][j]) % mod;
                    if(cnt[i][j] < 0) cnt[i][j] += mod;
                }
                else
                    cnt[i][j] = (cnt[i][j] + nCr[i][m]*dp[i-m][j]) % mod;
            }
        }
    }

    ans[0] = 1;
    for1(j, k) {

        if(j>1) ans[j] = ans[j-2];

        for(ll i = j; i <= mxn; i++)
            ans[j] = (ans[j] + way(n, i) * cnt[i][j]) % mod;

        pf("%lld ", ans[j]);
    }
    pn;

    return 0;
}
