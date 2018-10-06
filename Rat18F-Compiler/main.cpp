#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//returns a col for the identifier DFSM
int char_to_col_identifier(char c)
{
    if (isdigit(c)) return 1;
    if (isalpha(c)) return 0;
    return 2;
}

//returns true if the string passed to it is an identifier
bool identifier_DFSM(string str)
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
        if (inFile)
        {
            inFile.get(c);
        }
        if(lexeme + c == "$$")
        {
            lexeme += c;
            return true;
        }
        else
        {
            inFile.putback(c);
            return false;
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
        if (inFile)
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
                lexeme = "^";
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

tuple<string, string> lexer(ifstream &inFile)
{
    char c;
    string lexeme = "";
    if(inFile)
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
            while (inFile)
            {
                inFile.get(c);
                //check to see if the character is not an letter or number and if infile is at the end of the file.
                if(!isalnum(c) || inFile.eof())
                {
                    inFile.putback(c);
                    if (identifier_DFSM(lexeme))
                    {
                        if (isKeyword(lexeme))
                        {
                            return make_tuple(lexeme, "Keyword");
                        }
                        //if c is not a space, letter, or digit returns c to inFile.
                        return make_tuple(lexeme, "Identifier");
                    }
                    else
                    {
                        inFile.putback(c);
                        return make_tuple(lexeme, "Invalid Token");
                    }
                }
                lexeme += c;
            }
        }
        else if(is_number_DFSM(lexeme)) // check to see if lexeme is a real or integer
        {
            while(inFile)
            {
                inFile.get(c);
                if (c == '.')
                {
                    lexeme += c;
                    inFile.get(c);
                    while (inFile && isdigit(c))
                    {
                        lexeme += c;
                        inFile.get(c);
                    }
                    if(!isspace(c))
                    {
                        if (is_number_DFSM(lexeme))
                        {
                            inFile.putback(c);
                        }
                        else
                        {
                            return make_tuple(lexeme, "Invalid Token");
                        }
                    }
                    return make_tuple(lexeme, "Real");
                }
                else if (!isalnum(c))
                {
                    inFile.putback(c);
                    if (is_number_DFSM(lexeme))
                    {
                        return make_tuple(lexeme, "Integer");
                    }
                    else
                    {
                        return make_tuple(lexeme, "Invalid Token");
                    }
                }
                lexeme += c;
            }
        }
    }
    return make_tuple(lexeme, "Invalid Token");
}

int main() {
    
    // filepath to code
    string baseFilePath, filepath, userChoice;
    
    cout << "Enter the file path of the folder with the test case files in it: ";
    getline(cin, baseFilePath);
    
    // This will only work for Macs since file paths for Windows and other operating systems are different
    baseFilePath += '/';
    cout << "Enter the file name(for supplied test cases enter \"1\", \"2\", or \"3\"): ";
    cin >> userChoice;
    
    
    //check to see if the user wants to test one of the predefined test cases.1
    if (userChoice == "1")
    {
        filepath = baseFilePath + "TestCase1.txt";
    }
    else if (userChoice == "2")
    {
        filepath = baseFilePath + "TestCase2.txt";
    }
    else if(userChoice == "3")
    {
        filepath = baseFilePath + "TestCase3.txt";
    }
    else
    {
        filepath = baseFilePath + userChoice;
    }
    
    // opening the input file
    ifstream inFile;
    inFile.open(filepath);
    if (!inFile)
    {
        cout <<"Error: Unable to open specified input file \"" << filepath << "\"" << endl;
        exit(0);
    }
    
    //opening the output file
    ofstream outfile;
    filepath =  baseFilePath + "ouput" + userChoice + ".txt";
    outfile.open(filepath);
    if (!outfile)
    {
        cout <<"Error: Unable to open specified output file \"" << filepath << "\"" << endl;
        exit(0);
    }
    
    
    outfile << left << setw(20) << "Token" <<setw(20) << "Lexeme" << endl;
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
        while (inFile)
        {
            // get the first character from file
            // c = ' '; // is this necessary? <==================================================
            inFile.get(c);
            
            // reads all the leading whitespace of the file to the first non-whitespace
            while (inFile && isspace(c))
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
                    if (!endComment) {
                        outfile << left << setw(20) << "Unknown" << setw(20) << "Unable to find end " \
                        "of comment" << endl;
                    }
                }
                else
                {
                    // only the '[' symbol was read and we have to putback the character we peeked at
                    inFile.putback(next);
                    outfile << left << setw(20) << "Invalid Token"<< setw(20) << "[" << endl;
                }
            }
            else if (c != '\n' && !isspace(c)){
                inFile.putback(c);
                tuple<string, string> token = lexer(inFile);
                outfile << left << setw(20) << get<1>(token) << setw(20) << get<0>(token) << endl;
            }
        }
        cout << endl << "Lexicon Analyzer Complete" << endl;
    }
    else
    {
        cerr << endl <<  "Unable to open specified file." << endl;
    }
    // closes file
    inFile.close();
    
    return 0;
}
