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

struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
// http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

unordered_map <int, vector <pii>, custom_hash> X, Y;
unordered_map <int, int, custom_hash> existX, existY;

ll find_en(vector <pii> &v, ll p)
{
    for(int i = 0; i < v.size(); i++) {
        if(v[i].ff >= p)
            break;

        ll stop = i, mxCover = v[i].ss;

        for(int j = i+1; j < v.size(); j++) {
            if(v[j].ff > mxCover)
                break;

            stop = j, mxCover = max(mxCover, (ll)v[j].ss);
        }

        ll bad = p-v[i].ff;
        p = mxCover + bad, i = stop;
    }

    return p;
}

int main()
{
    ll n, m, k;
    cin >> n >> m >> k;

    for1(i, k) {
        ll x1, y1, x2, y2;
        sl(x1), sl(y1), sl(x2), sl(y2);

        if(y1 == y2) {
            if(x1 > x2) swap(x1, x2);
            Y[y1].pb(mp(x1, x2));
        }
        else {
            if(y1 > y2) swap(y1, y2);
            X[x1].pb(mp(y1, y2));
        }
    }

    if(n == 1 && m == 1) {
        cout << "SECOND\n";
        return 0;
    }

    ll linex = n-1, liney = m-1, xr = 0;

    for(auto it = X.begin(); it != X.end(); ++it) {
        vector <pii> &v = it->second;
        sort(all(v));

        linex--;

        ll tot = m, y = v[0].ff;

        for(pii &p : v) {
            if(p.ff <= y)
                tot -= max(0LL, p.ss-y);
            else
                tot -= (p.ss-p.ff);

            y = max(y, (ll)p.ss);
        }

        xr ^= tot;
        existX[it->first] = tot;
    }
    if(linex & 1) xr ^= m;

    for(auto it = Y.begin(); it != Y.end(); ++it) {
        vector <pii> &v = it->second;
        sort(all(v));

        liney--;

        ll tot = n, x = v[0].ff;

        for(pii &p : v) {
            if(p.ff <= x)
                tot -= max(0LL, p.ss-x);
            else
                tot -= (p.ss-p.ff);

            x = max(x, (ll)p.ss);
        }

        xr ^= tot;
        existY[it->first] = tot;
    }
    if(liney & 1) xr ^= n;

    if(!xr) pf("SECOND\n");
    else {
        pf("FIRST\n");

        for(auto it = existX.begin(); it != existX.end(); ++it) {
            ll need = xr ^ (it->second);
            need = (it->second) - need;
            if(need <= 0)
                continue;

            int fy = 0, sy = find_en(X[it->first], need);

            pf("%d %d %d %d\n", it->first, fy, it->first, sy);
            return 0;
        }

        for(auto it = existY.begin(); it != existY.end(); ++it) {
            ll need = xr ^ (it->second);
            need = (it->second) - need;
            if(need <= 0)
                continue;

            int fx = 0, sx = find_en(Y[it->first], need);

            pf("%d %d %d %d\n", fx, it->first, sx, it->first);
            return 0;
        }

        for1(i, n-1) {
            if(X.find(i) != X.end())
                continue;

            ll need = m - (xr ^ m);
            if(need <= 0) break;
            pf("%lld 0 %lld %lld\n", i, i, need);
            return 0;
        }

        for1(i, m-1) {
            if(Y.find(i) != Y.end())
                continue;

            ll need = n - (xr ^ n);
            pf("0 %lld %lld %lld\n", i, need, i);
            return 0;
        }
    }

    return 0;
}
