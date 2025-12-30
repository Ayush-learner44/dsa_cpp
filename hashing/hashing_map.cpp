#include <iostream>
#include <map>
#include <string>

using namespace std;

void hashing(string s)
{
    map<char, int> m;
    for (int i = 0; i < s.size(); i++)
    {
        char ch = s[i];
        if (isalpha(ch))
        {
            m[ch]++;
        }
    }
    for (auto i : m)
    {
        cout << i.first << ":" << i.second << endl;
    }
}

int main()
{
    string s;
    printf(
        "String??");
    getline(cin, s);
    hashing(s);
}