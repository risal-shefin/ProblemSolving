#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma")

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

const ll sz = 5005;
double prob[sz][sz], p[sz];
ll t[sz];

int main()
{
    fastio;

    ll n, T;
    cin >> n >> T;

    for1(i, n) {
        cin >> p[i] >> t[i];
        p[i] /= 100.0;
    }

    double ans = 0, got;
    prob[0][0] = 1;

    for1(i, n) {
        double pwt = pow(1-p[i], t[i]), pwt1 = pow(1-p[i], t[i]-1);

        for1(j, T) {

            if(t[i] == 1) {
                prob[i][j] = prob[i-1][j-1];
            }
            else if(j < t[i]) {
                prob[i][j] = prob[i-1][j-1]*p[i] + prob[i][j-1]*(1-p[i]);
            }
            else {
                got = prob[i][j-1]*(1-p[i]);

                if(j > t[i]) got -= prob[i-1][ j - (t[i]+1) ] * pwt;

//                got -= prob[i-1][ j-t[i] ] * pw[ t[i]-1 ] * p[i];
//                got += prob[i-1][ j-t[i] ] * pw[ t[i]-1 ];
                got += prob[i-1][ j-t[i] ] * pwt1 * (1 - p[i]);

                prob[i][j] = prob[i-1][j-1]*p[i] + got;
            }
            ans += prob[i][j];
        }
    }

    cout << setprecision(6) << fixed << ans << endl;

    return 0;
}
