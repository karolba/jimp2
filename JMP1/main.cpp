#include <iostream>
#include <regex>

using namespace std;

#define D       "[0-9]"
#define NL      "((?:\n)|(?:\r)|(?:\r\n))"
#define IDENT   "([a-zA-Z][a-zA-Z0-9]*)"
#define EXPON   "(?:[Ee][+-]?" D "+)"
#define NUMBER  "((?:" D "+\\.?" D "*" EXPON "?)|(?:\\." D "+" EXPON "?))"

#define WHOLE "(?:" NUMBER "|" IDENT "|" NL "|(,)|(;)|([(])|([)])|(=)|(+)|(-)|(*)|(/)|( ))"

enum TYP {
    TYP_NUMERIC,
    TYP_IDENTIFIER,
    TYP_ENDLINE,
    TYP_COMMA,
    TYP_SEMICOLON,
    TYP_LEFT_PARENTHESIS,
    TYP_RIGHT_PARENTHESIS,
    TYP_ASSIGN,
    TYP_PLUS,
    TYP_MINUS,
    TYP_MULTIPLY,
    TYP_DIVIDE,
    TYP_EXPONENTIAL
};

const char *name[] = {
    "Numeric",
    "Identifier",
    "Endline",
    "Comma",
    "Semicolon",
    "Left Parenthesis",
    "Right Parenthesis",
    "Assign",
    "Plus",
    "Minus",
    "Multiply",
    "Divide",
    "Exponential"
};

int main()
{
    cout << "Hello World!" << endl;
    string input, binput;
    while(getline(cin, binput))
    {
         input += binput + "\n";
    }

    cout << endl << input << endl;
    regex token(WHOLE);
    smatch sm;

    if(regex_search(input.cbegin(), input.cend(), sm, token)) {
        for(size_t i = 1; i < sm.size(); i++) {
            if(sm.position(i) == 0) {
                cout << name[i] << ": " << sm[i] << '\n';
            }
        }
    }
    return 0;
}
