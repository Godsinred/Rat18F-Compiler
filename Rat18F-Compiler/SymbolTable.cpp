//
//  SymbolTable.cpp
//  Rat18F-Compiler
//
//  Created by Matthew Mikulka on 11/23/18.
//  Copyright © 2018 Jonathan Ishii. All rights reserved.
//

#include "SymbolTable.h"

map <string, Symbol> symbolTable;

int memoryAddr = 5000;

void printTable(ostream &outfile)
{
    auto ittr = symbolTable.begin();
    auto ittrEnd = symbolTable.end();
    outfile << endl << endl;
    outfile << left << setw(20) << "identifier" << setw(20) << "Memory Location" << setw(20) << "Type" << endl;
    for (int i = 0; i < 60; i++) outfile << "-";
    outfile << endl << endl;
    while (ittr != ittrEnd)
    {
        outfile << left << setw(20) << ittr->first << setw(20) << ittr->second.memoryLocation
        << setw(20) << ittr->second.type << endl;
        ittr++;
    }
}

void insertItem(string &type, string &lexeme)
{
    if (inTable(lexeme))
    {
        cerr << "Error line number: " << getLineNumber() << endl;
        cerr << lexeme << " has been defined before.";
        exit(0);
    }
    Symbol current = {lexeme, type, memoryAddr};
    symbolTable[lexeme] = current;
    memoryAddr++;
}

bool inTable(string &lexeme)
{
    return symbolTable.find(lexeme) != symbolTable.end();
}

int get_address(const string &lexeme)
{
    return symbolTable[lexeme].memoryLocation;
}

string get_type(string &lexeme)
{
    return symbolTable.find(lexeme)->second.type;
}
