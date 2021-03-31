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
#define dbg(x) {++recur_depth; auto x_=x; --recur_depth; SYS_COL; cerr<<string(recur_depth, '\t')<<"\e[91m"<<__func__<<":"<<__LINE__<<"\t"<<#x<<" = "<<x_<<"\e[39m"<<endl;}
#else
#define dbg(x)
#endif
template<typename Ostream, typename Cont>
typename enable_if<is_same<Ostream,ostream>::value, Ostream&>::type operator<<(Ostream& os,  const Cont& v){
	os<<"[";
	for(auto& x:v){os<<x<<", ";}
	return os<<"]";
}
template<typename Ostream, typename ...Ts>
Ostream& operator<<(Ostream& os,  const pair<Ts...>& p){
	return os<<"{"<<p.first<<", "<<p.second<<"}";
}
// === Debug macro ends here ===

#define ff first
#define ss second

const ll sz = 1009, mod = 1e9 + 7;
ll dp[sz][sz][2], n;

ll solve(ll pos, ll k, bool d)
{
    if(k == 1 || pos < 1 || pos > n)
        return 1;

    ll &ret = dp[pos][k][d];
    if(ret != -1)
        return ret;

    ret = 0;
    if(d) {
        ret += solve(pos+1, k, d);
        ret += solve(pos-1, k-1, d^1);
    }
    else {
        ret += solve(pos-1, k, d);
        ret += solve(pos+1, k-1, d^1);
    }

    ret %= mod;
    return ret;
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {

        ll k;
        sl(n),sl(k);

        for0(i, n+1)
            for0(j, k+1)
                dp[i][j][0] = dp[i][j][1] = -1;

        pf("%lld\n", solve(1, k, 1));
    }

    return 0;
}
