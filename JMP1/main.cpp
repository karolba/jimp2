#include <iostream>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    string input, binput;
    while(getline(cin, binput))
    {
         input += binput;
    }
    cout << endl << input << endl;
    return 0;
}
