#include <iostream>
#include <vector>
using namespace std;

int merge(vector<int> &v, int start, int mid, int end)
{
    if (v.size() == 0)
        return 0;

    vector<int> temp;

    int i = start, j = mid + 1, count = 0;

    while (i <= mid and j <= end)
    {
        if (v[i] <= v[j])
            temp.push_back(v[i]), i++;
        else
        {
            count += (mid - i + 1);
            temp.push_back(v[j]), j++;
        }
    }

    while (i <= mid)
        temp.push_back(v[i]), i++;
    while (j <= end)
        temp.push_back(v[j]), j++;

    for (int i = 0; i < temp.size(); i++)
    {
        v[start + i] = temp[i];
    }

    return count;
}

int mergesort(vector<int> &v, int start, int end)
{
    if (start < end)
    {

        int mid = start + (end - start) / 2;

        int leftcount = mergesort(v, start, mid);
        int rightcount = mergesort(v, mid + 1, end);
        int inversionCount = merge(v, start, mid, end);

        return leftcount + rightcount + inversionCount;
    }

    return 0;
}

int main()
{
    vector<int> v = {1, 2, 5, 8, 3, 5, 2, 1, 3, 5};
    for (int i : v)
        cout << i << " ";
    cout << endl;

    int ans = mergesort(v, 0, v.size() - 1);

    cout << "Total counts: " << ans;
}