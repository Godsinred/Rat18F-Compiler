#ifndef SyntaxAnalyzer_h
#define SyntaxAnalyzer_h

using namespace std;

void Rat18F(ifstream &infile);

void OptFunctionDefinitions(ifstream &infile, tuple<string, string> &token);

void FunctionDefinitions(ifstream &infile, tuple<string, string> &token);

void Function(ifstream &infile, tuple<string, string> &token);

bool Identifier(const tuple<string, string> &token);

void OptParameterList(ifstream &infile, tuple<string, string> &token);

void ParameterList(ifstream &infile, tuple<string, string> &token);

bool Parameter(ifstream &infile, tuple<string, string> &token);

void ParameterListEnd(ifstream &infile, tuple<string, string> &token);

bool IDs(ifstream &infile, tuple<string, string> &token);

void IDsEnd(ifstream &infile, tuple<string, string> &token);

void Qualifier(ifstream &infile, tuple<string, string> &token);

#endif /* SyntaxAnalyzer_h */
