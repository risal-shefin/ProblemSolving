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

const ll sz = 105;
char mat[sz][sz];
ll n, m, freq[30];
ll dr[] = {1, -1, 0, 0};
ll dc[] = {0, 0, 1, -1};

char find_char(ll r, ll c)
{
    ms(freq, 0);

    for0(i, 4) {
        ll nr = r+dr[i], nc = c+dc[i];
        if(nr < 1 || nc < 1 || nr > n || nc > m || mat[nr][nc] == '\0')
            continue;

        freq[ mat[nr][nc] - 'A' ]++;
    }
    for0(i, 26) if(freq[i] == 0) return (i+'A');
}

bool chk_char(ll r, ll c, char ch)
{
    for0(i, 4) {
        ll nr = r+dr[i], nc = c+dc[i];
        if(nr < 1 || nc < 1 || nr > n || nc > m)
            continue;

        if(mat[nr][nc] == ch)
            return 0;
    }
    return 1;
}

int main()
{
    cin >> n >> m;

    for1(i, n) {
        for1(j, m) {
            if(mat[i][j] != '\0')
                continue;

            char ch = find_char(i, j);
            ll r = i, c = j;

            while(r+1 <= n && c+1 <= m) {
                bool ok = (find_char(i, c+1)>=ch);

                for(ll k = j; k <= c+1; k++) {
                    ok &= (mat[r+1][k] == '\0');
                    ok &= chk_char(r+1, k, ch);
                }

                for(ll k = i; k <= r+1; k++) {
                    ok &= (mat[k][c+1] == '\0');
                    ok &= chk_char(k, c+1, ch);
                }

                if(!ok) break;

                r++, c++;
            }

            for(ll k = i; k <= r; k++)
                for(ll k2 = j; k2 <= c; k2++)
                    mat[k][k2] = ch;
        }
    }

    for1(i, n) {
        for1(j, m)
            pf("%c", mat[i][j]);
        pn;
    }

    return 0;
}
