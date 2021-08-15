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

const ll sz = 55, sz2 = 1e5 + 10, mod = 998244353;
ll l[sz], r[sz], l2[sz], r2[sz];
ll dp[sz][sz2], pre[sz2], bad[sz2];

int main()
{
    fastio;

    ll n, m;
    cin >> n >> m;

    for1(i, n) cin >> l[i] >> r[i];

    dp[0][0] = 1;
    pre[0] = 1;
    for1(i, m) pre[i] = 1;

    for1(i, n) {

        for(ll j = 1; j <= m; j++) {
            if(j-l[i] < 0)
                continue;

            ll lft = max(0LL, j-r[i]), rgt = j-l[i];

            ll tot = pre[rgt];
            if(lft > 0) tot -= pre[lft-1];

            if(tot < 0) tot += mod;

            dp[i][j] = tot;

            //dbg(mp(j, pre[j]));
        }

        pre[0] = dp[i][0];
        for1(j, m) {
            pre[j] = pre[j-1] + dp[i][j];
            if(pre[j] >= mod) pre[j] -= mod;
        }
    }

    ll good = pre[m];
    //dbg(good);

    for(ll k = 2; k <= m; k++) {
        ll d = m/k;
        if(d < n) break;

        ll ok = 1;
        for1(i, n) {
            l2[i] = l[i] / k;
            if(l[i] % k != 0) l2[i]++;

            r2[i] = r[i]/k;

            if(r2[i] == 0) {
                ok = 0;
                break;
            }
            if(r[i]/k == (l[i]-1)/k || l2[i] > r2[i]) {
                ok = 2;
                break;
            }
        }
        if(!ok) break;
        if(ok == 2) continue;
        //dbg(k);

        dp[0][0] = 1;
        pre[0] = 1;
        for1(i, d) pre[i] = 1;

        for1(i, n) {

            for(ll j = 1; j <= d; j++) {
                if(j-l2[i] < 0) {
                    dp[i][j] = 0;
                    continue;
                }

                ll lft = max(0LL, j-r2[i]), rgt = j-l2[i];

                ll tot = pre[rgt];
                if(lft > 0) tot -= pre[lft-1];

                if(tot < 0) tot += mod;

                dp[i][j] = tot;

                //dbg(mp(j, pre[j]));
            }

            pre[0] = dp[i][0];
            for1(j, d) {
                pre[j] = pre[j-1] + dp[i][j];
                if(pre[j] >= mod) pre[j] -= mod;
            }
        }

        //dbg(mp(k, pre[d]));
        bad[k] = pre[d];
    }

    for(ll i = m; i >= 2; i--) {
        for(ll j = i+i; j <= m; j += i) {
            bad[i] -= bad[j];
            if(bad[i] < 0) bad[i] += mod;
        }
        //dbg(mp(i, bad[i]));

        good -= bad[i];
        if(good < 0) good += mod;
    }

    cout << good << EL;

    return 0;
}


