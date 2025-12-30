#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

// can't handle the worst case...
int Partition(vector<int> &v, int low, int high)
{
    int pivot = v[low];
    int i = low, j = high;
    while (i < j)
    {
        while (v[i] <= pivot and i < high)
            i++;
        while (v[j] > pivot and j > 0)
            j--;
        if (i < j)
            swap(v[i], v[j]);
    }

    swap(v[low], v[j]);

    return j;
}

// chooses the random....can handle the worst case broo....
int partition(vector<int> &v, int low, int high)
{
    int range = high - low + 1;
    int randomIndex = low + (rand() % range);
    swap(v[randomIndex], v[low]);

    int pivot = v[low], i = low, j = high;

    while (i < j)
    {
        while (v[i] <= pivot and i < high)
            i++;
        while (v[j] > pivot and j > 0)
            j--;
        if (i < j)
            swap(v[i], v[j]);
    }

    swap(v[low], v[j]);

    return j;
}

void QS(vector<int> &v, int low, int high)
{
    if (low < high)
    {
        int partitionIndex = partition(v, low, high);
        QS(v, low, partitionIndex - 1);
        QS(v, partitionIndex + 1, high);
    }
}

int main()
{
    vector<int> v = {4, 6, 2, 5, 7, 9, 1, 3};
    QS(v, 0, v.size() - 1);

    for (int x : v)
        cout << x << " ";
    return 0;
}