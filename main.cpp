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
    bool is_postfix;
    in >> regex >> is_postfix;
    if (!is_postfix)
        regex = convert_to_prefix_form(regex);

    std::cout << regex << std::endl;
    lambda_nfa *nfa = convert_postf_to_lambda_nfa(regex);
    nfa->assign_index();
    std::vector<std::vector<std::pair<char, int>>>
        transitions = nfa->get_transitions();

    int *colors = new int[nfa->size];
    colors[0] = 1;
    for (auto finalNode: nfa->final_states){
        colors[finalNode->index] = 2;
    }

    for (int i = 0; i < transitions.size(); i++)
    {
        std::string color;

        out << i << ' ' << colors[i] << ": ";
        for (int j = 0; j < transitions[i].size(); j++)
        {
            out << "(" << transitions[i][j].first << "," << transitions[i][j].second << ") ";
        }
        out << std::endl;
    }

    nfa->freeCurrentMemory();
    delete nfa;

    system("./venv/bin/python print_nfa.py");
}