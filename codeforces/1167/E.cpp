#include <bits/stdc++.h>
using namespace std;

#define ll int
#define inf 1000000000
ll mngreat[4000009], mxgreat[4000009];
bool state[1000009], tree[4000009];
long long ans = 0;

set <ll> lst;
set <ll> ::iterator it;
ll ara[1000009];

void update(ll lo, ll hi, ll &idx, ll node)

{
    if(lo > idx || hi < idx)
        return;
    if(lo == hi) {
        tree[node] = 1;
        return;
    }

    ll mid = (lo + hi) / 2;
    update(lo, mid, idx, node << 1);
    update(mid + 1, hi, idx, (node << 1) | 1);

    tree[node] = max(tree[node << 1], tree[(node<<1) | 1]);
}

bool query(ll lo, ll hi, ll &left, ll &right, ll node)

{
    if(lo > right || hi < left)
        return 0;
    if(lo >= left && hi <= right)
        return tree[node];

    ll mid = (lo + hi) / 2;
    bool p1 = query(lo, mid, left, right, (node << 1));
    bool p2 = query(mid + 1, hi, left, right, (node << 1) | 1);

    return max(p1, p2);
}

ll mxBIT[1000009], mnBIT[1000009];

ll getMax(ll index)
{
    ll mx = -inf; // Iniialize result

    // Traverse ancestors of BITree[index]
    while (index>0)
    {
        mx = max(mx, mxBIT[index]);

        // Move index to parent node in getSum View
        index -= index & (-index);
    }
    return mx;
}

void updatemxBIT(ll index, ll &val)

{
    // Traverse all ancestors
    while (index <= 1000000)
    {
        mxBIT[index] = max(mxBIT[index], val);

       // Update index to that of parent in update View
       index += index & (-index);
    }
}

ll getMin(ll index)
{
    ll mn = inf; // Iniialize result

    // Traverse ancestors of BITree[index]
    while (index>0)
    {
        mn = min(mn, mnBIT[index]);

        // Move index to parent node in getSum View
        index -= index & (-index);
    }
    return mn;
}

void updatemnBIT(ll index, ll &val)

{
    // Traverse all ancestors
    while (index <= 1000000)
    {
        mnBIT[index] = min(mnBIT[index], val);

       // Update index to that of parent in update View
       index += index & (-index);
    }
}

//#define gc getchar_unlocked
#define gc getchar   // for windows
inline void read_int(int &x)

{
    x=0;
    register char c=gc();
    for(;c<'0' || c>'9';c=gc());
    for(;c>='0' && c<='9';c=gc())
    x=(x<<3)+(x<<1)+(c-'0');
}

int main()

{
    //freopen("in.txt", "r", stdin);
    ll n, x;
    read_int(n), read_int(x);

    for(ll i = 0; i <= 1000000; i++) {
        mxBIT[i] = -inf;
        mnBIT[i] = inf;
    }


    ll v;
    bool t;
    for(ll i = 1; i <= n; i++) {
        scanf("%d", &ara[i]);
        lst.insert(ara[i]);

        it = lst.lower_bound(ara[i]);
        it++;
        if(it != lst.end()) {
            update(0, 1000000, ara[i], 1);

            v = *it, t = 0;
            updatemnBIT(ara[i], v);
            v = *(--lst.end()), t = 1;
            updatemxBIT(ara[i], v);
        }
    }

    ll minboro, maxboro, start, stop, lo, hi, mid, range;

    for(ll i = 1; i <= x; i++) {
        start = i, stop = x, t = 1;
        bool ret = query(0, 1000000, start, stop, 1);
        if(ret == 0) {
            for(ll j = i; j <= x; j++)
                state[j] = 1;

            break;
        }
    }

    for(ll i = 1; i <= x; i++) {
        minboro = getMin(i - 1);
        //cout << i << "  " << minboro << endl;
        if(minboro < i)
            break;

        maxboro = getMax(i - 1);

        lo = max(i, maxboro), hi = x, range = -1;
        while(lo <= hi) {
            mid = (lo + hi) / 2;

            if(mid == x) {
                range = mid;
                hi = mid - 1;
            }
            else {
                if(state[mid + 1] == 1) {
                    range = mid;
                    hi = mid - 1;
                }
                else
                    lo = mid + 1;
            }
        }

        //cout << i << " " << range << "  " << minboro << endl;
        if(range == -1)
            continue;

        ans += (long long)(x - range + 1);
    }

    printf("%lld\n", ans);

    return 0;
}
