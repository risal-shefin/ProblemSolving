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

const ll sz = 1e5 + 10;
ll par[sz][2];

ll findp(ll u ,ll f)
{
    if(par[u][f] == u)
        return u;

    return par[u][f] = findp(par[u][f], f);
}

bool Union(ll u, ll v, ll f)
{
    ll pu = findp(u, f), pv = findp(v, f);
    if(pu == pv)
        return false;

    if(pu > pv) swap(pu, pv);
    par[pv][f] = pu;

    return true;
}

int main()
{
    ll n, m1, m2;
    cin >> n >> m1 >> m2;

    for1(i, n) par[i][0] = par[i][1] = i;

    for1(i, m1) {
        ll u, v;
        sl(u), sl(v);

        Union(u, v, 0);
    }

    for1(i, m2) {
        ll u, v;
        sl(u), sl(v);

        Union(u, v, 1);
    }

    vector <pii> v;
    stack <int> other1, other2;

    ll r1 = findp(1, 0), r2 = findp(1, 1);

    for(ll i = 2; i <= n; i++) {
        ll p1 = findp(i, 0), p2 = findp(i, 1);

        if(p1 != r1 && p2 != r2) {
            Union(1, i, 0), Union(1, i, 1);
            v.pb(mp(1, i));
        }

        if(findp(i, 0) != r1) other1.push(i);
        if(findp(i, 1) != r2) other2.push(i);
    }
    //dbg(v);

    while(!other1.empty() && !other2.empty()) {

        ll a = other1.top();

        if(findp(a, 0) == r1 && findp(a, 1) == r2) {
            other1.pop();
            continue;
        }

        ll b = other2.top();

        if(findp(b, 0) == r1 && findp(b, 1) == r2) {
            other2.pop();
            continue;
        }

        Union(a, b, 0), Union(a, b, 1);
        v.pb(mp(a, b));
    }

    cout << v.size() << EL;
    for(pii &p : v)
        pf("%d %d\n", p.ff, p.ss);

    return 0;
}
