// Majority_element > n/2

#include <iostream>
#include <vector>
using namespace std;

int majority_element(vector<int> v)
{
    int count = 0;
    int n = v.size();
    for (int i = 0; i < n; i++)
    {
        count = 0;
        int k = v[i];
        for (int j = 0; j < n; j++)
        {
            if (k == v[j])
                count++;
        }
        if (count > n / 2)
            return k;
    }
    return -1;
}

// better
int majority_element_better(vector<int> v)
{
    int count = v.size();
    unordered_map<int, int> hash;

    for (int i = 0; i < count; i++)
    {
        hash[v[i]]++;
    }
    int majority_element = -1;

    for (auto i : hash)
    {
        if (i.second > count / 2)
            return i.first;
    }
    return -1;
}

// Moore's voting algo
int majority_element_optimal(vector<int> v)
{
    int count = v.size();
    int majority_element = -1, temp_count = 0;

    for (int i = 0; i < count; i++)
    {
        if (temp_count == 0)
        {
            majority_element = v[i];
            temp_count = 1;
        }
        else if (majority_element == v[i])
            temp_count++;
        else
            temp_count--;
    }

    int actual_count = 0;

    for (int i = 0; i < count; i++)
    {
        if (majority_element == v[i])
            actual_count++;
    }

    if (actual_count > count / 2)
        return majority_element;

    return -1;
}

int main()
{
    vector<int> v = {1, 2, 2, 1, 1, 1, 1, 1, 3, 3};
    cout << majority_element(v) << endl;
    cout << majority_element_better(v) << endl;
    cout << majority_element_optimal(v) << endl;
}