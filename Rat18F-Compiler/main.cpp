#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main(int argc, const char * argv[]) {
    
    // filepath to code
    string filepath = "/Users/godsinred/Desktop/Rat18F-Compiler/Rat18F-Compiler/example.txt";
    
    // opening the input file
    ifstream inFile;
    inFile.open(filepath);
    
    //opening the output file
    ofstream outfile;
    filepath = "/Users/godsinred/Desktop/Rat18F-Compiler/Rat18F-Compiler/ouput.txt";
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
        string lexeme;
        
        
        // checks to make sure that the file isn't all whitespace or first characters aren't all whitespaces
        if (!inFile.eof())
        {
            inFile.get(c);
        }
        // reads all the leading whitespace of the file to the first non-whitespace
        while (!inFile.eof() && isspace(c))
        {
            inFile.get(c);
        }
        // found the first non-whitespace character and puts it back to be read
        if (!inFile.eof())
        {
            inFile.putback(c);
        }
        
        //starts building lexemes
        while (!inFile.eof())
        {
            // builds a lexeme to be identified one char at a time
            inFile.get(c);
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
                    // only the ']' symbol was read and we have to putback the character we peeked at and
                    // add ']' to the string we are building
                    inFile.putback(next);
                    lexeme += c;
                }
            }
            // checking if it is not a whitespace
            else if (!isspace(c))
            {
                lexeme += c;
            }
            // whitespace condition
            else
            {
                string token = "no token yet";
                // token = lexer(lexeme);
                outfile << left << setw(20) << token << setw(20) << lexeme << endl;
                lexeme = "";
                
                // reads all the possible whitespace inbetween lexemes
                while (!inFile.eof() && isspace(c))
                {
                    inFile.get(c);
                }
                if (!inFile.eof())
                {
                    inFile.putback(c);
                }
            }
        }
    }
    
    // closes file
    inFile.close();
    
    return 0;
}
