/*
     Jonathan Ishii
     Matthew Mikulka
     
     CPSC 323 - Section 1
     
     Assignment 2
 */

#ifndef SyntaxAnalyzer_h
#define SyntaxAnalyzer_h

using namespace std;

void Rat18F(ifstream &infile);

void OptFunctionDefinitions(ifstream &infile, tuple<string, string> &token);

void FunctionDefinitions(ifstream &infile, tuple<string, string> &token);

void FunctionDefinitionsEnd(ifstream &infile, tuple<string, string> &token);

bool Function(ifstream &infile, tuple<string, string> &token);

bool Identifier(const tuple<string, string> &token);

bool OptParameterList(ifstream &infile, tuple<string, string> &token);

bool ParameterList(ifstream &infile, tuple<string, string> &token);

bool Parameter(ifstream &infile, tuple<string, string> &token);

void ParameterListEnd(ifstream &infile, tuple<string, string> &token);

bool IDs(ifstream &infile, tuple<string, string> &token);

void IDsEnd(ifstream &infile, tuple<string, string> &token);

bool Qualifier(ifstream &infile, tuple<string, string> &token);

void OptDeclarationList(ifstream &infile, tuple<string, string> &token);

void DeclarationList(ifstream &infile, tuple<string, string> &token);

bool Declaration(ifstream &infile, tuple<string, string> &token);

void DeclarationListEnd(ifstream &infile, tuple<string, string> &token);

void Body(ifstream &infile, tuple<string, string> &token);

bool StatementList(ifstream &infile, tuple<string, string> &token);

void StatementListEnd(ifstream &infile, tuple<string, string> &token);

bool Statement(ifstream &infile, tuple<string, string> &token);

bool Compound(ifstream &infile, tuple<string, string> &token);

bool Assign(ifstream &infile, tuple<string, string> &token);

void Expression(ifstream &infile, tuple<string, string> &token);

void Term(ifstream &infile, tuple<string, string> &token);

void Factor(ifstream &infile, tuple<string, string> &token);

bool Primary(ifstream &infile, tuple<string, string> &token);

void PrimaryEnd(ifstream &infile, tuple<string, string> &token);

bool TermPrime(ifstream &infile, tuple<string, string> &token);

bool ExpressionPrime(ifstream &infile, tuple<string, string> &token);

#endif /* SyntaxAnalyzer_h */
