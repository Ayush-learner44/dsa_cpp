#include <iostream>
#include <vector>

using namespace std;

// Brute Force
vector<int> intersection(vector<int> v1, vector<int> v2)
{
    int n1 = v1.size(), n2 = v2.size();

    vector<int> visited(n2, 0);
    vector<int> ans;

    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            if (v1[i] == v2[j] and !visited[j])
            {
                ans.emplace_back(v2[j]);
                visited[j] = 1;
                break;
            }
            if (v1[i] < v2[j])
                break;
        }
    }
    return ans;
}

// optimal
vector<int> Intersection(vector<int> v1, vector<int> v2)
{
    int n1 = v1.size(), n2 = v2.size();
    int i = 0, j = 0;

    vector<int> ans;

    while (i < n1 and j < n2)
    {
        if (v1[i] == v2[j])
        {
            ans.emplace_back(v1[i]);
            i++, j++;
        }
        else if (v1[i] > v2[j])
            j++;
        else
            i++;
    }

    return ans;
}

int main()
{
    vector<int> v1 = {1, 1, 2, 3, 3, 6, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 10};
    vector<int> v2 = {3, 3, 3, 4, 5, 6, 7, 7, 7, 7, 7, 7, 8, 9};

    // vector<int> ans = intersection(v1, v2);
    vector<int> ans = Intersection(v1, v2);
    for (auto i : ans)
        cout << i << " ";
}