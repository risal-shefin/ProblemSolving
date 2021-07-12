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

const ll sz = 1005, mod = 998244353;
ll mat[sz][505], n, m;
vector <int> alive, ans;
int cnt[505];

void del_sim(int r)
{
    for(int k = 0; k < alive.size(); k++) {
        int i = alive[k];

        for1(c, n) {
            if(mat[i][c] == mat[r][c]) {

                alive.erase(alive.begin()+k);
                k--;
                break;
            }
        }
    }
}

int main()
{
    fastio;

    ll t;
    cin >> t;

    while(t--) {
        cin >> n;
        m = 2*n;

        for1(i, m) {
            for1(j, n)
                cin >> mat[i][j];

            alive.pb(i);
        }

        ll tot = 1;

        while(!alive.empty()) {
            ll x = -1;

            for1(j, n) {
                ms(cnt, 0);

                for(int &i : alive) cnt[ mat[i][j] ]++;

                for1(k, n) {
                    if(cnt[k] == 1) {
                        x = k;
                        break;
                    }
                }
                if(x == -1) continue;

                ll r;
                for(int &i : alive) if(mat[i][j] == x) r = i;

                ans.pb(r);
                del_sim(r);
                break;
            }
            if(x != -1) continue;

            tot = (tot * 2) % mod;
            ans.pb(alive[0]);
            del_sim(alive[0]);
        }

        cout << tot << EL;
        for(int &x : ans) cout << x << " ";
        cout << EL;

        ans.clear();
        alive.clear();
    }

    return 0;
}
