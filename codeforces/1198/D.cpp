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

const ll sz = 52;
int dp[sz][sz][sz][sz], pre[sz][sz];
char mat[sz][sz];

inline int getCount(int r1, int c1, int r2, int c2)
{
    return pre[r2][c2] - pre[r1-1][c2] - pre[r2][c1-1] + pre[r1-1][c1-1];
}

int solve(int r1, int c1, int r2, int c2)
{
    if(r1 == r2 && c1 == c2)
        return (mat[r1][c1] == '#');

    int &ret = dp[r1][r2][c1][c2];
    if(ret != -1)
        return ret;

    if(getCount(r1, c1, r2, c2) == 0)
        return ret = 0;

    ret = max(r2-r1+1, c2-c1+1);

    for(int i = r1; i < r2; i++) ret = min(ret, solve(r1, c1, i, c2) + solve(i+1, c1, r2, c2));
    for(int i = c1; i < c2; i++) ret = min(ret, solve(r1, c1, r2, i) + solve(r1, i+1, r2, c2));

    return ret;
}

int main()
{
    int n; cin>>n;
    for1(i, n) scanf("%s", mat[i]+1);

    for1(i, n) {
        int sum = 0;
        for1(j, n) {
            sum += (mat[i][j] == '#');
            pre[i][j] = pre[i-1][j] + sum;
        }
    }

    ms(dp, -1);
    cout << solve(1, 1, n, n) << EL;

    return 0;
}
