/*
     Jonathan Ishii
     Matthew Mikulka
     
     CPSC 323 - Section 1
 
     Assignment 2
 */

#ifndef LexicalAnalyzer_hpp
#define LexicalAnalyzer_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <tuple>
#include <string>

using namespace std;

//returns a col for the identifier DFSM
int char_to_col_identifier(char c);

//returns true if the string passed to it is an identifier
bool identifier_DFSM(const string &str);

// returns a col number for the integer/real DFSM
int number_to_col(char c);

// determines if the input is a integer or real
bool is_number_DFSM(const string &lexeme);

bool is_integer(const string &lexeme);

// Checks to see if the lexeme is a separator
bool isSeparator(const string &lexeme, string &nextLexeme, ifstream &inFile);

//checks to see if the lexeme is an operator
bool isOperator(const string &lexeme, string &nextLexeme, ifstream &inFile);

//checks to see if the identifier is a keyword
bool isKeyword(const string &lexeme);

tuple<bool, string> is_comment(char c, ifstream &inFile);

tuple<string, string> lexer(ifstream &inFile, ostream &outfile);

tuple<string, string> actualLexer(ifstream &infile);

int getLineNumber();

#endif /* LexicalAnalyzer_hpp */
