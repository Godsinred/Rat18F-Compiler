/*
     Jonathan Ishii
     Matthew Mikulka
     
     CPSC 323 - Section 1
     
     Assignment 2
 */

#ifndef SyntaxAnalyzer_h
#define SyntaxAnalyzer_h

using namespace std;

void Rat18F(ifstream &infile, ostream &outfile);

void OptFunctionDefinitions(ifstream &infile, ostream &outfile, tuple<string, string> &token);

void FunctionDefinitions(ifstream &infile, ostream &outfile, tuple<string, string> &token);

void FunctionDefinitionsEnd(ifstream &infile, ostream &outfile, tuple<string, string> &token);

bool Function(ifstream &infile, ostream &outfile, tuple<string, string> &token);

bool Identifier(ostream &outfile, const tuple<string, string> &token);

bool OptParameterList(ifstream &infile, ostream &outfile, tuple<string, string> &token);

bool ParameterList(ifstream &infile, ostream &outfile, tuple<string, string> &token);

bool Parameter(ifstream &infile, ostream &outfile, tuple<string, string> &token);

void ParameterListEnd(ifstream &infile, ostream &outfile, tuple<string, string> &token);

bool IDs(ifstream &infile, ostream &outfile, tuple<string, string> &token);

void IDsEnd(ifstream &infile, ostream &outfile, tuple<string, string> &token);

bool Qualifier(ifstream &infile, ostream &outfile, tuple<string, string> &token);

void OptDeclarationList(ifstream &infile, ostream &outfile, tuple<string, string> &token);

void DeclarationList(ifstream &infile, ostream &outfile, tuple<string, string> &token);

bool Declaration(ifstream &infile, ostream &outfile, tuple<string, string> &token);

void DeclarationListEnd(ifstream &infile, ostream &outfile, tuple<string, string> &token);

void Body(ifstream &infile, ostream &outfile, tuple<string, string> &token);

bool StatementList(ifstream &infile, ostream &outfile, tuple<string, string> &token);

void StatementListEnd(ifstream &infile, ostream &outfile, tuple<string, string> &token);

bool Statement(ifstream &infile, ostream &outfile, tuple<string, string> &token);

bool Compound(ifstream &infile, ostream &outfile, tuple<string, string> &token);

bool Assign(ifstream &infile, ostream &outfile, tuple<string, string> &token);

bool If(ifstream &infile, ostream &outfile, tuple<string, string> &token);

bool Return(ifstream &infile, ostream &outfile, tuple<string, string> &token);

bool ReturnEnd(ifstream &infile, ostream &outfile, tuple<string, string> &token);

bool Print(ifstream &infile, ostream &outfile, tuple<string, string> &token);

bool Scan(ifstream &infile, ostream &outfile, tuple<string, string> &token);

bool While(ifstream &infile, ostream &outfile, tuple<string, string> &token);

void Condition(ifstream &infile, ostream &outfile, tuple<string, string> &token);

void IfEnd(ifstream &infile, ostream &outfile, tuple<string, string> &token);

void Relop(ifstream &infile, ostream &outfile, tuple<string, string> &token);

void Expression(ifstream &infile, ostream &outfile, tuple<string, string> &token);

void Term(ifstream &infile, ostream &outfile, tuple<string, string> &token);

void Factor(ifstream &infile, ostream &outfile, tuple<string, string> &token);

bool Primary(ifstream &infile, ostream &outfile, tuple<string, string> &token);

void PrimaryEnd(ifstream &infile, ostream &outfile, tuple<string, string> &token);

bool TermPrime(ifstream &infile, ostream &outfile, tuple<string, string> &token);

bool ExpressionPrime(ifstream &infile, ostream &outfile, tuple<string, string> &token);

void errorReporting(ostream &outfile, string expected, string received);

#endif /* SyntaxAnalyzer_h */
