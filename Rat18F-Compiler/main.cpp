/*
    Jonathan Ishii
    Matthew Mikulka
 
    CPSC 323 - Section 1
 
    Assignment 2
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <tuple>
#include <string>
#include "SyntaxAnalyzer.h"
#include "LexicalAnalyzer.h"

using namespace std;

int main()
{
    
    // filepath to code
    string baseFilePath, filepath, userChoice;

    cout << "Enter the file path of the folder with the test case files in it: ";
    getline(cin, baseFilePath);

    // This will only work for Macs since file paths for Windows and other operating systems are different
    baseFilePath += '/';
    cout << "Enter the file name(for supplied test cases enter \"1\", \"2\", or \"3\"): ";
    cin >> userChoice;

    //check to see if the user wants to test one of the predefined test cases.
    if (userChoice == "1")
    {
        filepath = baseFilePath + "TestCase1.txt";
        userChoice = "TestCase1.txt";
    }
    else if (userChoice == "2")
    {
        filepath = baseFilePath + "TestCase2.txt";
        userChoice = "TestCase2.txt";
    }
    else if(userChoice == "3")
    {
        filepath = baseFilePath + "TestCase3.txt";
        userChoice = "TestCase3.txt";
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
    filepath =  baseFilePath + "output_" + userChoice;
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
        // controls all the functions if they should print their grammar
        bool printSwitch = true;
        
        //starts building lexemes
        while (inFile)
        {
            // uncomment this for LA testing
            /*
            tuple<string, string> token = lexer(inFile);
            if(get<0>(token) != "")
            {
                // token / lexeme
                outfile << left << setw(20) << get<0>(token) << setw(20) << get<1>(token) << endl;
            }
            */
            Rat18F(printSwitch, inFile);
        }
        cout << endl << "Lexicon Analyzer Complete" << endl;
    }
    else
    {
        cerr << endl <<  "Unable to open specified file." << endl;
    }
    
    // closes files
    inFile.close();
    outfile.close();

    return 0;
}
