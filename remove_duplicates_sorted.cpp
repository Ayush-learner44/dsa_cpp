#include <iostream>
#include <vector>
#include <set>

using namespace std;

// Brute force
int removeDuplicate(vector<int> &v)
{
    set<int> s;

    for (int i = 0; i < v.size(); i++)
    {
        s.emplace(v[i]);
    }

    int index = 0;

    for (auto i : s)
    {
        v[index++] = i;
    }
    return index;
}

// Optimal Approach 2-pointer
int RemoveDuplicate(vector<int> &v)
{
    int i = 0;
    for (int j = 1; j < v.size(); j++)
    {
        if (v[i] != v[j])
        {
            v[++i] = v[j];
        }
    }
    return i + 1;
}

int main()
{
    vector<int> v = {1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 5, 5};
    int size = RemoveDuplicate(v);
    for (int i = 0; i < size; i++)
    {
        cout << v[i] << " ";
    }
}