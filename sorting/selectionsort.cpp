#include <iostream>
#include <vector>

using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void selectionSort(vector<int> &v)
{
    for (int i = 0; i < v.size() - 1; i++)
    {
        int minIndex = i;
        for (int j = i; j < v.size(); j++)
        {
            if (v[j] < v[minIndex])
                minIndex = j;
        }
        if (i != minIndex)
            swap(v[i], v[minIndex]);
    }
}

int main()
{
    vector<int> v = {7, 6, 5, 4, 3, 2, 1, 67, 789, 32, 45, 324};
    selectionSort(v);
    for (int i = 0; i < v.size(); i++)
    {
        printf("%d ", v[i]);
    }
}