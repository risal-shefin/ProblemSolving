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

const ll sz = 30;
ll ara[sz];

int main()
{
    ll n, odd = 0, g = 0;
    sl(n);

    for0(i, n) {
        sl(ara[i]);

        if(ara[i] & 1) odd++;
        g = __gcd(g, ara[i]);
    }

    if(odd > 1) {
        pf("0\n");

        for0(i, n)
            for0(j, ara[i])
                pf("%c", 'a'+i);
        pn;
        return 0;
    }

    cout << g << EL;

    if(g % 2 == 0) {

        string s = "";

        for0(i, n) {
            ll x = ara[i] / g;
            for0(j, x)
                s.pb('a'+i);
        }

        string t = s;
        reverse(all(t));
        s += t;

        for1(i, g/2) cout << s;
        cout << EL;
    }
    else {

        string s = "", t = "";

        for0(i, n) {
            ll x = (ara[i] / g) / 2;
            for0(j, x) {
                s.pb('a'+i);
                t.pb('a'+i);
            }
        }

        for0(i, n) {
            ll x = ara[i] / g;
            if(x & 1) s.pb('a' + i);
        }

        reverse(all(t));
        s += t;

        for1(i, g) cout << s;
        cout << EL;
    }

    return 0;
}
