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

ll a, b, w, h;
inline ll sq(ll x) {return x*x;}

ll solve1(ll x1, ll y1, ll x2, ll y2)
{
    ll x = a, y = b, dx = 0, dy = 0, ret = inf;

    if(y1 <= y && x1 <= x) {
        dy = max(0LL, y-y1);
        dx = max(0LL, x-x1);

        y2 += dy, x2 += dx;
    }
    if(y2 <= h) ret = min(ret, dy);
    if(x2 <= w) ret = min(ret, dx);

    return ret;
}

ll solve2(ll x1, ll y1, ll x2, ll y2)
{
    ll x = w-a, y = b, dx = 0, dy = 0, ret = inf;

    if(y1 < y && x2 > x) {
        dy = max(0LL, y-y1);
        dx = max(0LL, x2-x);

        y2 += dy, x1 -= dx;
    }
    if(y2 <= h) ret = min(ret, dy);
    if(x1 >= 0) ret = min(ret, dx);

    return ret;
}

ll solve3(ll x1, ll y1, ll x2, ll y2)
{
    ll x = a, y = h-b, dx = 0, dy = 0, ret = inf;

    if(y2 > y && x1 < x) {
        dy = max(0LL, y2-y);
        dx = max(0LL, x-x1);

        y1 -= dy, x2 += dx;
    }
    if(y1 >= 0) ret = min(ret, dy);
    if(x2 <= w) ret = min(ret, dx);

    return ret;
}

ll solve4(ll x1, ll y1, ll x2, ll y2)
{
    ll x = w-a, y = h-b, dx = 0, dy = 0, ret = inf;

    if(y2 > y && x2 > x) {
        dy = max(0LL, y2-y);
        dx = max(0LL, x2-x);

        y1 -= dy, x1 -= dx;
    }
    if(y1 >= 0) ret = min(ret, dy);
    if(x1 >= 0) ret = min(ret, dx);

    return ret;
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        sl(w), sl(h);

        ll x1, y1, x2, y2;
        sl(x1), sl(y1), sl(x2), sl(y2);

        sl(a), sl(b);

        ll got = min({solve1(x1, y1, x2, y2), solve2(x1, y1, x2, y2), solve3(x1, y1, x2, y2), solve4(x1, y1, x2, y2)});

        if(got == inf)
            pf("-1\n");
        else
            pf("%lld\n", got);
    }

    return 0;
}
