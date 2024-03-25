#include <iostream>
#include <deque>
#include <string>
#include "utils.h"

inline bool is_left_asoc(char c)
{
    return c == '.' || c == '|';
}

inline int get_prec(char c)
{
    if (c == '(' || c == ')')
        return 4;
    if (c == '*')
        return 3;
    if (c == '.')
        return 2;
    return 1;
}

inline bool is_popable(char op1, wchar_t op2)
{
    return op2 != '(' && (get_prec(op1) < get_prec(op2) || (get_prec(op1) == get_prec(op2) && is_left_asoc(op1)));
}

// deal with lambda

std::string convert_to_prefix_form(std::string regex)
{
    int len = regex.length();
    int cnt = 0;
    for (int i = 0; i < len; ++i)
    {
        if (regex[i] == '(' || regex[i] == ')')
            ++cnt;
    }

    std::string output(len - cnt, '\0');
    int output_pos = 0;

    std::deque<char> operator_stack;

    for (int i = 0; i < len; ++i)
    {
        if (is_alphanum(regex[i]))
        {
            output[output_pos++] = regex[i];
            continue;
        }
        // is operator
        if (regex[i] == '(')
        {
            operator_stack.push_back(regex[i]);
            continue;
        }
        if (regex[i] == ')')
        {
            while (!operator_stack.empty() && operator_stack.back() != '(')
            {
                output[output_pos++] = operator_stack.back();
                operator_stack.pop_back();
            }
            if (operator_stack.empty())
            {
                throw std::runtime_error("Unmatched parenthesis");
            }
            operator_stack.pop_back();
            continue;
        }
        while (!operator_stack.empty() && is_popable(regex[i], operator_stack.back()))
        {
            output[output_pos++] = operator_stack.back();
            operator_stack.pop_back();
        }
        operator_stack.push_back(regex[i]);
    }
    while (!operator_stack.empty())
    {
        output[output_pos++] = operator_stack.back();
        operator_stack.pop_back();
    }

    return output;
}