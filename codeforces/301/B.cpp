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

const ll sz = 109;
ll a[sz], x[sz], y[sz], n, d, dist[sz];

struct info {
    ll v, w;
};
const bool operator <(const info &a, const info &b)
{
    return a.w > b.w;
}

inline ll get_d(ll i, ll j)
{
    return d*(abs(x[i]-x[j]) + abs(y[i]- y[j]));
}

bool dijkstra(ll x)
{
    for1(i, n) dist[i] = inf;

    priority_queue <info> pq;
    pq.push({1, 0});
    dist[1] = 0;

    while(!pq.empty()) {
        info u = pq.top();
        pq.pop();

        if(dist[u.v] != u.w)
            continue;

        for1(i, n) {
            if(u.v == i) continue;

            if(u.w + get_d(u.v, i)-a[i] < dist[i] && u.w+get_d(u.v, i) <= x) {
                dist[i] = u.w + get_d(u.v, i) - a[i];
                pq.push({i, dist[i]});
            }
        }
    }

    return dist[n] != inf;
}

int main()
{
    cin >> n >> d;
    for(ll i = 2; i < n; i++) sl(a[i]);

    for1(i, n) sl(x[i]), sl(y[i]);

    ll lo = 0, hi = 1e9, ret;
    while(lo <= hi) {
        ll mid = lo+hi>>1;

        if(dijkstra(mid)) {
            ret = mid;
            hi = mid-1;
        }
        else
            lo = mid+1;
    }

    cout << ret << EL;

    return 0;
}
