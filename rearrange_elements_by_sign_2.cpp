// arrange the +ve on even positions and -ves on the odd positions..that's it...but this time the number of -ves and +ves are not equal and therefore keep the rest numbers at the end.

#include <iostream>
#include <vector>

using namespace std;

// only one solution and that is the brute one ok..

void rearrange(vector<int> &v)
{
    vector<int> positive, negative;

    int n = v.size();

    for (int i = 0; i < n; i++)
    {
        if (v[i] >= 0)
            positive.emplace_back(v[i]);
        else
            negative.emplace_back(v[i]);
    }

    int i = 0, k = 0;

    while (k < positive.size() and k < negative.size())
    {
        v[i++] = positive[k];
        v[i++] = negative[k];
        k++;
    }

    while (k < positive.size())
    {
        v[i++] = positive[k++];
    }
    while (k < negative.size())
    {
        v[i++] = negative[k++];
    }
}

int main()
{
    // vector<int> v = {-1, 2, 3, 4, -6, -7, -8, 0, -3, -4, -8};
    vector<int> v = {-1, 2, 3, 4, -6, -7, -8, 0};
    rearrange(v);
    for (int i : v)
        cout << i << " ";
}