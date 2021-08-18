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

const ll sz = 5009;
vector <int> lrow[sz], rrow[sz], ucol[sz], dcol[sz];
char mat[sz][sz];

void init(ll n, ll m)
{
    for(int i = 0; i <= n+2; ++i)
        for(int j = 0; j <= m+2; ++j)
            lrow[i][j] = rrow[i][j] = ucol[i][j] = dcol[i][j] = -1;

    for1(i, n) {
        for1(j, m) {

            if(mat[i][j-1] != '.')
                lrow[i][j] = j-1;
            else
                lrow[i][j] = lrow[i][j-1];

            if(mat[i-1][j] != '.')
                ucol[i][j] = i-1;
            else
                ucol[i][j] = ucol[i-1][j];
        }
    }

    rep1(i, n) {
        rep1(j, m) {

            if(mat[i][j+1] != '.')
                rrow[i][j] = j+1;
            else
                rrow[i][j] = rrow[i][j+1];

            if(mat[i+1][j] != '.')
                dcol[i][j] = i+1;
            else
                dcol[i][j] = dcol[i+1][j];
        }
    }
}

ll solve(ll r, ll c)
{
    ll dr = dcol[r][c], ur = ucol[r][c];
    ll lc = lrow[r][c], rc = rrow[r][c];

    if(dr != -1) ucol[dr][c] = ur;
    if(ur != -1) dcol[ur][c] = dr;
    if(rc != -1) lrow[r][rc] = lc;
    if(lc != -1) rrow[r][lc] = rc;

    if(mat[r][c] == 'U') {
        if(ur == -1)
            return 1;

        return 1 + solve(ur, c);
    }
    else if(mat[r][c] == 'D') {
        if(dr == -1)
            return 1;

        return 1 + solve(dr, c);
    }
    else if(mat[r][c] == 'L') {
        if(lc == -1)
            return 1;

        return 1 + solve(r, lc);
    }
    else {
        if(rc == -1)
            return 1;

        return 1 + solve(r, rc);
    }
}

int main()
{
    ms(mat, '.');

    ll n, m;
    cin >> n >> m;
    for1(i, n) {
        scanf("%s", mat[i]+1);
        mat[i][m+1] = '.';
    }

    for(int i = 0; i <= n+5; ++i) {
        lrow[i].resize(m+5), rrow[i].resize(m+5);
        ucol[i].resize(m+5), dcol[i].resize(m+5);
    }

    ll ans = 0, cnt = 0;

    for1(i, n) {
        for1(j, m) {
            if(mat[i][j] == '.')
                continue;

            init(n, m);
            ll got = solve(i, j);

            if(got > ans)
                ans = got, cnt = 1;
            else if(got == ans)
                ++cnt;
        }
    }

    cout << ans << " " << cnt << EL;

    return 0;
}

