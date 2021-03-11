// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
using namespace std;

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

const ll sz = 505;
char mat[sz][sz];

void printAns(ll n, ll m)
{
    for1(i, n) {
        for1(j, m) {
            pf("%c", mat[i][j]);
        }
        pn;
    }
}

void joinCol(ll start, ll n, ll m)
{
    for(ll j = start; j+3 <= m; j += 3) {

        ll nxt = j+3, fnd = 1;

        for1(i, n) {

            if(mat[i][j+1] == 'X' || mat[i][nxt-1] == 'X') {
                fnd = i;
                break;
            }
        }

        for(ll i = j; i <= nxt; i++)
            mat[fnd][i] = 'X';
    }
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n, m;
        sl(n), sl(m);

        for1(i, n)
            scanf("%s", mat[i]+1);

        if(m % 3 != 0) {

            for1(i, n) {
                for(ll j = 1; j <= m; j += 3)
                    mat[i][j] = 'X';
            }

            joinCol(1, n, m);
        }
        else {

            for1(i, n) {
                for(ll j = 2; j <= m; j += 3)
                    mat[i][j] = 'X';
            }

            joinCol(2, n, m);
        }

        printAns(n, m);
    }

    return 0;
}
