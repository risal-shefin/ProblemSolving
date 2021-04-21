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

string solve(string &a, string &b)
{
    string ret = "";
    ll o1 = 0, z1 = 0, o2 = 0, z2 = 0;

    for(char &ch : a) {
        if(ch == '0')
            z1++;
        else
            o1++;
    }

    for(char &ch : a) {
        if(ch == '0')
            z2++;
        else
            o2++;
    }

    if( (z1 > o1 && o2 > z2) || (z1<o1 && o2<z2)) {
        ll len = a.length() + b.length();
        for0(i, len) ret.pb('0');
        return ret;
    }

    char x, y;
    if(z1 > o1) x = '0', y = '1';
    else x = '1', y = '0';

    ll ptr1 = 0, ptr2 = 0;
    while(1) {

        if(ptr1 >= a.size()) {
            while(ptr2 < b.size()) {
                ret.pb(b[ptr2]);
                ptr2++;
            }
            break;
        }
        if(ptr2 >= b.size()) {
            while(ptr1 < a.size()) {
                ret.pb(a[ptr1]);
                ptr1++;
            }
            break;
        }

        ll c1 = 0, c2 = 0;
        while(ptr1 < a.length() && a[ptr1] != x) {
            ptr1++;
            c1++;
        }
        while(ptr2 < b.length() && b[ptr2] != x) {
            ptr2++;
            c2++;
        }

        ll mx = max(c1, c2);

        for1(i, mx) ret.pb(y);

        if(ptr1 < a.size() || ptr2 < b.size())
            ret.pb(x);

        ptr1++, ptr2++;
    }

    return ret;
}

int main()
{
    fastio;
    ll t; cin >> t;

    while(t--) {
        ll n; cin >> n;
        string a, b, c;
        cin >> a >> b >> c;

        string s1 = solve(a, b), s2 = solve(a, c), s3 = solve(b, c);

        ll mn = min({s1.size(), s2.size(), s3.size()});
        if(s1.size() == mn)
            cout << s1 << EL;
        else if(s2.size() == mn)
            cout << s2 << EL;
        else
            cout << s3 << EL;
    }

    return 0;
}

