/*
     Jonathan Ishii
     Matthew Mikulka
     
     CPSC 323 - Section 1
     
     Assignment 2
 */

#include "LexicalAnalyzer.h"

bool printswitch = true;
//returns a col for the identifier DFSM
int char_to_col_identifier(char c)
{
    if (isdigit(c)) return 1;
    if (isalpha(c)) return 0;
    return 2;
}

//returns true if the string passed to it is an identifier
bool identifier_DFSM(const string &str)
{
    const int STATES = 5, INPUT = 3;
    int dfsmTable [STATES][INPUT] =
    {{0, 0, 0},
        {2, 0, 0},
        {3, 4, 0},
        {3, 4, 0},
        {3, 4, 0}};
    int state = 1;
    int strLength = int(str.length());
    for (int i = 0; i < strLength; ++i)
    {
        int col  = char_to_col_identifier(str[i]);
        state = dfsmTable[state][col];
    }
    if (state == 2 || state == 3) return true;
    return false;
}

// returns a col number for the integer/real DFSM
int number_to_col(char c)
{
    if (isdigit(c))
        return 0;
    else if (c == '.')
        return 1;
    else
        return 2;
}

// determines if the input is a integer or real
bool is_number_DFSM(const string &lexeme)
{
    const int STATES = 5, INPUT = 3;
    int dfsmTable [STATES][INPUT] = {
        {2, 3, 3},
        {2, 4, 3},
        {3, 3, 3},
        {5, 3, 3},
        {5, 3, 3}
    };
    int state = 1;
    int lexemeLength = int(lexeme.length());

    for(int i = 0; i < lexemeLength; ++i)
    {
        int col  = number_to_col(lexeme[i]);
        state = dfsmTable[state - 1][col];
    }

    if(state == 2 || state == 5)
    {
        return true;
    }
    return false;
}

bool is_integer(const string &lexeme)
{
    int lexemeLength = int(lexeme.length());

    for(int i = 0; i < lexemeLength; ++i)
    {
        if(!isdigit(lexeme[i]))
        {
            return false;
        }
    }
    return true;
}

// Checks to see if the lexeme is a separator
bool isSeparator(const string &lexeme, string &nextLexeme, ifstream &inFile)
{
    const int SIZE = 8;
    string separators[SIZE] = {"(", ")", ",", "{",
        "}", ";", ":", "$$"}; // list of all separators in the language

    // checks to see if it is a separator
    for (int i = 0; i < SIZE; ++i)
    {
        if (separators[i] == nextLexeme)
        {
            return true;
        }
    }

    // checks to see if it is the double $ sep.
    if (nextLexeme == "$")
    {
        // peeks at the next character
        char c = ' ';
        if (inFile)
        {
            inFile.get(c);
        }
        if(nextLexeme + c == "$$")
        {
            //means this is the first time this is going through the lexer and we will be outputting this
            if (lexeme == "")
            {
                nextLexeme += c;
                return true;
            }
            // means that there is already a lexeme being built and this is a delimiter for it
            inFile.putback(c);
            return true;
        }
        else
        {
            // means the next char wasn't a dollar sign and we put back the char and return false
            inFile.putback(c);
            return false;
        }
    }
    return false;
}

//checks to see if the lexeme is an operator
bool isOperator(const string &lexeme, string &nextLexeme, ifstream &inFile)
{
    const int SIZE = 6, SIZE_FINAL = 4;
    bool isOperator = false;
    string singleOperators[SIZE] = {"+", ">",
        "<", "-", "*", "/"};    //Array of single character operators
    for (int i = 0; i < SIZE; ++i)
    {
        if (singleOperators[i] == nextLexeme)
            return true;
    }
    if (nextLexeme == "^" || nextLexeme == "=") // checks to see if the lexer has the first character of a double character operator
    {
        if (inFile)
        {
            char c;
            inFile.get(c);
            nextLexeme += c;
            string finalOperators[SIZE_FINAL] = {"^=", "==", "=>", "=<"};
            for (int j = 0; j < SIZE_FINAL; ++j)
            {
                if(nextLexeme == finalOperators[j])
                {
                    isOperator = true;    //if lexeme is a double character operator returns true
                }
            }

            //means this is the first time this is going through the lexer and we will be outputting this
            if (lexeme == "" && isOperator)
            {
                return true;
            }

            inFile.putback(c);  //lexeme is not a double character operator. put back the last character removed from inFile.
            if (nextLexeme[0] == '^')   // since the lexeme is not a double character operator check wether the first characer is a '^'.
            {
                nextLexeme = "^";
                return false;       //if it is the lexeme is not a operator
            }
            nextLexeme = "=";   //the first character must be an equal sign, so reset lexeme to '='
            return true;
        }
    }
    return false;
}

//checks to see if the identifier is a keyword
bool isKeyword(const string &lexeme)
{
    string keywords[14] ={"function", "int", "bool", "real",
        "if", "ifend", "else","return", "put", "get", "while", "whileend",
        "true", "false"};
    string lowercaseLexeme = "";
    for (int i = 0; i < lexeme.length(); ++i)
    {
        lowercaseLexeme += tolower(lexeme[i]);
    }
    for (int i = 0; i < 14; ++i)
    {
        if (keywords[i] == lowercaseLexeme)
        {
            return true;
        }
    }
    return false;
}

tuple<bool, string> is_comment(char c, ifstream &inFile)
{
    char next;
    if (c == '[')
    {
        // gets the next character to see if the programmers is trying to make a comment
        inFile.get(next);
        if (next == '*')
        {
            // reads and ignores all the characters until '*]' is found or eof is reached
            char current;
            inFile.get(current);
            inFile.get(next);
            bool endComment = false;
            if (current == '*' && next == ']')
            {
                endComment = true;
            }
            while (inFile && !endComment)
            {
                current = next;
                inFile.get(next);
                if (current == '*' && next == ']')
                {
                    endComment = true;
                }
            }

            // need this just in case file ends before the end of comment can be found
            if (!endComment)
            {
                return make_tuple(false, "Unknown");
            }
            else
            {
                return make_tuple(true, "1");;
            }
        }
        else
        {
            inFile.putback(next);
            return make_tuple(false, "Not a comment");
        }
    }
    return make_tuple(false, "Not a comment");
}

tuple<string, string> lexer(ifstream &inFile)
{
    tuple<string, string> token = actualLexer(inFile);
    if (printswitch)
    {
        cout << left << "Token: " << setw(20) << get<0>(token) << "Lexeme: " << setw(20) << get<1>(token) << endl;
        if(get<0>(token) == "Unknown")
        {
            cout << "ERROR: Unknown token.\n";
            exit(1);
        }
    }
    return token;
}

tuple<string, string> actualLexer(ifstream &inFile)
{
    char c;
    string lexeme, nextLexeme;
    bool endOfLexeme = false;

    if (inFile.is_open())
    {
        // get the first character from file
        inFile.get(c);
        
        // reads all the leading whitespace of the file to the first non-whitespace
        while (inFile && (isspace(c) || c == '\n'))
        {
            inFile.get(c);
        }
        if (!inFile.eof())
        {
            inFile.putback(c);
        }
        // builds the lexeme until a space, separator, or operator is found because numbers or identifiers can be separated by operators
        // or separators in arithmetic operations.  i.e a=2+x; is the same as a = 2 + x ;
        while(!inFile.eof() && !endOfLexeme)
        {
            inFile.get(c);
            nextLexeme = c;
            if (isspace(c))
            {
                // just in case a comment was found at the end after a lexeme was returned so it doesn't return nothing
                if (lexeme != "")
                {
                    endOfLexeme = true;
                }
            }
            else if (c == '[')
            {
                // the next character could be part of a comment.
                tuple<bool, string> value = is_comment(c, inFile);
                bool isComment = get<0>(value);
                if (!isComment)
                {
                    if (get<1>(value) == "Unknown")
                    {
                        if (lexeme == "")
                        {
                            return make_tuple("Unknown", "Unable to find end of comment");
                        }
                    }
                    lexeme += '[';
                }
            }
            else if (isSeparator(lexeme, nextLexeme, inFile))
            {
                // means it is the start of a lexeme and then it should be return since a token was found
                if (lexeme == "")
                {
                    return make_tuple("Separator", nextLexeme);
                }
                // means a sep was found but it is next to a non sep so it should be put back and end the loop since it could
                // mean an arithmetic operation
                inFile.putback(c);
                endOfLexeme = true;
            }
            else if (isOperator(lexeme, nextLexeme, inFile))
            {
                // means it is the start of a lexeme and then it should be return since a token was found
                if (lexeme == "")
                {
                    return make_tuple("Operator", nextLexeme);
                }
                // means a sep was found but it is next to a non sep so it should be put back and end the loop since it could
                // mean an arithmetic operation
                inFile.putback(c);
                endOfLexeme = true;
            }
            else
            {
                lexeme += c;
            }
        }

        // means a space, separator, or operator was found to end the lexeme
        if (identifier_DFSM(lexeme))
        {
            if(isKeyword(lexeme))
            {
                return make_tuple("Keyword", lexeme);
            }
            else
            {
                return make_tuple("Identifier", lexeme);
            }
        }
        else if (is_number_DFSM(lexeme))
        {
            if (is_integer(lexeme))
            {
                return make_tuple("Integer", lexeme);
            }
            return make_tuple("Real", lexeme);
        }
        else
        {
            return make_tuple("Unknown", lexeme);
        }
    }
    else
    {
        cerr << "Error: File is not open.";
        return make_tuple("Unknown", lexeme);
    }
}
