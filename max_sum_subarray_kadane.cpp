#include <iostream>
#include <vector>

using namespace std;

// extreme brute force
int maximum(vector<int> v)
{
    int n = v.size();
    int maxSum = -999999;

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            int sum = 0;

            for (int k = i; k < j; k++)
            {
                sum += v[k];
            }
            if (sum > maxSum)
            {
                maxSum = sum;
            }
        }
    }
    return maxSum;
}

// better than brute
int maximum_better(vector<int> v)
{
    int count = v.size();
    int maxSum = -999999;
    for (int i = 0; i < count; i++)
    {
        int sum = 0;
        for (int j = i; j < count; j++)
        {
            sum += v[j];
            if (sum > maxSum)
                maxSum = sum;
        }
    }
    return maxSum;
}

// kadandes algo
int maximum_optimised(vector<int> v)
{
    int maxSum = -999999;
    int sum = 0;

    for (int i : v)
    {
        sum += i;
        if (sum < 0)
            sum = 0;
        else
        {
            maxSum = max(sum, maxSum);
        }
    }
    return maxSum < 0 ? 0 : maxSum;
}

void maximum_optimised_subarray(vector<int> v)
{
    int maxSum = -999999;
    int sum = 0;
    int k = 0, start = 0, begin = -1, end = -1;

    for (int i : v)
    {
        if (sum == 0)
            start = k;

        sum += i;

        if (sum < 0)
        {
            sum = 0;
        }
        if (sum > maxSum)
        {
            maxSum = sum;
            begin = start;
            end = k;
        }
        ++k;
    }

    for (int i = begin; i <= end; i++)
    {

        cout << v[i] << " ";
    }
}

int main()
{
    vector<int> v = {-2, -3, 4, -1, -2, 1, 5, -3};
    // vector<int> v = {-2, -3, -3};
    cout << maximum(v) << endl;
    cout << maximum_better(v) << endl;
    cout << maximum_optimised(v) << endl;
    maximum_optimised_subarray(v);
}