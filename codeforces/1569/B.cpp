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

const ll sz = 55;
char mat[sz][sz], s[sz];

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n; sl(n);
        scanf("%s", s+1);

        vector <int> w, l;

        for1(i, n) {
            if(s[i] == '1') w.pb(i);
            else l.pb(i);
        }

        if(l.size() == 1 || l.size() == 2) {
            pf("NO\n");
            continue;
        }

        for0(i, w.size()) {
            for(ll j = i+1; j < w.size(); j++) {
                mat[ w[i] ][ w[j] ] = mat[ w[j] ][ w[i] ] = '=';
            }

            for(int &x : l) {
                mat[ w[i] ][x] = '+';
                mat[x][ w[i] ] = '-';
            }

            mat[w[i]][w[i]] = 'X';
        }

        for0(i, l.size()) {
            int nxt = i+1;
            if(nxt == l.size()) nxt = 0;
            nxt = l[nxt];

            mat[ l[i] ][nxt] = '+';
            mat[nxt][ l[i] ] = '-';

            for(ll j = i+2; j < l.size(); j++) {
                mat[ l[i] ][ l[j] ] = '-';
                mat[ l[j] ][ l[i] ] = '+';
            }

            mat[ l[i] ][ l[i] ] = 'X';
        }

        pf("YES\n");
        for1(i, n) {
            for1(j, n)
                pf("%c", mat[i][j]);
            pn;
        }
    }

    return 0;
}
