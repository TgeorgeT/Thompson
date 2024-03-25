#include <iostream>
#include <string>
#include "convert.h"
#include "lambda_nfa.h"
#include "fstream"

std::ifstream in("input.txt");
std::ofstream out("transitions.txt");

int main()
{
    std::string regex;
    in >> regex;
    regex = convert_to_prefix_form(regex);

    std::cout << regex << std::endl;
    lambda_nfa *nfa = convert_postf_to_lambda_nfa(regex);
    nfa->assign_index();
    std::vector<std::vector<std::pair<char, int>>>
        transitions = nfa->get_transitions();

    for (int i = 0; i < transitions.size(); i++)
    {
        out << i << ": ";
        for (int j = 0; j < transitions[i].size(); j++)
        {
            out << "(" << transitions[i][j].first << "," << transitions[i][j].second << ") ";
        }
        out << std::endl;
    }
    system("./venv/bin/python print_nfa.py");
}