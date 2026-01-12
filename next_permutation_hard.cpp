// Narayana Pandita's Algorithm (Next Permutation)
#include <iostream>
#include <vector>
#include <algorithm> // Essential for reverse()

using namespace std;

// Built-in STL function for reference
void nextPermutation(vector<int> &v)
{
    next_permutation(v.begin(), v.end());
}

/* Optimal Approach Logic:
   1. Find the "breakpoint" (the first dip from the right).
   2. Find the "next best" number to swap with (slightly larger than the dip).
   3. Reverse the tail to make it as small as possible.
*/
void next_permutation_optimal(vector<int> &v)
{
    int n = v.size();

    // STEP 1: Find the first "dip" from right to left.
    // We start at n-2 because we need to compare i with i+1.
    // Why from right? Because we want the smallest lexicographical change.
    int index = -1;
    for (int i = n - 2; i >= 0; i--)
    {
        if (v[i] < v[i + 1]) // Found a number smaller than its neighbor!
        {
            index = i;
            break;
        }
    }

    // EDGE CASE: If no dip is found (index stays -1), the array is in
    // max descending order (e.g., 3 2 1). The "next" is the reverse (1 2 3).
    if (index == -1)
    {
        reverse(v.begin(), v.end());
        return;
    }

    // STEP 2: Find the successor to v[index].
    // Since everything to the right of 'index' is descending, the first
    // number we hit from the right that is > v[index] is the smallest possible increase.
    for (int i = n - 1; i > index; i--)
    {
        // Using >= ensures we find the next valid digit, though strictly > is usually safer.
        if (v[i] >= v[index])
        {
            swap(v[index], v[i]);
            break; // VERY IMPORTANT: Stop after the first swap!
        }
    }

    // STEP 3: The tail (everything after index) is currently in descending order.
    // Descending order = Largest possible number for those digits.
    // To get the smallest increase overall, we need this tail to be the
    // SMALLEST possible (Ascending order). Reversing it does exactly that.
    reverse(v.begin() + index + 1, v.end());
}

int main()
{
    vector<int> v = {2, 1, 3};

    // Test built-in
    nextPermutation(v);
    for (int i : v)
        cout << i << " "; // Output: 2 3 1

    cout << endl;

    // Test your optimal
    next_permutation_optimal(v);
    for (int i : v)
        cout << i << " "; // Output: 3 1 2

    return 0;
}