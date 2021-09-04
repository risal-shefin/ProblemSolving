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

const ll MAX_N = 5005;
char s[MAX_N];
int dp[MAX_N];

int solve(int len)
{
    if(len <= 0)
        return 0;

    int &ret = dp[len];
    if(ret != -1)
        return ret;

    ret = 0;
    set <int> lst;

    for1(i, len)
        lst.insert(solve(i-2) ^ solve(len-i-1));

    int mex = 0;
    while(!lst.empty() && mex == *lst.begin()) {
        mex++;
        lst.erase(lst.begin());
    }

    return ret = mex;
}

int main()
{
    scanf("%s", s+1);
    ll slen = strlen(s+1);

    ms(dp, -1);
    ll got = 0;

    for(int i = 2; i < slen; i++) {\
        if(s[i-1] != s[i+1])
            continue;

        ll stop = i;

        for(int j = i+1; j < slen; j++) {
            if(s[j-1] != s[j+1])
                break;

            stop = j;
        }

        got ^= solve(stop-i+1);
        i = stop;
    }

    if(!got) {
        cout << "Second\n";
        return 0;
    }

    cout << "First\n";

    for(int i = 2; i < slen; i++) {\
        if(s[i-1] != s[i+1])
            continue;

        ll stop = i;

        for(int j = i+1; j < slen; j++) {
            if(s[j-1] != s[j+1])
                break;

            stop = j;
        }

        ll len = stop-i+1, cur = solve(len);
        ll gameNow = got^cur;

        for1(j, len) {
            ll sub = solve(j-2) ^ solve(len-j-1);

            if((gameNow ^ sub) == 0) {
                cout << i+j-1 << EL;
                return 0;
            }
        }

        i = stop;
    }

    return 0;
}

