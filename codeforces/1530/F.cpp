//#pragma GCC optimize("Ofast,unroll-loops")
//#pragma GCC target("avx,avx2,fma")

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
#define for1(i, stop) for(int i = 1; i <= stop; ++i)
#define for0(i, stop) for(int i = 0; i < stop; ++i)
#define rep1(i, start) for(int i = start; i >= 1; --i)
#define rep0(i, start) for(int i = (start-1); i >= 0; --i)
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

const int mod = 31607, sz = 21;
int a[sz][sz], ia[sz][sz], rp[sz], cp[sz], d1=1, d2=1, n;
int lim, mdg, adg, idx, dp[sz][2], rowp[sz];

ll fastPow(ll x, ll n, ll MOD)
{
    ll ret = 1;
    while (n)
    {
        if (n & 1) ret = (ret * x) % MOD;
        x = (x * x) % MOD;
        n >>= 1;
    }
    return ret % MOD;
}

int solve(int r, int odd)
{
    if(r==n) {
        if(odd) return 1;
        else return -1;
    }

    int &ret = dp[r][odd];
    if(ret != -1)
        return ret;

    ret = solve(r+1, odd);

    ret = (ret + rowp[r]*solve(r+1, odd^1)) % mod;
    if(ret < 0) ret += mod;

    return ret;
}

int main()
{
    const int vag = fastPow(1e4, mod-2, mod);

    cin >> n;
    for0(i, n) {
        rp[i] = 1;

        for0(j, n) {
            si(a[i][j]);
            a[i][j] = (a[i][j] * vag) % mod;
            ia[i][j] = fastPow(a[i][j], mod-2, mod);

            rp[i] = (rp[i] * a[i][j]) % mod;
        }

        d1 = (d1*a[i][i] ) % mod;
        d2 = (d2*a[i][n-i-1]) % mod;
    }

    for0(j, n) {
        cp[j] = 1;
        for0(i, n)
            cp[j] = (cp[j] * a[i][j]) % mod;
    }

    lim = 1<<(n+2), mdg = n, adg = n+1;
    int ans = 0;

    for0(msk, lim) {
        int prob = 1, cnt = 0;

        for0(r, n) {
            rowp[r] = rp[r];

            if((msk>>mdg) & 1) {
                if(!((msk>>r) & 1))
                    rowp[r] = (rowp[r]*ia[r][r]) % mod;
            }

            if((msk>>adg) & 1) {
                int c = n-r-1;

                if(!((msk>>c)&1) && !( ((msk>>mdg)&1) && c==r) )
                    rowp[r] = (rowp[r] * ia[r][c]) % mod;
            }
        }

        for0(j, n) {
            if((msk>>j)&1) {
                ++cnt;
                prob = (cp[j] * prob) % mod;

                if((msk>>mdg) & 1) prob = (prob * ia[j][j]) % mod;

                if((msk>>adg) & 1) prob = (prob * ia[n-j-1][j]) % mod;

                for0(r, n) rowp[r] = (rowp[r] * ia[r][j]) % mod;
            }
        }

        if((msk>>mdg) & 1) {
            cnt++;
            prob = (prob*d1) % mod;
        }

        if((msk>>adg) & 1) {
            cnt++;
            prob = (prob*d2) % mod;

            int pnt = n/2;
            if((n&1) && ((msk>>mdg)&1) && !((msk>>pnt)&1)) prob = (prob*ia[pnt][pnt]) % mod;
        }

        ms(dp, -1);
        ans = (ans + prob*solve(0, cnt&1)) % mod;
        if(ans < 0) ans += mod;
    }

    pf("%d\n", (ans+1)%mod);  // +1 because zero line will add -1 to the ans

    return 0;
}
