#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//returns a col for the identifier DFSM
int char_to_col_identifier(char c)
{
    if (c >= 'a' && c <= 'z')
        return 1;
    if (c >= 'a' && c <= 'Z')
        return 1;
    if (c >= '0' && c <= '9')
        return 0;
    return 2;
}

//returns true if the string passed to it is an identifier
bool identifier_DFSM(string str)
{
    int dfsmTable [2][4] = {{0, 3, 3, 3},{2, 4, 4, 4}};
    int state = 1;
    int strLength = int(str.length());
    for (int i = 0; i < strLength; ++i)
    {
        int col  = char_to_col_identifier(str[i]);
        state = dfsmTable[col][state];
    }
    if (state == 2 || state == 4) return true;
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
bool is_number_DFSM(string lexeme)
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

// Checks to see if the lexeme is a separator
bool isSeparator(string &lexeme, ifstream &inFile)
{
    string separators[7] = {"(", ")", ",", "{",
        "}", ";", "$$"}; // list of all separators in the language
    if (lexeme == "$")
    {
        char c;
        if (!inFile.eof())
        {
            inFile.get(c);
            lexeme += c;
        }
    }
    for (int i = 0; i < 7; ++i)
    {
        if (separators[i] == lexeme)
        {
            return true;
        }
    }
    return false;
}

//checks to see if the lexeme is an operator
bool isOperator(string &lexeme, ifstream &inFile)
{
    string singleOperators[6] = {"+", ">",
        "<", "-", "*", "/"};    //Array of single character operators
    for (int i = 0; i < 6; ++i)
    {
        if (singleOperators[i] == lexeme)
            return true;
    }
    if (lexeme == "^" || lexeme == "=") // checks to see if the lexer has the first character of a double character operator
    {
        if (!inFile.eof())
        {
            char c;
            inFile.get(c);
            lexeme += c;
            string finalOperators[4] = {"^=", "==", "=>", "=<"};
            for (int j = 0; j < 4; ++j)
            {
                if(lexeme == finalOperators[j])
                {
                    return true;    //if lexeme is a double character operator returns true
                }
            }
            inFile.putback(c);  //lexeme is not a double character operator. put back the last character removed from inFile.
            if (lexeme[0] == '^')   // since the lexeme is not a double character operator check wether the first characer is a '^'.
            {
                return false;       //if it is the lexeme is not a operator
            }
            lexeme = "=";   //the first character must be an equal sign, so reset lexeme to '='
            return true;
        }
    }
    return false;
}

//checks to see if the identifier is a keyword
bool isKeyword(string &lexeme)
{
    string keywords[14] ={"function", "int", "bool", "real",
        "if", "ifend", "else","return", "put", "get", "while", "whileend",
        "true", "false"};
    for (int i = 0; i < 14; ++i)
    {
        if (keywords[i] == lexeme)
        {
            return true;
        }
    }
    return false;
}

tuple<string, string> lexer(ifstream &inFile)
{
    char c;
    string lexeme = "";
    if(!inFile.eof())
    {
        inFile.get(c);
        lexeme += c;
        if (isSeparator(lexeme, inFile))
        {
            return make_tuple(lexeme, "Separator");
        }
        else if (isOperator(lexeme, inFile))
        {
            return make_tuple(lexeme, "Operator");
        }
        else if (identifier_DFSM(lexeme))   // check to see if the lexeme is an identifier
        {
            while (!inFile.eof())
            {
                inFile.get(c);
                if (isspace(c)) //checks to see if character is a space
                {
                    // checks to see if the lexeme is a keyword
                    if (identifier_DFSM(lexeme))
                    {
                        if (isKeyword(lexeme))
                        {
                            return make_tuple(lexeme, "Keyword");
                        }
                        return make_tuple(lexeme, "Identifier");
                    }
                    else
                    {
                        return make_tuple(lexeme, "Invalid Token");
                    }
                }
                //check to see if the character is not an letter or number and if infile is at the end of the file.
                if(!isalnum(c) || inFile.eof())
                {
                    if (identifier_DFSM(lexeme))
                    {
                        if (isKeyword(lexeme))
                        {
                            return make_tuple(lexeme, "Keyword");
                        }
                        //if c is not a space, letter, or digit returns c to inFile.
                        inFile.putback(c);
                        return make_tuple(lexeme, "Identifier");
                    }
                    else
                    {
                        return make_tuple(lexeme, "Invalid Token");
                    }
                }
                lexeme += c;
            }
        }
        else if(is_number_DFSM(lexeme)) // check to see if lexeme is a real or integer
        {
            while(!inFile.eof())
            {
                inFile.get(c);
                if (isspace(c))
                {
                    return make_tuple(lexeme, "Integer");
                }
                else if (c == '.')
                {
                    lexeme += c;
                    inFile.get(c);
                    lexeme += c;
                    while (!inFile.eof() && isdigit(c))
                    {
                        lexeme += c;
                        inFile.get(c);
                    }
                    if(!isspace(c))
                    {
                        inFile.putback(c);
                    }
                    return make_tuple(lexeme, "Real");
                }
                lexeme += c;
            }
        }
    }
    return make_tuple(lexeme, "Invalid Token");
}

int main() {
    
    // filepath to code
    string filepath = "example.txt";
    
    // opening the input file
    ifstream inFile;
    inFile.open(filepath);
    
    //opening the output file
    ofstream outfile;
    filepath = "ouput.txt";
    outfile.open(filepath);
    outfile << left << setw(20) << "token" << setw(20) << "lexeme" << endl;
    for (int i = 0; i < 40; ++i)
    {
        outfile << '-';
    }
    outfile << endl;
    
    
    // reads one character at a time till end of file and outputs token with lexeme
    if (inFile.is_open())
    {
        char c;
        
        //starts building lexemes
        while (!inFile.eof())
        {
            // get the first character from file
            inFile.get(c);
            
            // reads all the leading whitespace of the file to the first non-whitespace
            while (!inFile.eof() && isspace(c))
            {
                inFile.get(c);
            }
            
            // first checks for possible comment
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
                    if (current == '*' && next == ']') {
                        endComment = true;
                    }
                    while (!inFile.eof() && !endComment)
                    {
                        current = next;
                        inFile.get(next);
                        
                        if (current == '*' && next == ']') {
                            endComment = true;
                        }
                    }
                }
                else
                {
                    // only the '[' symbol was read and we have to putback the character we peeked at
                    inFile.putback(next);
                }
            }
            else{
                if (c != '[' && !isspace(c))
                {
                    inFile.putback(c);
                }
                tuple<string, string> token = lexer(inFile);
                outfile << left << setw(20) << get<0>(token) << setw(20) << get<1>(token) << endl;
                //cout << left << setw(20) << get<0>(token) << setw(20) << get<1>(token) << endl;
            }
        }
    }
    
    // closes file
    inFile.close();
}
