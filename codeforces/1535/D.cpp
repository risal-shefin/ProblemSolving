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
char s[sz];
ll tr[sz];
pii rng[sz];

void mrg(ll lo, ll hi, ll node)
{
    ll mid = lo+hi>>1, lft = node<<1, rgt = lft|1;

    if(s[node] == '?')
        tr[node] = tr[lft] + tr[rgt];
    else if(s[node] == '0')
        tr[node] = tr[rgt];
    else
        tr[node] = tr[lft];
}

void init(ll lo, ll hi, ll node)
{
    rng[node] = mp(lo, hi);

    if(lo == hi) {
        if(s[node] == '?')
            tr[node] = 2;
        else
            tr[node] = 1;

        return;
    }

    ll mid = lo+hi>>1, lft = node<<1, rgt = lft|1;

    init(lo, mid, lft);
    init(mid+1, hi, rgt);

    mrg(lo, hi, node);
}

void upd(ll lo, ll hi, ll l, ll r, ll node)
{
    if(lo > l || hi < l)
        return;

    if(lo >= l && hi <= r) {

        if(lo == hi) {
            if(s[node] == '?')
                tr[node] = 2;
            else
                tr[node] = 1;

            return;
        }

        mrg(lo, hi, node);
        return;
    }

    ll mid = lo+hi>>1, lft = node<<1, rgt = lft|1;

    upd(lo, mid, l, r, lft);
    upd(mid+1, hi, l, r, rgt);

    mrg(lo, hi, node);
}

int main()
{
    ll k; sl(k);
    ll len = (1LL<<k) - 1, n = (1LL << k)/2;
    scanf("%s", s+1);

    reverse(s+1, s+len+1);

    init(1, n, 1);
    ll ans = tr[1];

    ll q; sl(q);

    while(q--) {
        ll p; char ch;
        scanf("%lld %c", &p, &ch);
        p = len-p+1;

        if(s[p] == ch)
            pf("%lld\n", ans);
        else {
            s[p] = ch;
            upd(1, n, rng[p].ff, rng[p].ss, 1);
            ans = tr[1];

            pf("%lld\n", ans);
        }
    }

    return 0;
}
