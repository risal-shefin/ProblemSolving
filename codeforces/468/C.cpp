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

#define LL __int128

LL dp[2][2][20][180];
vector <int> num;

LL solve(ll isStart, ll isSmall, ll pos, ll sum)
{
    if(pos == 0)
        return sum;

    LL &ret = dp[isStart][isSmall][pos][sum];
    if(ret != -1 && isSmall)
        return ret;

    ll lim, pos2 = num.size() - pos;
    if(isSmall)
        lim = 9;
    else
        lim = num[pos2];

    LL rt = 0;
    if(!isStart)
    {
        for(ll i = 0; i <= lim; i++)
            rt += solve(0, isSmall | i < num[pos2], pos - 1, sum+i);
    }
    else
    {
        for(ll i = 1; i <= lim; i++)
            rt += solve(0, isSmall | i < num[pos2], pos - 1, sum+i);
        rt += solve(1, 1, pos - 1, 0);
    }
    return ret = rt;
}

LL calc(ll n)
{
    ll tmp = n;
    num.clear();
    while(tmp)
    {
        num.pb(tmp % 10);
        tmp /= 10;
    }
    reverse(num.begin(), num.end());
    return solve(1, 0, num.size(), 0);
}

inline ll getSum(ll x)
{
    ll ret = 0;
    while(x) ret += x%10, x /= 10;
    return ret;
}

int main()
{
    ms(dp, -1);

    ll a;
    cin >> a;

    ll lo = 1, hi = a, ret;
    LL cur;

    while(lo <= hi) {
        ll mid = lo+hi>>1;

        LL got = calc(mid);
        if(got < a)
            lo = mid+1;
        else {
            ret = mid, cur = got;
            hi = mid-1;
        }
    }

    ll l = 1, r = ret;

    while(cur != a) {
        if(cur < a) cur += getSum(++r);
        else cur -= getSum(l++);
    }
    //dbg(ret);

    cout << l << " " << r << EL;

    return 0;
}

