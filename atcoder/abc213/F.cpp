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

#define MAX_N 1000020
int n, t;
char s[MAX_N];
int SA[MAX_N], LCP[MAX_N];
int RA[MAX_N], tempRA[MAX_N];
int tempSA[MAX_N];
int c[MAX_N];
int Phi[MAX_N], PLCP[MAX_N];
// second approach: O(n log n)
// rank array and temporary rank array
// suffix array and temporary suffix array
// for counting/radix sort
void countingSort(int k)   // O(n)
{
    int i, sum, maxi = max(300, n);
// up to 255 ASCII chars or length of n
    memset(c, 0, sizeof c);
// clear frequency table
    for (i = 0; i < n; i++)
// count the frequency of each integer rank
        c[i + k < n ? RA[i + k] : 0]++;
    for (i = sum = 0; i < maxi; i++)
    {
        int t = c[i];
        c[i] = sum;
        sum += t;
    }
    for (i = 0; i < n; i++)
// shuffle the suffix array if necessary
        tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
    for (i = 0; i < n; i++)
// update the suffix array SA
        SA[i] = tempSA[i];
}
void buildSA()
{
    int i, k, r;
    for (i = 0; i < n; i++)
        RA[i] = s[i];
// initial rankings
    for (i = 0; i < n; i++)
        SA[i] = i;
// initial SA: {0, 1, 2, ..., n-1}
    for (k = 1; k < n; k <<= 1)
    {
// repeat sorting process log n times
        countingSort(k); // actually radix sort: sort based on the second item
        countingSort(0);
// then (stable) sort based on the first item
        tempRA[SA[0]] = r = 0;
// re-ranking; start from rank r = 0
        for (i = 1; i < n; i++)
// compare adjacent suffixes
            tempRA[SA[i]] = // if same pair => same rank r; otherwise, increase r
                (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
        for (i = 0; i < n; i++)
// update the rank array RA
            RA[i] = tempRA[i];
        if (RA[SA[n - 1]] == n - 1)
            break;
// nice optimization trick
    }
}
void buildLCP()
{
    int i, L;
    Phi[SA[0]] = -1;
// default value
    for (i = 1; i < n; i++)
// compute Phi in O(n)
        Phi[SA[i]] = SA[i - 1];
// remember which suffix is behind this suffix
    for (i = L = 0; i < n; i++)
    {
// compute Permuted LCP in O(n)
        if (Phi[i] == -1)
        {
            PLCP[i] = 0;
            continue;
        }
// special case
        while (s[i + L] == s[Phi[i] + L])
            L++;
// L increased max n times
        PLCP[i] = L;
        L = max(L - 1, 0);
// L decreased max n times
    }
    for (i = 0; i < n; i++)
// compute LCP in O(n)
        LCP[i] = PLCP[SA[i]];
// put the permuted LCP to the correct position
}
// n = string length + 1
// s = the string
// memset(LCP, 0, sizeof(LCP)); setting all index of LCP to zero
// buildSA(); for building suffix array
// buildLCP(); for building LCP array
// LCP is the longest common prefix with the previous suffix here
// SA[0] holds the empty suffix "\0".

int tr[4*MAX_N], lz[4*MAX_N];
ll tr2[4*MAX_N], ans[MAX_N];

void prop(int node)
{
    int lft=node<<1, rgt=lft|1;
    lz[lft] = lz[rgt] = tr[lft] = tr[rgt] = 0;
    tr2[lft] = tr2[rgt] = 0;
    lz[node] = -1;
}

void upd(int lo, int hi, int l, int r, int node)
{
    if(lo > r || hi < l)
        return;
    if(lo >= l && hi <= r) {
        tr[node] = tr2[node] = lz[node] = 0;
        return;
    }
    if(lz[node] != -1) prop(node);

    int mid = lo+hi>>1, lft=node<<1, rgt=lft|1;

    upd(lo, mid, l, r, lft);
    upd(mid+1, hi, l, r, rgt);

    tr[node] = tr[lft] + tr[rgt];
    tr2[node] = tr2[lft] + tr2[rgt];
}

void upd2(int lo, int hi, int idx, int v, int node)
{
    if(lo > idx || hi < idx)
        return;
    if(lo == hi) {
        tr[node] += v;
        tr2[node] += (ll)lo*v;
        return;
    }
    if(lz[node] != -1) prop(node);

    int mid = lo+hi>>1, lft=node<<1, rgt=lft|1;

    upd2(lo, mid, idx, v, lft);
    upd2(mid+1, hi, idx, v, rgt);

    tr[node] = tr[lft] + tr[rgt];
    tr2[node] = tr2[lft] + tr2[rgt];
}

int qry(int lo, int hi, int l, int r, int node)
{
    if(lo > r || hi < l)
        return 0;
    if(lo >= l && hi <= r)
        return tr[node];

    if(lz[node] != -1) prop(node);

    int mid = lo+hi>>1, lft=node<<1, rgt=lft|1;

    return qry(lo, mid, l, r, lft)
        +  qry(mid+1, hi, l, r, rgt);
}

int main()
{
    ll len;
    cin >> len;
    scanf("%s", s);
    n = len+1;

    buildSA();
    buildLCP();

    ms(lz, -1); ms(tr, 0); ms(tr2, 0);

    for1(i, len) {

        ll got = qry(0, len, LCP[i]+1, len, 1);

        upd(0, len, LCP[i]+1, len, 1);
        upd2(0, len, LCP[i], got+1, 1);

        ans[ SA[i] ] += tr2[1];
    }

    ms(lz, -1), ms(tr, 0), ms(tr2, 0);

    rep1(i, len) {
        ans[ SA[i] ] += tr2[1];

        ll got = qry(0, len, LCP[i]+1, len, 1);

        upd(0, len, LCP[i]+1, len, 1);
        upd2(0, len, LCP[i], got+1, 1);
    }

    for1(i, len) ans[ SA[i] ] += (len-SA[i]);

    for0(i, len) pf("%lld\n", ans[i]);

    return 0;
}

