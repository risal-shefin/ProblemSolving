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

const ll mod = 1e9 + 7, sz = 2e5 + 10;
pll ara[sz];
vector <ll> s[sz], num;
ll dp[sz];

int main()
{
    ll n, m;
    cin >> n >> m;
    num.pb(0), num.pb(n);

    for1(i, m) {
        sl(ara[i].ff), sl(ara[i].ss);
        num.pb(ara[i].ff), num.pb(ara[i].ss);
    }
    sort(all(num));
    num.erase(unique(all(num)), num.end());

    for1(i, m) {
        ll l = lower_bound(all(num), ara[i].ff) - num.begin();
        ll r = lower_bound(all(num), ara[i].ss) - num.begin();

        s[r].pb(l);
    }

    ll n2 = num.size()-1, now = s[n2].size();
    for(ll &l : s[n2]) dp[l]++;

    for(ll i = num.size()-2; i >= 0; i--) {
        ll cur = 0;

        for(ll &l : s[i]) {
            cur += now;
            if(cur >= mod) cur -= mod;

            dp[l] += now;
            if(dp[l] >= mod) dp[l] -= mod;
        }
        now += cur;
        if(now >= mod) now -= mod;

        now -= dp[i];
        if(now < 0) now += mod;
    }

    cout << dp[0] << EL;

    return 0;
}
