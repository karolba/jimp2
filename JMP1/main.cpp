#include <iostream>
#include <regex>
#include <vector>

using namespace std;

#define D       "[0-9]"
#define NL      "((?:\\n)|(?:\\r)|(?:\\r\\n))"
#define IDENT   "([a-zA-Z][a-zA-Z0-9]*)"
#define EXPON   "(?:[Ee][+-]?" D "+)"
#define NUMBER  "((?:" D "+\\.?" D "*" EXPON "?)|(?:\\." D "+" EXPON "?))"

#define WHOLE "(?:" NUMBER "|" IDENT "|" NL "|(,)|(;)|([(])|([)])|(=)|(\\+)|(-)|(\\*)|(/)|(\\^))"

enum TYP {
    TYP_NULL,

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
    "",
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

class Token {
private:
   TYP type;
   string content;
public:

   Token(TYP typ, const string &s) {
       this->type = typ;
       content = s;
   }

   TYP getType() {
       return type;
   }

   string getName() {
       return name[getType()];
   }

   string getContent() {
       return content;
   }

   void wypisz() {
       cout << getName() << ": " << getContent() << '\n';
   }
};

int main()
{
    vector<Token> tokens;

    cout << "Hello World!" << endl;
    string input, binput;
    while(getline(cin, binput))
    {
         input += binput + "\n";
    }

    cout << endl << input << endl;
    regex token(WHOLE);
    smatch sm;

    auto tokens_begin = sregex_iterator(input.cbegin(), input.cend(), token);
    auto tokens_end = sregex_iterator();

    for (sregex_iterator i = tokens_begin; i != tokens_end; ++i) {
        smatch sm = *i;
        for(size_t i = 1; i < sm.size(); i++) {
            if(! sm[i].str().empty()) {
                Token token(static_cast<TYP>(i), sm.str());
                tokens.push_back(token);
            }
        }
    }

    for(Token &token : tokens) {
        token.wypisz();
    }

    return 0;
}
