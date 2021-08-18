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

const ll sz = 11;
double eps = 1e-9;

struct info {
    double x, v;
    ll m, id;
    const bool operator <(const info &rhs) {
        return x < rhs.x;
    }
} ara[sz];

bool done[sz];
double ans[sz];

inline double calc(ll i, ll j)
{
    if(ara[i].v > 0 && ara[j].v >= ara[i].v)
        return inf;
    if(ara[j].v < 0 && ara[i].v <= ara[j].v)
        return inf;
    if(ara[i].v < 0 && ara[j].v > 0)
        return inf;

    double d = ara[j].x - ara[i].x;

    if(ara[i].v > 0 && ara[j].v < 0)
        return (double)d / (ara[i].v + abs(ara[j].v));

    return (double)d / abs(ara[i].v - ara[j].v);
}

int main()
{
    ll n, t;
    cin >> n >> t;

    for1(i, n) sd(ara[i].x), sd(ara[i].v), sl(ara[i].m), ara[i].id = i;

    double tim = 0;

    while(tim < t) {
        ms(done, 0);
        sort(ara+1, ara+n+1);

        double dif = inf;

        for1(i, n-1)
            dif = min(dif, calc(i, i+1));

        if(tim+dif > t) {
            dif = t-tim;
            for1(i, n) ara[i].x = ara[i].x + ara[i].v*dif;
            break;
        }

        for1(i, n-1) {
            double got = calc(i, i+1);

            if(abs(dif-got) > eps)
                continue;

            done[i] = done[i+1] = 1;

            auto [x1, v1, m1, id1] = ara[i]; auto [x2, v2, m2, id2] = ara[i+1];

            x1 = x1 + v1*dif, x2 = x2 + v2*dif;

            double _v1 = ((m1-m2)*v1 + 2*m2*v2)/(m1+m2);
            double _v2 = ((m2-m1)*v2 + 2*m1*v1)/(m1+m2);

            v1 = _v1, v2 = _v2;
            ara[i] = {x1, v1, m1, id1}, ara[i+1] = {x2, v2, m2, id2};
            i++;
        }

        for1(i, n) {
            if(done[i]) continue;

            ara[i].x = ara[i].x + ara[i].v*dif;
        }
        tim += dif;

        if(tim+eps > t) eps = t-tim;

        for1(i, n) ara[i].x = ara[i].x + ara[i].v*eps;
        tim += eps;
    }

    for1(i, n) ans[ara[i].id] = ara[i].x;

    for1(i, n)
        pf("%0.9f\n", ans[i]);

    return 0;
}
