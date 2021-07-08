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

const ll mod = 1e9 + 7;
ll n, ans, val[50];

bool isPrime(ll x)
{
    for(ll i = 2; i*i <= x; i++) {
        if(x % i == 0)
            return 0;
    }
    return 1;
}

int main()
{
    vector <int> lst;
    for(ll i = 2; i <= 41; i++) {
        if(isPrime(i)) {
            lst.pb(i);

            ll now = i*i;
            while(now <= 41) {
                lst.pb(now);
                now *= i;
            }
        }
    }
    sort(all(lst));


    ll t;
    cin >> t;

    while(t--) {
        sl(n);

        ans = 0;

        for(ll i = 0; i < lst.size(); i++) {

            ll p = lst[i], sum = 0, lcm = p;

            for(ll j = i-1; j >= 0; j--) {
                ll p2 = lst[j];
                lcm = (lcm*p2) / __gcd(lcm, p2);

                sum += val[j];
            }
            ll sob = n-(n/lcm);

            val[i] = sob - sum;

            ans += (val[i]*p)%mod;
            if(ans >= mod) ans -= mod;
        }

        pf("%lld\n", ans);
    }

    return 0;
}

