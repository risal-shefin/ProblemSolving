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

const ll sz = 105;
bool got[26], vis[sz];
ll need[2*sz];

int main()
{
    fastio;

    ll b, d;
    cin >> b >> d;

    string a, c;
    cin >> a >> c;

    for(char &ch : a) got[ch-'a'] = 1;

    for(char &ch : c) {
        if(!got[ch-'a']) {
            cout << 0 << EL;
            return 0;
        }
    }

    ll cnt1 = 0, cnt2 = 0, ptr1 = 0, ptr2 = 0;

    while(1) {
        while(a[ptr1] != c[ptr2]) {
            ptr1++;
            if(ptr1 == a.size())
                ptr1 = 0, cnt1++;
        }

        if(ptr2 == c.size()-1) {
            need[cnt2] = cnt1+1;

            if(vis[ptr1])
                break;
            vis[ptr1] = 1;
        }

        ptr1++, ptr2++;
        if(ptr1 == a.size()) ptr1 = 0, cnt1++;
        if(ptr2 == c.size()) ptr2 = 0, cnt2++;
    }

    ll last = need[cnt2] - need[cnt2-1], diff = need[0]-last;

    ll lo = 1, hi = 1e9, ret = 0;
    while(lo <= hi) {
        ll mid = lo+hi>>1;

        ll occ = d*mid - 1, cnt = occ/cnt2, rem = occ%cnt2;
        ll take = cnt*need[cnt2-1] + need[rem] - cnt*diff;

        if(take > b)
            hi = mid-1;
        else {
            ret = mid;
            lo = mid+1;
        }
    }
    cout << ret << EL;

    return 0;
}
