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

ll dx[] = {1, -1, -2, -1, 1, 2};
ll dy[] = {2, 2, 0, -2, -2, 0};
ll cnt[] = {1, 0, 1, 1, 1, 1};

inline ll step(ll rnd)
{
    return 6*((rnd*(rnd+1))/2) - rnd;
}

int main()
{
    ll n, x = 0, y = 0;
    sl(n);

    ll lo = 1, hi = 1e9, ret = 0, bad = 0;
    while(lo <= hi) {
        ll mid = lo+hi>>1;

        if(step(mid) <= n) {
            ret = mid;
            lo = mid + 1;
        }
        else
            hi = mid-1;
    }
    if(ret > 0) bad = step(ret);

    n -= bad, x += ret*dx[4], y += ret*dy[4];
    //dbg(n);

    ll idx = 0;

    while(n) {
        cnt[idx] += ret;
        ll len = min(n, cnt[idx]);

        x += len*dx[idx], y += len*dy[idx];

        idx++, n -= len;
    }

    cout << x << " " << y << EL;

    return 0;
}
