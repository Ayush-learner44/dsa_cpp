#include <iostream>
using namespace std;

void pattern(int rows)
{

    int k = 1;
    for (int i = 1; i <= rows; i++)
    {

        int j = i;

        while (j--)
        {
            cout << k++ << " ";
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