#include <iostream>
#include <regex>

using namespace std;

#define D       "[0-9]"
#define NL      "((\n)|(\r)|(\r\n))"
#define IDENT   "([a-zA-Z][a-zA-Z0-9]*)"
#define EXPON   "([Ee][+-]?{D}+)"
#define NUMBER  "(({D}+\.?{D}*{EXPON}?)|(\.{D}+{EXPON}?))"

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
