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

const ll sz = 3e5 + 10;
ll ara[sz], BIT[sz][2];

void upd(ll idx, bool f, ll v)
{
    while(idx < sz) {
        BIT[idx][f] += v;
        idx += idx&(-idx);
    }
}

inline ll getSum(ll idx, bool f)
{
    ll ret = 0;
    while(idx > 0) {
        ret += BIT[idx][f];
        idx -= idx&(-idx);
    }
    return ret;
}

inline ll qry(ll l, ll r) {
    return getSum(r, 1) - getSum(l-1, 1);
}

int main()
{
    ll n; sl(n);
    for1(i, n) sl(ara[i]);

    ll pre = 0, sum1 = 0, sum2 = 0;

    for1(k, n) {
        ll s1 = sum1 + (k-1)*ara[k] + getSum(ara[k], 0);  // s1 = sum(ai mod aj), i > j
        ll s2 = sum2 + pre;

        for(ll d = 1; d*ara[k] < sz; d++) {
            ll l = d*ara[k], r = min(sz-1, (d+1)*ara[k] - 1);
            s2 += ara[k] * d*qry(l, r);
        }
        // s2 = sum(ai mod aj), i < j

        pf("%lld ", s1+s2);

        sum1 = s1, sum2 = s2, pre += ara[k];

        for(ll d = 1; d*ara[k] < sz; d++) {
            ll l = d*ara[k], r = min(sz-1, (d+1)*ara[k] - 1);

            upd(l, 0, -ara[k]*d);
            upd(r+1, 0, ara[k]*d);
        }

        upd(ara[k], 1, -1);
    }
    pn;

    return 0;
}

