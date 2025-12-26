#include <iostream>
using namespace std;

void pattern(int rows)
{

    for (int i = 0; i < rows; i++)
    {
        int stars = (i + 1);

        while (stars--)
        {

            cout << (stars + 1) % 2 << " ";
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