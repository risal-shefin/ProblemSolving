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

const ll sz = 1e5 + 10;
ll ara[sz], pre[sz];

struct pnt {
    ll x, y;
} p[sz], tmp[sz], strip[sz];

inline bool cmpX(const pnt &a, const pnt &b) {
    if(a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

inline bool cmpY(const pnt &a, const pnt &b) {
    return a.y < b.y;
}

inline ll sq(ll x) {return x*x;}

inline ll dist(const pnt &a, const pnt &b) {
    return sq(a.x-b.x) + sq(a.y-b.y);
}

void Merge(ll lo, ll hi)
{
    ll mid = lo+hi>>1, l = lo, r = mid+1;

    for(ll i = lo; i <= hi; i++) {

        if(r > hi) tmp[i] = p[l++];
        else if(l > mid) tmp[i] = p[r++];
        else if(cmpY(p[l], p[r])) tmp[i] = p[l++];
        else tmp[i] = p[r++];
    }

    for(ll i = lo; i <= hi; i++) p[i] = tmp[i];
}

ll closestPoint(ll lo, ll hi)
{
    if(hi-lo+1 <= 3) {
        ll d = inf;

        for(ll i = lo; i <= hi; i++) {
            for(ll j = i+1; j <= hi; j++)
                d = min(d, dist(p[i], p[j]));
        }

        sort(p+lo, p+hi+1, cmpY);
        return d;
    }

    ll mid = lo+hi>>1, midx = p[mid].x;
    ll d1 = closestPoint(lo, mid), d2 = closestPoint(mid+1, hi);
    ll d = min(d1, d2);

    Merge(lo, hi);

    ll idx = 0;
    for(ll i = lo; i <= hi; i++) {
        if(sq(p[i].x - midx) < d) {

            for(ll j = idx; j >= 1 && sq(p[i].y-strip[j].y) < d; j--)
                d = min(d, dist(p[i], strip[j]));

            strip[++idx] = p[i];
        }
    }

    return d;
}

int main()
{
    ll n; sl(n);

    for1(i, n) {
        sl(ara[i]);
        pre[i] = (pre[i-1] + ara[i]);

        p[i] = {i, pre[i]};
    }

    sort(p+1, p+n+1, cmpX);
    cout << closestPoint(1, n) << EL;

    return 0;
}
