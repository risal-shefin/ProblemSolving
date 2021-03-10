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

const ll sz = 1e5 + 10;
ll ara[sz];

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n, k;
        sl(n), sl(k);

        for1(i, n) sl(ara[i]);

        if(k == 0) {
            pf("%lld\n", n);
            continue;
        }

        sort(ara+1, ara+n+1);

        ll prv = -1, mis = ara[n]+1;

        for1(i, n) {
            if(ara[i]-prv > 1) {
                mis = prv+1;
                break;
            }
            prv = ara[i];
        }

        //dbg(mis);

        if(mis == ara[n]+1) {
            pf("%lld\n", n+k);
            continue;
        }

        ll val = (ara[n] + mis) / 2;
        if((ara[n] +  mis) & 1)
            val++;

        //dbg(val);

        ll ans = n, add = 1;
        for1(i, n) {
            if(val == ara[i])
                add = 0;
        }
        pf("%lld\n", ans+add);
    }

    return 0;
}
