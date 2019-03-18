#include <iostream>
#include <map>
using namespace std;

int main()
{
    int num = 0, liczba1=0;
    map <int,int> m;
    cout << "Hello World!" << endl;
    cin >> liczba1;
    for (int i=0; i<liczba1; i++)
    {
    cin >> num;
    if(m.find(num)==m.end())
            {m[num]=0;}
    m[num]++;
    }
    return 0;
}
