#include <iostream>
#include <vector>
#include <map>

using namespace std;

// Brute Force
int FindOne(vector<int> v)
{
    int n = v.size();

    int count = 0;

    for (int i = 0; i < n; i++)
    {
        int curr = v[i];
        count = 0;
        for (int j = 0; j < n; j++)
        {
            if (v[j] == curr)
                count++;
            if (count > 1)
                break;
        }
        if (count == 1)
            return curr;
    }
    return -1;
}

// Better1--hashing--not good for the -ve numbers and extremly large numbers

int findOne_1(vector<int> v)
{
    int n = v.size();
    int max = *max_element(v.begin(), v.end());
    vector<int> hash(max + 1, 0);

    for (auto i : v)
    {
        hash[i]++;
    }

    for (int i = 0; i < hash.size(); i++)
    {
        if (hash[i] == 1)
            return i;
    }

    return -1;
}

// Better 2 using map
int findOne_2(vector<int> v)
{
    int n = v.size();
    map<long long, int> m;

    for (int i = 0; i < n; i++)
    {
        m[v[i]]++;
    }

    for (auto i : m)
        if (i.second == 1)
            return i.first;
    return -1;
}

// Optimal Solution xor
int findOne(vector<int> v)
{
    int n = v.size();
    int xorr = 0;

    for (auto i : v)
        xorr ^= i;

    return xorr;
}

int main()
{
    vector<int> v = {1, 1, 2, 2, 3, 4, 4};
    cout << FindOne(v) << endl;
    cout << findOne_1(v) << endl;
    cout << findOne_2(v) << endl;
    cout << findOne(v) << endl;
}