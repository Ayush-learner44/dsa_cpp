/*
 * @lc app=leetcode id=73 lang=cpp
 *
 * [73] Set Matrix Zeroes
 */

// @lc code=start

// Brute force...
class Solution
{
public:
    void setZeroes(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<int> row(n, 0), col(m, 0);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (matrix[i][j] == 0)
                {
                    row[i] = 1;
                    col[j] = 1;
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (row[i] or col[j])
                {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};
// @lc code=en

/// Optimal solution...just reduced the space and didn't change the time complexity at all ..
/*
 * @lc app=leetcode id=73 lang=cpp
 *
 * [73] Set Matrix Zeroes
 */

// @lc code=start
class Solution
{
public:
    void setZeroes(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        int m = matrix[0].size();

        int firstRowZero = 0, firstColZero = 0;

        for (int i = 0; i < m; i++)
        {
            if (matrix[0][i] == 0)
            {
                firstRowZero = 1;
                break;
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (matrix[i][0] == 0)
            {
                firstColZero = 1;
                break;
            }
        }

        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j < m; j++)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j < m; j++)
            {
                if (matrix[i][0] == 0 or matrix[0][j] == 0)
                {
                    matrix[i][j] = 0;
                }
            }
        }

        if (firstRowZero)
            for (int j = 0; j < m; j++)
            {
                matrix[0][j] = 0;
            }
        if (firstColZero)
            for (int i = 0; i < n; i++)
            {
                matrix[i][0] = 0;
            }
    }
};
// @lc code=end
