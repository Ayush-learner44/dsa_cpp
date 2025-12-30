#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

void hashing(string s)
{
    vector<int> v(27, 0);
    for (int i = 0; i < s.size(); i++)
    {

        char ch = (s[i]);
        if (isalpha(ch))
            ch = tolower(ch);
        v[ch - 'a']++;
    }

    for (int i = 0; i < 27; i++)
    {
        if (v[i] > 0)
        {
            cout << (char)(i + 'a') << ":" << v[i] << endl;
        }
    }
}

int main()
{
    string s;
    cout << "String?";
    getline(cin, s);

    hashing(s);
}