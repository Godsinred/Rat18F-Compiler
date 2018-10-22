#include <iostream>
#include "LexicalAnalyzer.h"
#include <string>
#include <fstream>
#include <iomanip>
#include <tuple>
#include "SyntaxAnalyzer.h"

using namespace std;

void Rat18F(bool printSwitch, ifstream &infile)
{
    if (printSwitch)
    {
        cout << "R1. <Rat18F>  ::=   <Opt Function Definitions>   $$  <Opt Declaration List>  <Statement List>  $$" << endl;
    }
    tuple<string, string> token = lexer(infile);
    cout << get<1>(token) << endl;
    OptFunctionDefinitions(printSwitch, infile, token);
//    $$
//    OptDeclarationList();
//    StatementList();
//    $$
    cout << "SA is correct.\n";
}

void OptFunctionDefinitions(bool printSwitch, ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R2. <Opt Function Definitions> ::= <Function Definitions>     |  <Empty>" << endl;
    }
    FunctionDefinitions(printSwitch, infile, token);
}

void FunctionDefinitions(bool printSwitch, ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R3. <Function Definitions>  ::= <Function> <Function Definitions End>" << endl;
    }
    Function(printSwitch, infile, token);
    //FunctionDefinitionsEnd(); <==========================================================================================
}

void Function(bool printSwitch, ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R5. <Function> ::= function  <Identifier>   ( <Opt Parameter List> )  <Opt Declaration List>  <Body>" << endl;
    }
    
    if(get<1>(token) == "function")
    {
        token = lexer(infile);
        cout << get<1>(token) << endl;
        if(!Identifier(printSwitch, token))
        {
            cout << "Expected: Identifier\nReceived: " << get<1>(token) << endl;
            exit(1);
        }
        
        token = lexer(infile);
        cout << get<1>(token) << endl;
        if(get<1>(token) != "(")
        {
            cout << "Expected: (\nReceived: " << get<1>(token) << endl;
            exit(1);
        }
        
        token = lexer(infile);
        cout << get<1>(token) << endl;
        OptParameterList(printSwitch, infile, token);
        
        cout << get<1>(token) << endl;
        if(get<1>(token) != ")")
        {
            cout << "Expected: )\nReceived: " << get<1>(token) << endl;
            exit(1);
        }
        // <Opt Declaration List><==========================================================================================
        // <Body><==========================================================================================
    }
}

bool Identifier(bool printSwitch, const tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "<Identifier>" << endl;
    }
    
    if(get<0>(token) != "Identifier")
    {
        return false;
    }
    return true;
}

void OptParameterList(bool printSwitch, ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R6. <Opt Parameter List> ::=  <Parameter List>    |     <Empty>" << endl;
    }
    ParameterList(printSwitch, infile, token);
}

void ParameterList(bool printSwitch, ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R7. <Parameter List>  ::=  <Parameter>  <Parameter List End>" << endl;
    }
    Parameter(printSwitch, infile, token);
    ParameterListEnd(printSwitch, infile, token);
}

void Parameter(bool printSwitch, ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R9. <Parameter> ::=  <IDs > : <Qualifier>" << endl;
    }
    if(IDs(printSwitch, infile, token))
    {
        if(get<1>(token) != ":")
        {
            cout << "Expected: :\nReceived: " << get<1>(token) << endl;
            exit(1);
        }
        Qualifier(printSwitch, infile, token);
    }
    
}

void ParameterListEnd(bool printSwitch, ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R8. <Parameter List End> ::= , <Parameter List> | ε" << endl;
    }
    token = lexer(infile);
    cout << get<1>(token) << endl;
    if(get<1>(token) == ",")
    {
        ParameterList(printSwitch, infile, token);
    }
    
}

bool IDs(bool printSwitch, ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R16. <IDs> ::=     <Identifier>  <IDs End>" << endl;
    }
    if(Identifier(printSwitch, token))
    {
        IDsEnd(printSwitch, infile, token);
        return true;
    }
    return false;
}

void IDsEnd(bool printSwitch, ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R17. <IDs End> ::= , <IDs> | ε" << endl;
    }
    token = lexer(infile);
    cout << get<1>(token) << endl;
    if(get<1>(token) == ",")
    {
        token = lexer(infile);
        cout << get<1>(token) << endl;
        if(!IDs(printSwitch, infile, token))
        {
            cout << "Expected: Identifier\nReceived: " << get<1>(token) << endl;
            exit(1);
        }
    }
}

void Qualifier(bool printSwitch, ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R10. <Qualifier> ::= int     |    boolean    |  real" << endl;
    }
    token = lexer(infile);
    cout << get<1>(token) << endl;
    if(get<1>(token) != "int" && get<1>(token) != "boolean" && get<1>(token) != "real")
    {
        cout << "Expected: int or boolean or real\nReceived: " << get<1>(token) << endl;
        exit(1);
    }
}

//R4.<Function Definitions End> ::= <Function Definitions>  | ε
//
//
//
//
//R11. <Body>  ::= {  < Statement List>  }
//R12. <Opt Declaration List> ::= <Declaration List>   |    <Empty>
//R13. <Declaration List>  ::= <Declaration> ;   <Declaration List End>
//R14. <Declaration List End> ::= <Declaration List> | ε
//R15. <Declaration> ::=   <Qualifier > <IDs>
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
