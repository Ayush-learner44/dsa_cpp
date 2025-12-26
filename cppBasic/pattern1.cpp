#include <iostream>
using namespace std;

void pattern(int rows)
{
    for (int i = 0; i < rows; i++)
    {
        int j = (rows - i);
        while (j--)
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