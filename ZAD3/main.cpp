#include <iostream>
#include <map>
using namespace std;

int main()
{
    int num = 0, count = 0, max = 0;
    map <int, int> m;
    cin >> count;

    for (int i = 0; i < count; i++)
    {
        cin >> num;
        if (m.find(num) == m.end())
        {
            m[num] = 0;
        }
        m[num]++;
        if (max < m[num])
        {
            max = m[num];
        }
    }
    cout << max;
    for (auto i : m)
    {
        if (i.second == max)
        {
            cout << " " << i.first;
        }
    }
    cout << endl;
    return 0;
}
