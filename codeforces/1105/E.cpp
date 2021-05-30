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

// === Debug macro starts here ===
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
// === Debug macro ends here ===

#define ff first
#define ss second

unordered_map <string, int> track;
int inv1[(1<<20)], inv2[(1<<20)], nxt[(1<<20)], dp[(1<<20)];
int n, m, h;

inline ll bitCount(ll x)
{
    ll ret = 0;
    while(x) ret++, x &= (x-1);
    return ret;
}

void calc_invalid(int msk1, int msk2)
{
    for0(i, h) {
        if(!((msk1>>i) & 1))
            continue;

        inv1[i] |= msk1^(1<<i);
        nxt[i] |= msk2;
    }

    ll rest = m-h;
    for0(i, rest) {
        if(!((msk2>>i) & 1))
            continue;

        inv2[i] |= msk2^(1<<i);
    }
}

int main()
{
    cin >> n >> m;

    int msk1 = 0, msk2 = 0, id = 0;
    h = m/2 + (m&1);

    for1(i, n) {
        ll op; sl(op);

        if(op == 1) {
            calc_invalid(msk1, msk2);
            msk1 = msk2 = 0;
        }
        else {
            string s; cin>>s;
            ll now;

            if(track.find(s) != track.end())
                now = track[s];
            else {
                now = id;
                track[s] = id++;
            }

            if(now < h)
                msk1 |= (1<<now);
            else
                msk2 |= (1<<(now-h));
        }
    }
    calc_invalid(msk1, msk2);

    ll ans = 0, lim1 = 1<<h, lim2 = 1<<(m-h);

    for0(msk, lim2) {
        ll rest = m-h, bad = 0;

        for0(i, rest) {
            if(!((msk>>i)&1))
                continue;

            bad |= inv2[i];
        }

        if((msk&bad) == 0) dp[msk] = bitCount(msk);
        ans = max(ans, (ll)dp[msk]);
    }

    // SOS DP
    for(int i = 0; i < (m-h); ++i) {
        for(int mask = 0; mask < lim2; ++mask){
            if(mask & (1<<i))
                dp[mask] = max(dp[mask], dp[mask^(1<<i)]);
        }
    }

    for0(msk, lim1) {
        ll bad = 0, badNxt = 0, rest = m-h;

        for0(i, h) {
            if(!((msk>>i)&1))
                continue;

            bad |= inv1[i];
            badNxt |= nxt[i];
        }

        ll valid2 = ((1<<rest)-1) ^ badNxt;
        //dbg(dp[valid2]);

        if((msk&bad) == 0) ans = max(ans, dp[valid2] + bitCount(msk));
        //dbg(mp(msk, ans));
    }

    cout << ans << EL;

    return 0;
}
