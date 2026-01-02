#include <iostream>
#include <vector>
using namespace std;

// Brute Force
int findMissing(vector<int> v)
{
    int n = v.size();

    for (int i = 1; i <= n; i++)
    {
        int flag = 0;

        for (int j = 0; j <= n; j++)
        {
            if (i == v[j])
            {
                flag = 1;
                break;
            }
        }
        if (!flag)
            return i;
    }

    return -1;
}

// Optimal Solution 1
int FindMissing(vector<int> v)
{
    int n = v.size() + 1;
    int sum = n * (n + 1) / 2;
    int sum2 = 0;
    for (auto i : v)
        sum2 = sum2 + i;
    return sum - sum2;
}

// optimal solution 2
int findMissing2(vector<int> v)
{
    int n = v.size();
    int xor1 = 0, xor2 = 0;

    for (int i = 0; i < n; i++)
    {
        xor1 = xor1 ^ v[i];
        xor2 = xor2 ^ (i + 1);
    }
    xor2 = xor2 ^ (n + 1);
    return xor1 ^ xor2;
}

int main()
{

    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 10};
    // int missing = findMissing(v);
    // int missing = FindMissing(v);
    int missing = findMissing2(v);
    if (!missing)
        cout << "Nothing is missing!!!";
    else
        cout << missing;
}