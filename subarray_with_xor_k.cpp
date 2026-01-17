#include <iostream>
#include <vector>

using namespace std;

class solution
{
public:
    int subarrayWithXorK_brute(vector<int> v, int target)
    {
        int n = v.size();
        int xr = 0;
        int count = 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                xr = 0;
                for (int k = i; k <= j; k++)
                {
                    xr = xr ^ v[k];
                }
                if (xr == target)
                    count++;
            }
        }
        return count;
    }

    // better
    int subarrayWithXorK_better(vector<int> v, int target)
    {
        int n = v.size();
        int xr = 0;
        int count = 0;

        for (int i = 0; i < n; i++)
        {
            xr = 0;
            for (int j = i; j < n; j++)
            {
                xr = xr ^ v[j];
                if (xr == target)
                    count++;
            }
        }
        return count;
    }

    // optimal...using logic x = xr ^ k;

    int subarrayWithXorK_optimal(vector<int> v, int target)
    {
        int n = v.size();
        int xr = 0;
        int count = 0;
        unordered_map<int, int> hashMap;
        hashMap[0] = 1;

        for (int i = 0; i < n; i++)
        {
            xr = v[i] ^ xr;
            int x = xr ^ target;

            if (hashMap.find(x) != hashMap.end())
            {
                count += hashMap[x];
            }
            hashMap[x]++;
        }
        return count;
    }
};

int main()
{
    vector<int> v = {4, 2, 2, 6, 4};
    solution sol;
    cout << sol.subarrayWithXorK_brute(v, 6) << endl;
    cout << sol.subarrayWithXorK_better(v, 6) << endl;
    cout << sol.subarrayWithXorK_optimal(v, 6) << endl;
}