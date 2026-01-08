#include <iostream>
#include <vector>
#include <map>

using namespace std;

// Brute force
int longestSubarray(vector<int> v, int k)
{
    int maxLen = 0;
    long long sum = 0;
    long long rem = 0;
    unordered_map<long long, int> prefixSum;

    for (int i = 0; i < v.size(); i++)
    {
        sum += v[i];

        rem = sum - k;

        if (sum == k)
            maxLen = max(maxLen, i + 1);

        if (prefixSum.find(rem) != prefixSum.end())
        {
            int len = i - prefixSum[rem];
            maxLen = max(maxLen, len);
        }

        if (prefixSum.find(sum) == prefixSum.end())
            prefixSum[sum] = i;
    }
    return maxLen;
}

// Optimal works only for the non -ves otherwise have to use the brute one
int longestSubarray_optimal(vector<int> v, int k)
{
    int i = 0, j = 0;
    long long sum = 0;
    int maxLen = 0;
    int n = v.size();

    while (j < n)
    {
        sum += v[j];

        while (i <= j and sum > k)
        {
            sum -= v[i];
            i++;
        }

        if (sum == k)
            maxLen = max(maxLen, j - i + 1);

        j++;
    }
    return maxLen;
}

int main()
{
    // vector<int> v = {1, 0, -1, 2, -2, 3};
    vector<int> v = {1, 2, 3, 1, 1, 1, 1};
    cout << longestSubarray(v, 3) << endl;
    cout << longestSubarray_optimal(v, 3) << endl;
}