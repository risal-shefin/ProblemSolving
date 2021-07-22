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

const ll sz = 1009;
char s[sz][sz];
ll n, m, k, hor[sz][sz], ver[sz][sz];
pll cell[26];
pair <char, ll> op[(ll)1e5+10];

bool solve(ll r, ll c)
{
    for1(i, k) {
        if(op[i].ff == 'N') {
            ll r2 = r-op[i].ss;
            if(r2 < 1 || ver[c][r]-ver[c][r2-1] > 0)
                return 0;
            r = r2;
        }
        else if(op[i].ff == 'S') {
            ll r2 = r+op[i].ss;
            if(r2 > n || ver[c][r2]-ver[c][r-1] > 0)
                return 0;
            r = r2;
        }
        else if(op[i].ff == 'W') {
            ll c2 = c-op[i].ss;
            if(c2<1 || hor[r][c] - hor[r][c2-1] > 0)
                return 0;
            c = c2;
        }
        else {
            ll c2 = c+op[i].ss;
            if(c2>m || hor[r][c2] - hor[r][c-1] > 0)
                return 0;
            c = c2;
        }
    }

    return 1;
}

int main()
{
    cin >> n >> m;
    for1(i, n)
        scanf("%s", s[i]+1);

    vector <pll> lst;
    for1(i, n) {
        for1(j, m) {
            if(isalpha(s[i][j]))
                cell[ s[i][j] - 'A' ] = {i, j};
            else if(s[i][j] == '#')
                hor[i][j] = ver[j][i] = 1;

            hor[i][j] += hor[i][j-1];
        }
    }

    for1(j, m)
        for1(i, n)
            ver[j][i] += ver[j][i-1];

    cin>>k;
    for1(i, k)
        scanf(" %c %lld", &op[i].ff, &op[i].ss);

    string ans;
    for0(i, 26) {
        if(cell[i].ff != 0 && solve(cell[i].ff, cell[i].ss))
            ans.pb(i+'A');
    }

    if(ans.empty()) pf("no solution\n");
    else cout << ans << EL;

    return 0;
}
