#include <string>
#include <iostream>

using namespace std;
const int INPUTS = 2, STATES = 4;

int char_to_col(char c)
{
    if (c >= 'a' && c <= 'z')
        return 1;
    if (c >= 'a' && c <= 'Z')
        return 1;
    if (c >= '0' && c <= '9')
        return 0;
    return 2;
}

int identifier_DFSM(string str)
{
    int dfsmTable [INPUTS][STATES] = {{0, 3, 3, 3},{2, 4, 4, 4}};
    int state = 1;
    int strLength = int(str.length());
    for (int i = 0; i < strLength; ++i)
    {
        int col  = char_to_col(str[i]);
        state = dfsmTable[col][state];
    }
    if (state == 2 || state == 4) return 1;
    return 0;
}
