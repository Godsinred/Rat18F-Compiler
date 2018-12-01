//
//  SymbolTable.hpp
//  Rat18F-Compiler
//
//  Created by Matthew Mikulka on 11/23/18.
//  Copyright © 2018 Jonathan Ishii. All rights reserved.
//

#ifndef SymbolTable_hpp
#define SymbolTable_hpp

#include <string>
#include <iostream>
#include <map>

#include "LexicalAnalyzer.h"

using namespace std;

void printTable(ostream &outfile);
void insertItem(string &type, string &lexeme);
bool inTable(string &lexeme);
int get_address(const string &lexeme);
string get_type(string &lexeme);

struct Symbol
{
    string lexeme;
    string type;
    int memoryLocation;
};

#endif /* SymbolTable_hpp */
