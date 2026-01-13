class Solution
{
public:
    vector<int> spiralOrder(vector<vector<int>> &v)
    {
        if (v.empty() || v[0].empty())
            return {};

        int rows = v.size();
        int cols = v[0].size();

        vector<int> ans;

        int left = 0, right = cols - 1, top = 0, bottom = rows - 1;

        while (left <= right and top <= bottom)
        { // right
            for (int i = left; i <= right; i++)
            {
                ans.push_back(v[top][i]);
            }
            top++;

            // down

            for (int i = top; i <= bottom; i++)
            {
                ans.push_back(v[i][right]);
            }
            right--;

            // left
            if (top <= bottom)
            {
                for (int i = right; i >= left; i--)
                {
                    ans.push_back(v[bottom][i]);
                }
                bottom--;
            }
            // up

            if (left <= right)
            {
                for (int i = bottom; i >= top; i--)
                {
                    ans.push_back(v[i][left]);
                }
                left++;
            }
        }

        return ans;
    }
};