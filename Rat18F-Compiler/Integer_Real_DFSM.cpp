#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

// gets the column of the FSM based off of the input
int number_to_col(char c)
{
    if (isdigit(c))
        return 0;
    else if (c == '.')
        return 1;
    else
        return 2;
}

// determines if the input is a integer or real
int is_number_DFSM(string lexeme)
{
    const int STATES = 5, INPUT = 3;
    int dfsmTable [STATES][INPUT] = {
        {2, 3, 3},
        {2, 4, 3},
        {3, 3, 3},
        {5, 3, 3},
        {5, 3, 3}
    };
    int state = 1;
    int lexemeLength = int(lexeme.length());
    
    for(int i = 0; i < lexemeLength; ++i)
    {
        int col  = number_to_col(lexeme[i]);
        state = dfsmTable[state - 1][col];
    }
    
    if(state == 2 || state == 5)
    {
        return 1;
    }
    return 0;
}

// helper function to print out results of test cases
void number_result_print(string lexeme, int result)
{
    if(result == 1)
    {
        cout << setw(10) << left << lexeme << ": is an integer or real." << endl;
    }
    else
    {
        cout << setw(10) << left << lexeme << ": is NOT integer or real." << endl;
    }
}

// helper function of test cases
void integer_real_test_cases()
{
    // testing
    string lexeme = "123";
    int result = is_number_DFSM(lexeme);
    number_result_print(lexeme, result);
    
    lexeme = "123456789";
    result = is_number_DFSM(lexeme);
    number_result_print(lexeme, result);
    
    lexeme = "000000";
    result = is_number_DFSM(lexeme);
    number_result_print(lexeme, result);
    
    lexeme = "123.123";
    result = is_number_DFSM(lexeme);
    number_result_print(lexeme, result);
    
    lexeme = "0.123";
    result = is_number_DFSM(lexeme);
    number_result_print(lexeme, result);
    
    lexeme = "number";
    result = is_number_DFSM(lexeme);
    number_result_print(lexeme, result);
    
    lexeme = "123.";
    result = is_number_DFSM(lexeme);
    number_result_print(lexeme, result);
    
    lexeme = ".123";
    result = is_number_DFSM(lexeme);
    number_result_print(lexeme, result);
    
    lexeme = "123.num";
    result = is_number_DFSM(lexeme);
    number_result_print(lexeme, result);
    
    lexeme = "num.123";
    result = is_number_DFSM(lexeme);
    number_result_print(lexeme, result);
    
    lexeme = "num.num";
    result = is_number_DFSM(lexeme);
    number_result_print(lexeme, result);
    
    lexeme = ".";
    result = is_number_DFSM(lexeme);
    number_result_print(lexeme, result);
    
    lexeme = ".num";
    result = is_number_DFSM(lexeme);
    number_result_print(lexeme, result);
    
    lexeme = "num.";
    result = is_number_DFSM(lexeme);
    number_result_print(lexeme, result);
    
    lexeme = "123.123#";
    result = is_number_DFSM(lexeme);
    number_result_print(lexeme, result);
    
    lexeme = "123$123";
    result = is_number_DFSM(lexeme);
    number_result_print(lexeme, result);
    
    lexeme = "123five123";
    result = is_number_DFSM(lexeme);
    number_result_print(lexeme, result);
    
    lexeme = "#";
    result = is_number_DFSM(lexeme);
    number_result_print(lexeme, result);
}

//int main(int argc, const char * argv[]) {
//    
//    integer_real_test_cases();
//    
//    return 0;
//}
