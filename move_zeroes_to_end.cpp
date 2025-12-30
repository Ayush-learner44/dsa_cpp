#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// brute
vector<int> ZeroesLast(vector<int> &v)
{
    vector<int> temp;
    int n = v.size();

    for (int i = 0; i < n; i++)
    {
        if (v[i] != 0)
            temp.emplace_back(v[i]);
    }
    int zeroes = n - temp.size();

    for (int i = temp.size(); i < n; i++)
    {
        temp.emplace_back(0);
    }

    return temp;
}

// Optimal
void zeroesLast(vector<int> &v)
{
    int i = 0;

    int n = v.size();

    while (i < n)
    {
        if (v[i] == 0)
            break;
        i++;
    }

    if (i == (n - 1))
        return;

    for (int j = i + 1; j < n; j++)
    {
        if (v[j] != 0)
        {
            swap(v[i], v[j]);
            i++;
        }
    }
}

int main()
{
    vector<int> v = {1, 4, 0, 0, 0, 0, 5, 7, 3, 4, 2, 0, 4, 3, 1, 2};
    // vector<int> m = ZeroesLast(v);
    // for (auto i : m)
    //     cout << i << " ";
    zeroesLast(v);
    for (auto i : v)
        cout << i << " ";
}
