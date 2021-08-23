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

const ll sz = 2e5 + 10;
map <int, int> cnt;
map <int, vector <int> > lst;
map <int, ll> sum;
ll ase[sz], cst[sz];

struct cmp
{
    const bool operator ()(const int &a, const int &b) {
        return cst[a] < cst[b];
    }
};

priority_queue <int, vector<int>, cmp> pq;

int main()
{
    ll n;
    sl(n);

    for1(i, n) {
        ll x; sl(x);
        ++cnt[x];
        lst[x].pb(i);

        ase[i] = x;
    }

    for1(i, n) {
        sl(cst[i]);
        sum[ ase[i] ] += cst[i];
    }

    ll ans = 0, tot = 0;

    for(auto it = cnt.begin(); it != cnt.end(); ++it) {
        if(it->second == 1) {
            tot = 0;
            while(!pq.empty()) pq.pop();
            continue;
        }

        ll val = it->first, exist = it->second;
        cnt[val+1] += exist-1;

        for(int &x : lst[val])
            pq.push(x);

        if(sum.find(it->first) != sum.end())
            tot += sum[it->first];

        ll mxc = pq.top();
        pq.pop();
        tot -= cst[mxc];

        ans += tot;
    }

    cout << ans << EL;

    return 0;
}
