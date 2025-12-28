#include <iostream>
#include <vector>

using namespace std;

void subsequences(int arr[], vector<vector<int>> &v, vector<int> &temp, int size, int index)
{
    if (index >= size)
    {
        v.emplace_back(temp);
        return;
    }

    temp.emplace_back(arr[index]);

    subsequences(arr, v, temp, size, index + 1);
    temp.pop_back();

    subsequences(arr, v, temp, size, index + 1);
}

int main()
{
    int arr[4] = {3, 2, 1, 0};
    vector<vector<int>> sequences;
    vector<int> v;
    int j = 1;
    subsequences(arr, sequences, v, 4, 0);
    for (auto it : sequences)
    {

        cout << j++ << ": { ";
        for (auto i : it)
            cout << i << " ";
        cout << "}";
        cout << endl;
    }
}