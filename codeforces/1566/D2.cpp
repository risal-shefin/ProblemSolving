// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

template <typename T>  using orderedSet =
    tree<T, null_type, less<T>,   /// greater<T> for sorting decreasingly
    rb_tree_tag, tree_order_statistics_node_update>;

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

const ll sz = 300*300 + 10;

struct info {
    ll a, id;
    const bool operator <(const info &rhs) {
        if(a == rhs.a)
            return id < rhs.id;
        return a < rhs.a;
    }
} ara[sz];

orderedSet <int> lst[309];

int main()
{
    ll t;
    sl(t);

    while(t--) {
        ll n, m;
        sl(n), sl(m);

        ll idx = 0;

        for1(i, n) {
            for1(i, m) {
                idx++;
                sl(ara[idx].a), ara[idx].id = idx;
            }
        }
        sort(ara+1, ara+idx+1);

        for0(i, n) lst[i].clear();
        ll ans = 0;

        for1(i, idx) {
            ll cur = i-1;
            ll row = cur/m, stop = i;

            for(ll j = i; j <= idx; j++) {
                if(ara[j].a != ara[i].a || (j-1)/m != row)
                    break;

                stop = j;
                ans += lst[row].order_of_key(ara[j].id);
                //dbg(mp(ara[j].id, lst[row]));
            }

            for(ll j = i; j <= stop; j++) lst[row].insert(ara[j].id);

            i = stop;
        }

        pf("%lld\n", ans);
    }

    return 0;
}

