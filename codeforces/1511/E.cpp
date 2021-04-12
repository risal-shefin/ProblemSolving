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
#else
#define dbg(x)
#endif
// === Debug macro ends here ===

#define ff first
#define ss second

const ll sz = 3e5 + 10, mod = 998244353;
vector <ll> dp[sz], way[sz];
vector <char> mat[sz];
ll n, m;

ll way1(ll r, ll c)
{
    if(r > n)
        return 1;

    ll &ret = way[r][c];
    if(ret != -1)
        return ret;

    if(c == m) {
        if(mat[r][c] != 'o')
            return ret = way1(r+1, 1);
        return ret = (2*way1(r+1, 1)) % mod;
    }

    ret = way1(r, c+1);
    if(mat[r][c] == 'o') ret = (2*ret) % mod;

    return ret;
}

ll way2(ll r, ll c)
{
    if(c > m)
        return 1;

    ll &ret = way[r][c];
    if(ret != -1)
        return ret;

    if(r == n) {
        if(mat[r][c] != 'o')
            return ret = way2(1, c+1);
        return ret = (2*way2(1, c+1)) % mod;
    }

    ret = way2(r+1, c);
    if(mat[r][c] == 'o') ret = (2*ret) % mod;

    return ret;
}

ll solve1(ll r, ll c)
{
    if(r > n)
        return 0;

    ll &ret = dp[r][c];
    if(ret != -1)
        return ret;

    ret = 0;
    if(c == m) {
        ret = solve1(r+1, 1);

        if(mat[r][c] == 'o')
            ret = 2*ret;

        if(ret >= mod) ret -= mod;
        return ret;
    }

    if(mat[r][c] == 'o') ret = solve1(r, c+1);

    if(mat[r][c] != 'o' || mat[r][c+1] != 'o') {
        ret += solve1(r, c+1);
        if(ret >= mod) ret -= mod;
        return ret;
    }

    if(c+1 == m) {
        ret += way1(r+1, 1) +solve1(r+1, 1);
        ret += solve1(r+1, 1);
    }
    else {
        ret += way1(r,c+2) + solve1(r, c+2);
        ret += solve1(r, c+2);
    }

    ret %= mod;
    //cerr << r << " " << c << " || " << ret << endl;
    return ret;
}

ll solve2(ll r, ll c)
{
    if(c > m)
        return 0;

    ll &ret = dp[r][c];
    if(ret != -1)
        return ret;

    ret = 0;
    if(r == n) {
        ret = solve2(1, c+1);

        if(mat[r][c] == 'o')
            ret = 2*ret;

        if(ret >= mod) ret -= mod;
        return ret;
    }

    if(mat[r][c] == 'o') ret = solve2(r+1, c);

    if(mat[r][c] != 'o' || mat[r+1][c] != 'o') {
        ret += solve2(r+1, c);
        if(ret >= mod) ret -= mod;
        return ret;
    }

    if(r+1==n) {
        ret += way2(1, c+1) + solve2(1, c+1);
        ret += solve2(1, c+1);
    }
    else {
        ret += way2(r+2, c) + solve2(r+2, c);
        ret += solve2(r+2, c);
    }

    ret %= mod;
    return ret;
}

int main()
{
    cin >> n >> m;

    for1(i, n) {
        dp[i].resize(m+2, -1);
        way[i].resize(m+2, -1);
        mat[i].resize(m+2);
    }

    for1(i, n) {
        for1(j, m) {
            scanf(" %c", &mat[i][j]);
        }
    }

    ll ans1 = solve1(1, 1);
    //dbg(ans1);

    for1(i, n)
        for1(j, m)
            dp[i][j] = way[i][j] = -1;

    ll ans2 = solve2(1, 1);
    //dbg(ans2);

    cout << (ans1+ans2) % mod << EL;

    return 0;
}

