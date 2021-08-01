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

const ll sz = 2e5 + 10, LN = 19;
ll ara[sz], dif[sz], gt[sz][LN], LG[sz];

inline ll GCD(ll l, ll r)
{
    ll len = (r-l+1), k = LG[len];
    //dbg(k);
    return __gcd(gt[l][k], gt[r-(1<<k)+1][k]);
}

int main()
{
    LG[1] = 0;
    for(ll i = 2; i < sz; i++) LG[i] = LG[i/2] + 1;

    ll t;
    cin >> t;

    while(t--) {
        ll n; sl(n);

        for1(i, n) sl(ara[i]);

        if(n == 1) {
            pf("1\n");
            continue;
        }

        for1(i, n-1) {
            dif[i] = abs(ara[i+1] - ara[i]);
            gt[i][0] = dif[i];
        }

        ll m = n-1;
        for1(i, LN-1) {
            for(ll j = 1; j+(1<<i)-1 <= n; j++) {
                gt[j][i] = __gcd(gt[j][i-1], gt[j + (1<<(i-1)) ][i-1]);
            }
        }
        //dbg(GCD(3, 4));

        ll ans = 1;

        for1(i, m) {
            ll lo = i, hi = m, ret = 0;

            while(lo <= hi) {
                ll mid = (lo+hi>>1);

                if(GCD(i, mid) != 1) {
                    ret = mid-i+1;
                    lo = mid+1;
                }
                else
                    hi = mid-1;
            }

            ans = max(ans, ret+1);
        }

        pf("%lld\n", ans);
    }

    return 0;
}
