#include <iostream>
#include <vector>
#include <map>

using namespace std;

void two_sum(vector<int> v, int k)
{
    int n = v.size();
    vector<pair<int, int>> ans;

    for (int i = 0; i < n; i++)
    {
        int rem = k - v[i];

        for (int j = i + 1; j < n; j++)
        {
            if (j == i)
                continue;

            if (rem == v[j])
            {
                ans.emplace_back(i, j);
            }
        }
    }

    for (auto i : ans)
    {
        printf("(%d,%d)\n", i.first, i.second);
    }
}

void two_sum_better(vector<int> v, int k)
{
    unordered_map<int, int> m;

    for (int i = 0; i < v.size(); i++)
    {
        int rem = k - v[i];

        if (m.find(rem) != m.end())
            printf("(%d,%d)\n", m[rem], i);
        m[v[i]] = i;
    }
}

// use only if you want to find if the sum exists in the sorted array or not
void two_sum_optimised(vector<int> v, int k)
{
    int n = v.size();
    int i = 0, j = n - 1;

    // sorting
    sort(v.begin(), v.end());

    while (j >= 0 and i < n and i <= j)
    {
        int sum = v[i] + v[j];
        if (sum == k)
        {
            printf("(%d,%d)\n", i, j);
            i++, j--;
        }

        else if (sum < k and i <= j)
            i++;
        else
            j--;
        // while (sum < k and i <= j)
        //     i++;
        // while (sum > k and j >= i)
        //     j--;
    }
}
int main()
{
    vector<int> v = {1, 2, 3, 4, 5, 2, 1, 3};
    two_sum(v, 3);
    cout << endl;
    two_sum_better(v, 3);
    cout << endl;
    two_sum_optimised(v, 3);
}