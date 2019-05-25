#include <bits/stdc++.h>
using namespace std;

#define ll int
#define inf 1000000000
ll mngreat[1000009], mxgreat[1000009];
bool state[1000009];
long long ans = 0;

set <ll> lst;
set <ll> ::iterator it;
ll ara[1000009];

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

void updatemxBIT(ll index, ll val)

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

void updatemnBIT(ll index, ll val)

{
    // Traverse all ancestors
    while (index <= 1000000)
    {
        mnBIT[index] = min(mnBIT[index], val);

       // Update index to that of parent in update View
       index += index & (-index);
    }
}

int main()

{
    ll n, x;
    scanf("%d %d", &n, &x);

    for(ll i = 0; i <= 1000000; i++) {
        mxBIT[i] = -inf;
        mnBIT[i] = inf;
    }


    ll last = 0;
    for(ll i = 1; i <= n; i++) {
        scanf("%d", &ara[i]);
        lst.insert(ara[i]);

        it = lst.upper_bound(ara[i]);
        if(it != lst.end()) {
            last = max(last, ara[i]);

            updatemnBIT(ara[i], *it);
            updatemxBIT(ara[i], *(--lst.end()));
        }
    }

    for(ll i = last + 1; i <= x; i++)
        state[i] = 1;

    ll minboro, maxboro, lo, hi, mid, range;
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
