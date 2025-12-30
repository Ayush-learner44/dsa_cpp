#include <iostream>
#include <vector>

using namespace std;

void shiftByone(vector<int> &v)
{
    int temp = v[0];
    for (int i = 1; i < v.size(); i++)
    {
        v[i - 1] = v[i];
    }
    v[v.size() - 1] = temp;
}

// Brute force
void shiftByK(vector<int> &v, int k)
{
    int n = v.size();
    k = k % n;
    if (k == 0)
        return;

    vector<int> temp;
    for (int i = 0; i < k; i++)
    {
        temp.emplace_back(v[i]);
    }

    for (int i = k; i < n; i++)
    {
        v[i - k] = v[i];
    }

    for (int i = n - k; i < n; i++)
    {
        v[i] = temp[i - (n - k)];
    }
}

// Optimal
void shiftByD(vector<int> &v, int d)
{
    int n = v.size();
    d = d % n;
    if (d == 0)
        return;

    reverse(v.begin(), v.begin() + d);
    reverse(v.begin() + d, v.end());
    reverse(v.begin(), v.end());
}

int main()
{
    vector<int> v = {1, 2, 3, 4, 5};
    shiftByD(v, 2);
    // shiftByone(v);
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
}