#include <iostream>
#include "LexicalAnalyzer.h"
#include <string>
#include <fstream>
#include <iomanip>
#include <tuple>
#include "SyntaxAnalyzer.h"

using namespace std;

void Rat18F(bool printSwitch)
{
    if (printSwitch)
    {
        cout << "<Rat18F>  ::=   <Opt Function Definitions>   $$  <Opt Declaration List>  <Statement List>  $$" << endl;
    }
    string filepath = "/Users/godsinred/Desktop/Rat18F-Compiler/Rat18F-Compiler/TestCase3.txt";
    ifstream inFile;
    inFile.open(filepath);
    if (!inFile)
    {
        cout <<"Error: Unable to open specified input file \"" << filepath << "\"" << endl;
        exit(0);
    }
    tuple<string, string> token = lexer(inFile);
    if(get<0>(token) != "")
    {
        cout << left << setw(20) << get<1>(token) << setw(20) << get<0>(token) << endl;
    }
//    OptFunctionDefinitions();
//    $$
//    OptDeclarationList();
//    OptDeclarationList();
//    $$
}
//
//R2. <Opt Function Definitions> ::= <Function Definitions>     |  <Empty>
//R3. <Function Definitions>  ::= <Function> <Function Definitions End>
//R4.<Function Definitions End> ::= <Function Definitions>  | ε
//R5. <Function> ::= function  <Identifier>   ( <Opt Parameter List> )  <Opt Declaration List>  <Body>
//R6. <Opt Parameter List> ::=  <Parameter List>    |     <Empty>
//R7. <Parameter List>  ::=  <Parameter>  <Parameter List End>
//R8. <Parameter List End> ::= , <Parameter List> | ε
//R9. <Parameter> ::=  <IDs > : <Qualifier>
//R10. <Qualifier> ::= int     |    boolean    |  real
//R11. <Body>  ::= {  < Statement List>  }
//R12. <Opt Declaration List> ::= <Declaration List>   |    <Empty>
//R13. <Declaration List>  ::= <Declaration> ;   <Declaration List End>
//R14. <Declaration List End> ::= <Declaration List> | ε
//R15. <Declaration> ::=   <Qualifier > <IDs>
//R16. <IDs> ::=     <Identifier>  <IDs End>
//R17. <IDs End> ::= , <IDs> | ε
//R18. <Statement List> ::=   <Statement>  <Statement List End>
//R19. <Statement List End> ::= <Statement List> | ε
//R20. <Statement> ::=   <Compound>  |  <Assign> |   <If>  |  <Return>   | <Print>   |   <Scan>   |  <While>
//R21. <Compound> ::=   { <Statement List>  }
//R22. <Assign> ::=     <Identifier> = <Expression> ;
//R23. <If> ::=     if  ( <Condition>  ) <Statement>   <if End>
//R24> <if End> ::= ifend | else <Statement> ifend
//R25. <Return> ::=  return <Return End>
//R26. <Return End> ::= ; |  <Expression> ;
//R27. <Print> ::=    put ( <Expression>);
//R28. <Scan> ::=    get ( <IDs> );
//R29. <While> ::=  while ( <Condition>  )  <Statement> whileend
//R30. <Condition> ::=     <Expression>  <Relop>   <Expression>
//R31. <Relop> ::=        ==   |   ^=    |   >     |   <    |   =>    |   =<
//R32. <Expression>  ::=    <Term> <Expression’>
//R33. <Expression’> ::= + <Term> <Expression’>   |  - <Term>  <Expression’>   | ε
//R34. <Term>    ::=    <Factor>  <Term’>
//R35.<Term’> ::= * <Factor> <Term’>  | / <Factor> <Term’> | ε
//R36. <Factor> ::=      -  <Primary>    |    <Primary>
//R37. <Primary> ::=     <Identifier> <Primary End>   |  <Integer> |   ( <Expression> )   |
//<Real>  |   true   |  false
//R38. <Primary End> ::= ( <IDs> ) | ε
//R39. <Empty>   ::= ε
