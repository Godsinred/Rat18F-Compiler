/*
     Jonathan Ishii
     Matthew Mikulka
     
     CPSC 323 - Section 1
     
     Assignment 2
 */

#include <iostream>
#include "LexicalAnalyzer.h"
#include <string>
#include <fstream>
#include <iomanip>
#include <tuple>
#include "SyntaxAnalyzer.h"

using namespace std;

bool printSwitch = true;

void Rat18F(ifstream &infile)
{
    cout << endl;
    tuple<string, string> token = lexer(infile);
    if (printSwitch)
    {
        cout << "R1. <Rat18F>  ::=   <Opt Function Definitions>   $$  <Opt Declaration List>  <Statement List>  $$" << endl;
    }
    
    OptFunctionDefinitions(infile, token);
    
    
    if(get<1>(token) != "$$")
    {
        cout << "\nERROR: NOT VALID SYNTAX.\n";
        cout << "Expected: $$\nReceived: " << get<1>(token) << endl;
        exit(1);
    }

//    OptDeclarationList(); ==========================================================================================
//    StatementList(); =========================================================================================================

    token = lexer(infile);
    if(get<1>(token) != "$$")
    {
        cout << "\nERROR: NOT VALID SYNTAX.\n";
        cout << "Expected: $$\nReceived: " << get<1>(token) << endl;
        exit(1);
    }
    
    cout << "\nSA is correct.\n";
}

void OptFunctionDefinitions(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R2. <Opt Function Definitions> ::= <Function Definitions>     |  <Empty>" << endl;
    }
    FunctionDefinitions(infile, token);
}

void FunctionDefinitions(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R3. <Function Definitions>  ::= <Function> <Function Definitions End>" << endl;
    }
    if(Function(infile, token))
    {
        token = lexer(infile);
        FunctionDefinitionsEnd(infile, token);
    }
}

void FunctionDefinitionsEnd(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R4.<Function Definitions End> ::= <Function Definitions>  | ε" << endl;
    }
    FunctionDefinitions(infile, token);
}

bool Function(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R5. <Function> ::= function  <Identifier>   ( <Opt Parameter List> )  <Opt Declaration List>  <Body>" << endl;
    }
    
    if(get<1>(token) == "function")
    {
        token = lexer(infile);
        if(!Identifier(token))
        {
            cout << "\nERROR: NOT VALID SYNTAX.\n";
            cout << "Expected: Identifier\nReceived: " << get<1>(token) << endl;
            exit(1);
        }
        
        token = lexer(infile);
        if(get<1>(token) != "(")
        {
            cout << "\nERROR: NOT VALID SYNTAX.\n";
            cout << "Expected: (\nReceived: " << get<1>(token) << endl;
            exit(1);
        }
        
        OptParameterList(infile, token);
        
        if(get<1>(token) != ")")
        {
            cout << "\nERROR: NOT VALID SYNTAX.\n";
            cout << "Expected: )\nReceived: " << get<1>(token) << endl;
            exit(1);
        }
        
        OptDeclarationList(infile, token);
        
        Body(infile, token);
        
        return true;
    }
    return false;
}

bool Identifier(const tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R Checker. <Identifier>" << endl;
    }
    
    if(get<0>(token) != "Identifier")
    {
        return false;
    }
    return true;
}

bool OptParameterList(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R6. <Opt Parameter List> ::=  <Parameter List>    |     <Empty>" << endl;
    }
    if(ParameterList(infile, token))
    {
        return true;
    }
    return false;
}

bool ParameterList(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R7. <Parameter List>  ::=  <Parameter>  <Parameter List End>" << endl;
    }
    if(Parameter(infile, token))
    {
        ParameterListEnd(infile, token);
        return true;
    }
    return false;
}

bool Parameter(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R9. <Parameter> ::=  <IDs > : <Qualifier>" << endl;
    }
    token = lexer(infile);
    if(IDs(infile, token))
    {
        if(get<1>(token) != ":")
        {
            cout << "\nERROR: NOT VALID SYNTAX.\n";
            cout << "Expected: :\nReceived: " << get<1>(token) << endl;
            exit(1);
        }
        if(!Qualifier(infile, token))
        {
            cout << "\nERROR: NOT VALID SYNTAX.\n";
            cout << "Expected: int or boolean or real\nReceived: " << get<1>(token) << endl;
            exit(1);
        }
        return true;
    }
    return false;
}

void ParameterListEnd(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R8. <Parameter List End> ::= , <Parameter List> | ε" << endl;
    }
    token = lexer(infile);
    if(get<1>(token) == ",")
    {
        if(!ParameterList(infile, token))
        {
            cout << "\nERROR: NOT VALID SYNTAX.\n";
            cout << "Expected: <ParameterList> i.e. <Identifier> \nReceived: " << get<1>(token) << endl;
            exit(1);
        }
    }
}

bool IDs(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R16. <IDs> ::=     <Identifier>  <IDs End>" << endl;
    }
    if(Identifier(token))
    {
        IDsEnd(infile, token);
        return true;
    }
    return false;
}

void IDsEnd(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R17. <IDs End> ::= , <IDs> | ε" << endl;
    }
    token = lexer(infile);
    if(get<1>(token) == ",")
    {
        token = lexer(infile);
        if(!IDs(infile, token))
        {
            cout << "\nERROR: NOT VALID SYNTAX.\n";
            cout << "Expected: Identifier\nReceived: " << get<1>(token) << endl;
            exit(1);
        }
    }
}

bool Qualifier(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R10. <Qualifier> ::= int     |    boolean    |  real" << endl;
    }
    token = lexer(infile);
    if(get<1>(token) != "int" && get<1>(token) != "boolean" && get<1>(token) != "real")
    {
        return false;
    }
    return true;
}

void OptDeclarationList(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R12. <Opt Declaration List> ::= <Declaration List>   |    <Empty>" << endl;
    }
    
    DeclarationList(infile, token);
}

void DeclarationList(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R13. <Declaration List>  ::= <Declaration> ;   <Declaration List End>" << endl;
    }
    
    if(Declaration(infile, token))
    {
        if(get<1>(token) != ";")
        {
            cout << "\nERROR: NOT VALID SYNTAX.\n";
            cout << "Expected: ;\nReceived: " << get<1>(token) << endl;
            exit(1);
        }
        DeclarationListEnd(infile, token);
    }
}

bool Declaration(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R15. <Declaration> ::=   <Qualifier > <IDs>" << endl;
    }
    
    if(Qualifier(infile, token))
    {
        if(!IDs(infile, token))
        {
            cout << "\nERROR: NOT VALID SYNTAX.\n";
            cout << "Expected: <IDs>/Identifier\nReceived: " << get<1>(token) << endl;
            exit(1);
        }
        return true;
    }
    return false;
}

void DeclarationListEnd(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R14. <Declaration List End> ::= <Declaration List> | ε" << endl;
    }
    DeclarationList(infile, token);
}

void Body(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R11. <Body>  ::= {  < Statement List>  }" << endl;
    }
    
    if(get<1>(token) != "{")
    {
        cout << "\nERROR: NOT VALID SYNTAX.\n";
        cout << "Expected: {\nReceived: " << get<1>(token) << endl;
        exit(1);
    }
    
    if(!StatementList(infile, token))
    {
        cout << "\nERROR: NOT VALID SYNTAX.\n";
        cout << "Expected: <Statement List>\nReceived: " << get<1>(token) << endl;
        exit(1);
    }
    
    if(get<1>(token) != "}")
    {
        cout << "\nERROR: NOT VALID SYNTAX.\n";
        cout << "Expected: }\nReceived: " << get<1>(token) << endl;
        exit(1);
    }
}

bool StatementList(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R18. <Statement List> ::=   <Statement>  <Statement List End>" << endl;
    }
    if(Statement(infile, token))
    {
        StatementListEnd(infile, token);
        return true;
    }
    return false;
}

void StatementListEnd(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R19. <Statement List End> ::= <Statement List> | ε" << endl;
    }
    StatementList(infile, token);
}

bool Statement(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R20. <Statement> ::=   <Compound>  |  <Assign> |   <If>  |  <Return>   | <Print>   |   <Scan>   |  <While>" << endl;
    }

    token = lexer(infile);
    if(Compound(infile, token)) // THIS DOES NOT WORK!!!!!!!!!!!!!!!!!!!!! <<<<<=======================================
    {
        return true;
    }
    else if (Assign(infile, token))
    {
        return true;
    }
    
    // <If> ============================================================================
    // <Return> ============================================================================
    // <Scan> ============================================================================
    // <While> ============================================================================
    
    return false;
}

bool Compound(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R21. <Compound> ::=   { <Statement List>  }" << endl;
    }
    
    if(get<1>(token) == "{")
    {
        if(!StatementList(infile, token))
        {
            cout << "\nERROR: NOT VALID SYNTAX.\n";
            cout << "Expected: <Statement List>\nReceived: " << get<1>(token) << endl;
            exit(1);
        }
        
        token = lexer(infile);
        if(get<1>(token) != "}")
        {
            cout << "\nERROR: NOT VALID SYNTAX.\n";
            cout << "Expected: }\nReceived: " << get<1>(token) << endl;
            exit(1);
        }
        return true;
    }
    return false;
}

bool Assign(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R22. <Assign> ::=     <Identifier> = <Expression> ;" << endl;
    }
    
    if(Identifier(token))
    {
        token = lexer(infile);
        if(get<1>(token) != "=")
        {
            cout << "\nERROR: NOT VALID SYNTAX.\n";
            cout << "Expected: }\nReceived: " << get<1>(token) << endl;
            exit(1);
        }
    
        Expression(infile, token);
        
        
        if(get<1>(token) != ";")
        {
            cout << "\nERROR: NOT VALID SYNTAX.\n";
            cout << "Expected: ;\nReceived: " << get<1>(token) << endl;
            exit(1);
        }
        return true;
    }
    return false;
}

void Expression(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R32. <Expression>  ::=    <Term> <Expression’>" << endl;
    }
    
    Term(infile, token);
    ExpressionPrime(infile, token);
}

void Term(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R34. <Term>    ::=    <Factor>  <Term’>" << endl;
    }
    Factor(infile, token);
    TermPrime(infile, token);
}

void Factor(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R36. <Factor> ::=      -  <Primary>    |    <Primary>" << endl;
    }
    token = lexer(infile);
    if (get<1>(token) == "-")
    {
        token = lexer(infile);
        Primary(infile, token);
    }
    else
    {
        Primary(infile, token);
    }
    
}
        
bool Primary(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R37. <Primary> ::=     <Identifier> <Primary End>   |  <Integer> |   ( <Expression> )   |   <Real>  |   true   |  false" << endl;
    }
    
    if (Identifier(token))
    {
        PrimaryEnd(infile, token);
        return true;
    }
    else if(get<0>(token) == "Integer")
    {
        cout << "R. <Integer>\n";
        return true;
    }
    else if (get<1>(token) == "(")
    {
        cout << "(" << endl;
        
        Expression(infile, token);
        
        if (get<1>(token) != ")")
        {
            cout << "\nERROR: NOT VALID SYNTAX.\n";
            cout << "Expected: )\nReceived: " << get<1>(token) << endl;
            exit(1);
        }
        return true;
    }
    else if (get<0>(token) == "Real")
    {
        cout << "R. <Real>\n";
        return true;
    }
    else if (get<0>(token) == "Keyword")
    {
        string temp;
        int length = get<1>(token).length();
        for(int i = 0; i < length; ++i)
        {
            temp += tolower(get<1>(token)[i]);
        }
        if (temp == "true")
        {
            cout << "R. true\n";
        }
        else if (temp == "false")
        {
            cout << "R. false\n";
        }
        return true;
    }
    cout << "\nERROR: NOT VALID SYNTAX.\n";
    cout << "Expected: <Primary>\nReceived: " << get<1>(token) << endl;
    exit(1);
    return false;
}

void PrimaryEnd(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R38. <Primary End> ::= ( <IDs> ) | ε" << endl;
    }
    token = lexer(infile);
    if (get<1>(token) == "(")
    {
        if(!IDs(infile, token))
        {
            cout << "\nERROR: NOT VALID SYNTAX.\n";
            cout << "Expected: (\nReceived: " << get<1>(token) << endl;
            exit(1);
        }
        if (get<1>(token) != ")")
        {
            cout << "\nERROR: NOT VALID SYNTAX.\n";
            cout << "Expected: )\nReceived: " << get<1>(token) << endl;
            exit(1);
        }
    }
}

bool TermPrime(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R35.<Term’> ::= * <Factor> <Term’>  | / <Factor> <Term’> | ε" << endl;
    }
    
    token = lexer(infile);
    if (get<1>(token) == "*")
    {
        Factor(infile, token);
        TermPrime(infile, token);
        return true;
    }
    else if (get<1>(token) == "/")
    {
        Factor(infile, token);
        TermPrime(infile, token);
        return true;
    }
    return false;
}

bool ExpressionPrime(ifstream &infile, tuple<string, string> &token)
{
    if (printSwitch)
    {
        cout << "R33. <Expression’> ::= + <Term> <Expression’>   |  - <Term>  <Expression’>   | ε" << endl;
    }

    if (get<1>(token) == "+")
    {
        Term(infile, token);
        ExpressionPrime(infile, token);
        return true;
    }
    else if (get<1>(token) == "-")
    {
        Term(infile, token);
        ExpressionPrime(infile, token);
        return true;
    }
    return false;
}


//
//
//
//
//R23. <If> ::=     if  ( <Condition>  ) <Statement>   <if End>
//R24> <if End> ::= ifend | else <Statement> ifend
//R25. <Return> ::=  return <Return End>
//R26. <Return End> ::= ; |  <Expression> ;
//R27. <Print> ::=    put ( <Expression>);
//R28. <Scan> ::=    get ( <IDs> );
//R29. <While> ::=  while ( <Condition>  )  <Statement> whileend
//R30. <Condition> ::=     <Expression>  <Relop>   <Expression>
//R31. <Relop> ::=        ==   |   ^=    |   >     |   <    |   =>    |   =<
//
//
//
//
//
//
//
//R39. <Empty>   ::= ε
