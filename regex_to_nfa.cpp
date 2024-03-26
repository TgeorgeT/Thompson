#include "lambda_nfa.h"
#include "convert.h"
#include <string.h>
#include <deque>
#include "utils.h"
#include <iostream>

lambda_nfa *convert_postf_to_lambda_nfa(std::string regex)
{
    std::deque<lambda_nfa *> nfa_stack;

    for (char c : regex)
    {
        if (is_alphanum(c))
        {
            nfa_stack.push_back(new lambda_nfa(c));
            continue;
        }
        if (c == '*')
        {
            lambda_nfa *top = nfa_stack.back();
            top->kleene();
            continue;
        }
        if (c == '.')
        {
            lambda_nfa *first = nfa_stack.back();
            nfa_stack.pop_back();
            lambda_nfa *second = nfa_stack.back();
            nfa_stack.pop_back();
            second->concatenation(first);
            nfa_stack.push_back(second);
            delete first;
            continue;
        }
        // c == '|'
        lambda_nfa *first = nfa_stack.back();
        nfa_stack.pop_back();
        lambda_nfa *second = nfa_stack.back();
        nfa_stack.pop_back();
        first->reunion(second);
        delete second;
        nfa_stack.push_back(first);
    }
    return nfa_stack.back();
}