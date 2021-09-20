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

const ll sz = 410;
vector <int> conf[sz], cube[6];
map <vector<int>, int> cnt, done, same;

vector <int> make_lex_small(vector <int> v)
{
    vector <int> ret2({v[1], v[2], v[3], v[0]}), ret3({v[2], v[3], v[0], v[1]}),
                ret4({v[3], v[0], v[1], v[2]});

    return min({v, ret2, ret3, ret4});
}

inline int same_count(vector <int> v)
{
    vector <int> ret2({v[1], v[2], v[3], v[0]}), ret3({v[2], v[3], v[0], v[1]}),
                ret4({v[3], v[0], v[1], v[2]});

    return 1 + (ret2==v) + (ret3 == v) + (ret4 == v);
}

int main()
{
    ll n;
    cin >> n;

    for1(i, n) {
        ll c0, c1, c2, c3;
        sl(c0), sl(c1), sl(c2), sl(c3);

        conf[i] = make_lex_small({c0, c1, c2, c3});
        ++cnt[ conf[i] ];
        same[ conf[i] ] = same_count(conf[i]);
    }

    ll ans = 0;

    for1(i, n) {
        for1(j, n) {
            if(i == j)
                continue;

            cube[0] = conf[i];

            for0(y, 4) {

                cube[1].clear();

                ll ptr = y;
                do {
                    cube[1].pb(conf[j][ptr]);
                    ptr++;
                    if(ptr == 4) ptr = 0;
                } while(ptr != y);

                reverse(all(cube[1]));

                done[ conf[i] ] += same[ conf[i] ], done[ conf[j] ] += same[ conf[j] ];

                ll way = 1;

                for0(k, 4) {
                    int nxt = (k+1 == 4)? 0 : k+1;

                    vector <int> cur = make_lex_small({cube[0][nxt], cube[0][k], cube[1][k], cube[1][nxt]});
                    //if(i == 2 && j == 4 && cube[0] == vector<int>({0, 4, 6, 1}) && cube[1] == vector<int>({3, 5, 7, 2})) dbg(cur);
                    if(cnt.find(cur) == cnt.end()) {
                        way = 0;
                        break;
                    }

                    way = (way * ((ll)cnt[cur]*same[cur] - done[cur]));
                    done[cur] += same[cur];
                }
                ans += way;
                done.clear();
            }
        }
    }

    cout << ans/6 << EL;

    return 0;
}

