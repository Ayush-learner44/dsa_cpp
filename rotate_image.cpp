class Solution
{
public:
    void rotate(vector<vector<int>> &matrix)
    {
        vector<vector<int>> ans = matrix;
        int rows = matrix.size();
        int cols = matrix[0].size();

        // Brute force approach
        // for (int i = 0; i < rows; i++) {
        //     for (int j = 0; j < cols; j++) {
        //         ans[j][rows-1-i] = matrix[i][j];
        //     }
        // }

        // for (int i = 0; i < rows; i++) {
        //     for (int j = 0; j < cols; j++) {
        //         matrix[i][j] = ans[i][j];
        //     }
        // }

        // Transposing the matrix
        for (int i = 0; i < rows - 1; i++)
        {
            for (int j = i + 1; j < rows; j++)
            {
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        // reverses every single row
        for (int i = 0; i < rows; i++)
        {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};