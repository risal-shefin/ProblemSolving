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

struct info {
    string s;
    ll id;

    const bool operator <(const info &rhs) {
        return s < rhs.s;
    }
};

ll len[5009];
int mat[5009][5009];

int main()
{
    fastio;

    ll t;
    cin >> t;

    while(t--) {
        vector <info> v;

        ll n;
        cin >> n;

        string s;
        cin >> s;

        for(ll i = 0; i < s.size(); i++) {
            string tmp = "";
            for(ll j = i; j < s.size(); j++) {
                tmp.pb(s[j]);
            }

            v.pb({tmp, i});
        }
        sort(all(v));

        for(ll i = (ll)v.size()-2; i >= 0; i--) {
            ll same = 0;

            for(ll j = 0; j < min(v[i].s.size(), v[i+1].s.size()); j++) {
                if(v[i].s[j] != v[i+1].s[j])
                    break;

                same++;
            }
            mat[v[i].id][v[i+1].id] = mat[v[i+1].id][v[i].id] = same;

            for(ll j = i+2; j < v.size(); j++)
                mat[ v[i].id ][ v[j].id ] = mat[ v[j].id ][ v[i].id ] = min(same, (ll)mat[v[i+1].id][v[j].id]);
            //dbg(ptr);
        }

        ll ans = 0;

        for(ll i = 0; i < v.size(); i++) {

            ll tot = v[i].s.size(), mx = 0;

            for(ll j = 0; j < v[i].id; j++) {
                mx = max(mx, len[j] - mat[ v[i].id ][j]);
                //if(len[j]+tot==18) dbg(j);
            }

            ans = max(ans, tot+mx);
            len[ v[i].id ] = mx+tot;

            //dbg(mp(v[i].id, mx+tot));
        }
        for(ll i = 0; i <= n; i++) {
            len[i] = 0;
            for(ll j = 0; j <= n; j++)
                mat[i][j] = 0;
        }

        cout << ans << EL;
    }

    return 0;
}
