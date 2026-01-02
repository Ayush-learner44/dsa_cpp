#include <iostream>
#include <vector>
#include <set>
using namespace std;

// Brute Force
vector<int> Union(vector<int> v, vector<int> w)
{
    set<int> s;
    vector<int> temp;

    for (int i = 0; i < v.size(); i++)
    {
        s.emplace(v[i]);
    }
    for (int i = 0; i < w.size(); i++)
    {
        s.emplace(w[i]);
    }

    for (auto i : s)
        temp.emplace_back(i);

    return temp;
}

// Optimal Verisio
vector<int> Union_optimal(vector<int> v1, vector<int> v2)
{
    vector<int> temp;

    int i = 0, j = 0;

    while (i < v1.size() and j < v2.size())
    {
        if (v1[i] <= v2[j])
        {
            if (temp.empty() or temp.back() != v1[i])
            {
                temp.emplace_back(v1[i]);
            }
            if (v1[i] == v2[j])
                j++;
            i++;
        }
        else
        {

            if (temp.empty() or temp.back() != v2[j])
            {
                temp.emplace_back(v2[j]);
            }
            j++;
        }
    }

    while (j < v2.size())
    {
        if (temp.empty() or temp.back() != v2[j])
        {
            temp.emplace_back(v2[j]);
        }
        j++;
    }
    while (i < v1.size())
    {
        if (temp.empty() or temp.back() != v1[i])
        {
            temp.emplace_back(v1[i]);
        }
        i++;
    }

    return temp;
}

int main()
{
    vector<int> v1 = {1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 6, 7};
    vector<int> v2 = {1, 2, 2, 2, 4, 4, 4, 5, 6, 7, 8, 8, 8, 8, 8, 9, 9, 9};
    vector<int> result = Union_optimal(v1, v2);
    for (auto i : result)
        cout << i << " ";
}