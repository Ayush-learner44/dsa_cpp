#include <iostream>
#include <vector>

using namespace std;

class solution
{
public:
    vector<vector<int>> foursum(vector<int> &v)
    {
        sort(v.begin(), v.end());
        int n = v.size();

        vector<vector<int>> ans;

        for (int i = 0; i < n; i++)
        {
            if (i > 0 and v[i] == v[i - 1])
                continue;

            for (int j = i + 1; j < n; j++)
            {
                int low = j + 1, high = n - 1;
                if (j > i + 1 and v[j] == v[j - 1])
                    continue;

                while (low < high)
                {
                    int sum = v[i] + v[j] + v[low] + v[high];

                    if (sum > 0)
                        high--;
                    else if (sum < 0)
                        low++;
                    else
                    {
                        vector<int> temp = {v[i], v[j], v[low], v[high]};
                        sort(temp.begin(), temp.end());
                        ans.emplace_back(temp);

                        while (low < high and v[low] == v[low + 1])
                            low++;
                        while (low < high and v[high] == v[high - 1])
                            high--;

                        low++, high--;
                    }
                }
            }
        }
        return ans;
    }
};

int main()
{
    solution sol;

    vector<int> nums = {1, 0, -1, 0, -2, 2};
    // vector<int> nums = {2, 2, 2, 2, 2};
    // vector<int> nums = {1, 2, 3, 4};
    // vector<int> nums = {-3, -1, 0, 2, 4, 5};
    vector<vector<int>> ans = sol.foursum(nums);

    for (auto i : ans)
    {
        cout << "[";
        for (auto j : i)
            cout
                << j << " ";
        cout << "]" << endl;
    }
}