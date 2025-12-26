#include <iostream>
using namespace std;

void pattern(int rows)
{
    for (int i = rows; i > 0; i--)
    {
        int stars = (2 * i) - 1;
        int spaces = rows - i;
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