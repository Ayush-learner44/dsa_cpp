#include <iostream>
#include <vector>

using namespace std;

// Brute force
void arrange(vector<int> &v)
{
    sort(v.begin(), v.end());
}

// Better solution
void arrange_better(vector<int> &v)
{
    int zeroes = 0, ones = 0, twos = 0;
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == 0)
            zeroes++;
        else if (v[i] == 1)
            ones++;
        if (v[i] == 2)
            twos++;
    }
    int i = 0;
    while (zeroes--)
    {
        v[i] = 0;
        i++;
    }
    while (ones--)
    {
        v[i] = 1;
        i++;
    }
    while (twos--)
    {
        v[i] = 2;
        i++;
    }
}

// optimal
// Dutch National Flag Algorithm
void arrange_optimal(vector<int> &v)
{
    int low = 0;
    int mid = 0;
    int high = v.size() - 1;

    while (high >= mid)
    {
        if (v[mid] == 0)
        {
            swap(v[mid], v[low]);
            mid++, low++;
        }
        else if (v[mid] == 1)
            mid++;
        else
        {
            swap(v[high], v[mid]);
            high--;
        }
    }
}

int main()
{
    vector<int> v = {0, 1, 1, 0, 1, 0, 0, 1, 2, 0, 2, 1, 0, 1};
    // arrange(v);
    // arrange_better(v);
    arrange_optimal(v);
    for (auto i : v)
        cout << i << " ";
}