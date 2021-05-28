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

const ll sz = 1e5 + 10;
ll BIT[sz];

void upd(ll idx, ll v, ll n)
{
    while(idx <= n) {
        BIT[idx] += v;
        idx += idx&(-idx);
    }
}

ll getSum(ll idx)
{
    ll ret = 0;
    while(idx > 0) {
        ret += BIT[idx];
        idx -= idx&(-idx);
    }
    return ret;
}

inline ll qry(ll l, ll r)
{
    return getSum(r) - getSum(l-1);
}

int main()
{
    ll n, q;
    cin >> n >> q;

    for1(i, n) upd(i, 1, n);
    ll start = 0, stop = n, rev = 0;

    while(q--) {
        ll op; sl(op);

        if(op == 1) {
            ll p; sl(p);

            ll len = stop-start;

            if(p > len-p) {
                p = len-p;
                rev ^= 1;
            }

            if(!rev) {

                for(ll i = start+1, j = start+p+p; i <= start+p; i++, j--) {
                    ll got = qry(i, i);
                    upd(j, got, n);
                }
                start += p;
            }
            else {

                for(ll i = stop, j = stop-p-p+1; i > stop-p; i--, j++) {
                    ll got = qry(i, i);
                    upd(j, got, n);
                }
                stop -= p;
            }
        }
        else {
            ll l, r;
            sl(l), sl(r);
            l += start, r += start;

            if(!rev)
                pf("%lld\n", qry(l+1, r));
            else {
                l = stop-l +start, r = stop-r +start;
                swap(l, r);
                //dbg(qry(9,9));
                pf("%lld\n", qry(l+1, r));
            }
        }
        //dbg(stop-(1+fwd));
    }

    return 0;
}
