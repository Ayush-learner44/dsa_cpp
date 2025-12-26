#include <iostream>
using namespace std;

void pattern(int rows)
{
    for (int i = 0; i < rows; i++)
    {
        int stars = (1 + 2 * i);
        int spaces = rows - i + 1;
        while (spaces--)
        {
            cout << "  ";
        }
        while (stars--)
        {
            cout << "* ";
        }

        cout << endl;
    }
}
int main()
{
    int n;
    cout << "Enter the value of rows: ";
    cin >> n;
    pattern(n);
}