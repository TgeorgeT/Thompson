#ifndef LAMBDA_NFA_H
#define LAMBDA_NFA_H

#include <vector>

// lambda λ
struct node
{
    std::vector<std::pair<char, node *>> next;
    bool is_final;
    int index;

    node(bool is_final)
    {
        this->is_final = is_final;
        next = std::vector<std::pair<char, node *>>(0);
        index = -1;
    };
};

class lambda_nfa
{
public:
    int size;

public:
    node *start;
    std::vector<node *> final_states;

    lambda_nfa(char c);

    void reunion(lambda_nfa *other);

    void concatenation(lambda_nfa *other);

    void kleene();

    void assign_index();

    std::vector<std::vector<std::pair<char, int>>> get_transitions();
};

#endif