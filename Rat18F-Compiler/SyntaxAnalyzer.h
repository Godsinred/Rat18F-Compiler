#ifndef SyntaxAnalyzer_h
#define SyntaxAnalyzer_h

using namespace std;

void Rat18F(bool printSwitch, ifstream &infile);

void OptFunctionDefinitions(bool printSwitch, ifstream &infile, tuple<string, string> &token);

void FunctionDefinitions(bool printSwitch, ifstream &infile, tuple<string, string> &token);

void Function(bool printSwitch, ifstream &infile, tuple<string, string> &token);

void Identifier(bool printSwitch, const tuple<string, string> &token);

void OptParameterList(bool printSwitch, ifstream &infile, tuple<string, string> &token);




#endif /* SyntaxAnalyzer_h */
