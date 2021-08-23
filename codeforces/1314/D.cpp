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

const ll sz = 82;
ll mat[sz][sz], lst[6], idx, n, k;
set <pii> dist[sz][sz];

inline ll find_cst(ll u, ll v)
{
    for(const pii &p : dist[u][v]) {
        bool ok = 1;

        for0(i, idx) {
            if(p.ss == lst[i]) {
                ok = 0;
                break;
            }
        }

        if(ok) return p.ff;
    }
    return inf;
}

ll solve(ll k)
{
    if(k == 0) {
        ll ret = 0;
        lst[idx] = 1;

        for0(i, idx) {
            ret += find_cst(lst[i], lst[i+1]);
            if(ret >= inf) break;
        }

        return ret;
    }

    ll ret = inf;
    for1(i, n) {
        lst[idx++] = i;
        ret = min(ret, solve(k-2));
        idx--;
    }

    return ret;
}

int main()
{
    fastio;
    cin >> n >> k;

    for1(i, n)
        for1(j, n)
            cin >> mat[i][j];

    for1(i, n) {
        for1(j, n) {
            for1(k, n) {
                if(i == k || j == k)
                    continue;

                ll cst = mat[i][k] + mat[k][j];
                dist[i][j].insert(mp(cst, k));

                if(dist[i][j].size() > 4)
                    dist[i][j].erase(--dist[i][j].end());
            }
        }
    }

    lst[idx++] = 1;
    cout << solve(k-2) << EL;

    return 0;
}
