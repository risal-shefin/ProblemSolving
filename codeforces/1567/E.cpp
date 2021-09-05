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

struct info {
    ll sum, p, plen, s, slen;
} tr[4*sz];

ll ara[sz];

void build(ll lo, ll hi, ll node)
{
    if(lo == hi) {
        tr[node].p = tr[node].s = ara[lo];
        tr[node].sum = tr[node].plen = tr[node].slen = 1;
        return;
    }

    ll mid = lo+hi>>1, lft=node<<1, rgt=lft|1;

    build(lo, mid, lft);
    build(mid+1, hi, rgt);

    tr[node].p = tr[lft].p, tr[node].s = tr[rgt].s;

    if(tr[lft].s <= tr[rgt].p) {
        tr[node].sum = tr[lft].sum + tr[rgt].sum + tr[lft].slen*tr[rgt].plen;

        if(tr[lft].slen == (mid-lo+1)) {
            if(tr[rgt].plen == hi-mid)
                tr[node].plen = tr[node].slen = hi-lo+1;
            else
                tr[node].plen = tr[lft].slen + tr[rgt].plen, tr[node].slen = tr[rgt].slen;
        }
        else {
            if(tr[rgt].plen == hi-mid)
                tr[node].plen =  tr[lft].plen, tr[node].slen = tr[lft].slen + tr[rgt].plen;
            else
                tr[node].plen = tr[lft].plen, tr[node].slen = tr[rgt].slen;
        }
    }
    else {
        tr[node].sum = tr[lft].sum + tr[rgt].sum;
        tr[node].plen = tr[lft].plen, tr[node].slen = tr[rgt].slen;
    }
}

void upd(ll lo, ll hi, ll idx, ll x, ll node)
{
    if(lo > idx || hi < idx)
        return;
    if(lo == hi) {
        tr[node].p = tr[node].s = x;
        return;
    }

    ll mid = lo+hi>>1, lft=node<<1, rgt=lft|1;

    upd(lo, mid, idx, x, lft);
    upd(mid+1, hi, idx, x, rgt);

    tr[node].p = tr[lft].p, tr[node].s = tr[rgt].s;

    if(tr[lft].s <= tr[rgt].p) {
        tr[node].sum = tr[lft].sum + tr[rgt].sum + tr[lft].slen*tr[rgt].plen;

        if(tr[lft].slen == (mid-lo+1)) {
            if(tr[rgt].plen == hi-mid)
                tr[node].plen = tr[node].slen = hi-lo+1;
            else
                tr[node].plen = tr[lft].slen + tr[rgt].plen, tr[node].slen = tr[rgt].slen;
        }
        else {
            if(tr[rgt].plen == hi-mid)
                tr[node].plen =  tr[lft].plen, tr[node].slen = tr[lft].slen + tr[rgt].plen;
            else
                tr[node].plen = tr[lft].plen, tr[node].slen = tr[rgt].slen;
        }
    }
    else {
        tr[node].sum = tr[lft].sum + tr[rgt].sum;
        tr[node].plen = tr[lft].plen, tr[node].slen = tr[rgt].slen;
    }
}

info qry(ll lo, ll hi, ll l, ll r, ll node)
{
    if(lo > r || hi < l)
        return {inf, inf, inf, inf, inf};
    if(lo >= l && hi <= r)
        return tr[node];

    ll mid = lo+hi>>1, lft=node<<1, rgt=lft|1;

    info p1 = qry(lo, mid, l, r, lft);
    info p2 = qry(mid+1, hi, l, r, rgt);

    if(p1.p == inf)
        return p2;
    if(p2.p == inf)
        return p1;

    info ret;
    ret.p = p1.p, ret.s = p2.s;

    if(p1.s <= p2.p) {
        ret.sum = p1.sum + p2.sum + p1.slen*p2.plen;

        if(p1.slen == (mid-lo+1)) {
            if(p2.plen == hi-mid)
                ret.plen = ret.slen = hi-lo+1;
            else
                ret.plen = p1.slen + p2.plen, ret.slen = p2.slen;
        }
        else {
            if(p2.plen == hi-mid)
                ret.plen =  p1.plen, ret.slen = p1.slen + p2.plen;
            else
                ret.plen = p1.plen, ret.slen = p2.slen;
        }
    }
    else {
        ret.sum = p1.sum + p2.sum;
        ret.plen = p1.plen, ret.slen = p2.slen;
    }

    return ret;
}

int main()
{
    ll n, q;
    cin >> n >> q;

    for1(i, n) sl(ara[i]);

    build(1, n, 1);

    while(q--) {
        ll op, x, y;
        sl(op), sl(x), sl(y);

        if(op == 1) {
            upd(1, n, x, y, 1);
        }
        else {
            info got = qry(1, n, x, y, 1);
            pf("%lld\n", got.sum);
        }
    }

    return 0;
}
