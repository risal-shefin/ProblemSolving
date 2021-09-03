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

const ll sz = (1<<16) + 10;
vector <int> g[sz];
unordered_set <int> track[sz];
ll perm[sz], c[sz];
bool done[sz];

void make_perm(ll dim, ll vert)
{
    for0(i, vert) done[i] = 0;
    perm[0] = 0, done[0] = 1;

    for1(i, vert-1) {
        int p1 = -1, p2 = -1;

        for0(b, dim) {
            int p = i^(1<<b);

            if(p < i) {
                if(p1 == -1) p1 = p;
                else if(p2 == -1) p2 = p;
            }
        }

        int u = perm[p1];

        for(int &v : g[u]) {
            if(done[v])
                continue;

            if(p2 == -1 || track[v].find(perm[p2]) != track[v].end()) {
                perm[i] = v, done[v] = 1;
                break;
            }
        }
    }
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n; sl(n);
        ll vert = 1<<n, m = (vert * n) / 2;

        for0(i, vert) g[i].clear(), track[i].clear();

        for1(i, m) {
            ll u, v;
            sl(u), sl(v);

            g[u].pb(v);
            g[v].pb(u);

            track[u].insert(v);
            track[v].insert(u);
        }

        make_perm(n, vert);
        for0(i, vert) pf("%lld ", perm[i]);
        pn;

        if(vert % n != 0) {
            pf("-1\n");
            continue;
        }

        for0(i, vert) {
            ll col = 0;

            for0(b, n) {
                if((i>>b) & 1)
                    col ^= b;
            }

            c[ perm[i] ] = col;
        }

        for0(i, vert) pf("%lld ", c[i]);
        pn;
    }

    return 0;
}

