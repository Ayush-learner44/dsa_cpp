#include <iostream>
using namespace std;

// Bad merge...
void Merge(vector<int> &v, int low, int mid, int high)
{

    int left = low, right = mid + 1;
    vector<int> temp;

    while (left <= mid and right <= high)
    {
        if (v[left] <= v[right])
        {
            temp.emplace_back(v[left]);
            left++;
        }
        else
        {

            temp.emplace_back(v[right]);
            right++;
        }
    }
    while (left <= mid)
    {
        temp.emplace_back(v[left]);
        left++;
    }
    while (right <= high)
    {
        temp.emplace_back(v[right]);
        right++;
    }

    for (int i = low, j = 0; i <= high; i++, j++)
    {
        v[i] = temp[j];
    }
}

// Better Merge
void merge(vector<int> &v, int low, int mid, int high)
{
    int left = low, right = mid + 1;
    vector<int> temp(high - low + 1);
    int k = 0;

    while (left <= mid and right <= high)
    {
        if (v[left] <= v[right])
            temp[k++] = v[left++];
        else
            temp[k++] = v[right++];
    }

    while (left <= mid)
        temp[k++] = v[left++];
    while (right <= high)
        temp[k++] = v[right++];

    for (int i = low; i <= high; i++)
    {
        v[i] = temp[i - low];
    }
}

void merge_sort(vector<int> &v, int low, int high)
{
    if (low >= high)
        return;
    int mid = low + (high - low) / 2;
    merge_sort(v, low, mid);
    merge_sort(v, mid + 1, high);
    merge(v, low, mid, high);
}

int main()
{
    // vector<int> v = {2, 5, 7, 4, 1, 9, 3, 7, 2, 8, 9, 6, 4};
    vector<int> v = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    merge_sort(v, 0, v.size() - 1);
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
}