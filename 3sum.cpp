// brute force;

class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &v)
    {
        int rows = v.size();

        vector<int> triplet;
        set<vector<int>> set;

        for (int i = 0; i <= rows - 3; i++)
        {
            int first = v[i];
            for (int j = i + 1; j <= rows - 2; j++)
            {
                int second = v[j];
                for (int k = j + 1; k <= rows - 1; k++)
                {
                    int third = v[k];
                    if ((first + second + third) == 0)
                    {
                        triplet = {first, second, third};
                        sort(triplet.begin(), triplet.end());
                        set.insert(triplet);
                    }
                }
            }
        }
        vector<vector<int>> ans(set.begin(), set.end());
        return ans;
    }
};

// better one ....

class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &v)
    {

        int rows = v.size();
        set<int> st;
        set<vector<int>> triplet;

        for (int i = 0; i < rows; i++)
        {
            int first = v[i];
            st.clear();
            for (int j = i + 1; j < rows; j++)
            {
                int second = v[j];

                int third = -(first + second);

                if (st.find(third) != st.end())
                {
                    vector<int> temp = {first, second, third};
                    sort(temp.begin(), temp.end());
                    triplet.insert(temp);
                }
                else
                {
                    st.insert(second);
                }
            }
        }

        vector<vector<int>> ans(triplet.begin(), triplet.end());
        return ans;
    }
};

// Optimal two pointers;
class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &v)
    {

        int n = v.size();
        vector<vector<int>> ans;
        sort(v.begin(), v.end());

        int low = 0, high = 0;

        for (int i = 0; i < n; i++)
        {
            if (i > 0 and v[i] == v[i - 1])
                continue;
            low = i + 1, high = n - 1;

            while (low < high)
            {
                int sum = v[i] + v[low] + v[high];
                if (sum < 0)
                    low++;
                else if (sum > 0)
                    high--;
                else
                {
                    vector<int> temp = {v[i], v[low], v[high]};
                    ans.emplace_back(temp);

                    while (low < high and v[low] == v[low + 1])
                        low++;
                    while (low < high and v[high] == v[high - 1])
                        high--;

                    low++, high--;
                }
            }
        }
        return ans;
    }
};