#include "lambda_nfa.h"
#include <iostream>
#include <deque>
#include <string.h>

lambda_nfa::lambda_nfa(char c)
{
    start = new node(0);
    node *final = new node(1);

    start->next.push_back(std::make_pair(c, final));
    final_states = {final};
}

void lambda_nfa::freeCurrentMemory()
{
    std::deque<node *> queue;
    queue.push_back(start);

    bool *seen = new bool[size + 1];
    node** allNodes = new node*[size + 1];
    memset(seen, 0, size);

    std::cout << size << "\n";

    while (!queue.empty())
    {
        node *current = queue.front();
        queue.pop_front();

        if (seen[current->index] == true)
        {
            continue;
        }

        seen[current->index] = true;
        allNodes[current->index] = current;
        for (auto p : current->next)
        {
            if (seen[p.second->index] == false)
            {
                queue.push_back(p.second);
            }
        }
    }

    for (int i = 0; i < size; i++){
        if (seen[i] == false){
            continue;
        }
        delete (allNodes[i]);
    }
    delete allNodes;
    delete seen;
}

void lambda_nfa::reunion(lambda_nfa *other)
{
    node *new_start = new node(0);
    new_start->next.push_back(std::make_pair('_', start));
    new_start->next.push_back(std::make_pair('_', other->start));

    node *new_final = new node(1);
    new_final->is_final = true;
    for (node *final : final_states)
    {
        final->next.push_back(std::make_pair('_', new_final));
        final->is_final = false;
    }
    for (node *final : other->final_states)
    {
        final->next.push_back(std::make_pair('_', new_final));
        final->is_final = false;
    }
    final_states = {new_final};
    start = new_start;
}

void lambda_nfa::concatenation(lambda_nfa *other)
{
    for (node *final : final_states)
    {
        final->next.push_back(std::make_pair('_', other->start));
        final->is_final = false;
    }
    final_states = other->final_states;
}

void lambda_nfa::kleene()
{
    node *new_start = new node(0);
    new_start->next.push_back(std::make_pair('_', start));

    node *new_final = new node(1);
    new_final->is_final = true;

    new_start->next.push_back(std::make_pair('_', new_final));
    for (node *final : final_states)
    {
        final->next.push_back(std::make_pair('_', new_final));
        final->next.push_back(std::make_pair('_', start));
        final->is_final = false;
    }

    start = new_start;
}

// NOTE THAT YOU SHOULD MAKE SURE ALL NODES HAVE INDEX -1 FIRST
void lambda_nfa::assign_index()
{
    int index = 0;
    std::deque<node *> queue;
    queue.push_back(start);

    while (!queue.empty())
    {
        node *current = queue.front();
        queue.pop_front();

        if (current->index != -1)
        {
            continue;
        }

        current->index = index++;
        for (auto p : current->next)
        {
            queue.push_back(p.second);
        }
    }
    size = index;
}

std::vector<std::vector<std::pair<char, int>>> lambda_nfa::get_transitions()
{
    std::vector<std::vector<std::pair<char, int>>> transitions(size);

    std::deque<node *> queue;
    queue.push_back(start);

    bool *seen = new bool[size];
    memset(seen, 0, size);

    while (!queue.empty())
    {
        node *current = queue.front();
        queue.pop_front();

        if (seen[current->index])
        {
            continue;
        }

        seen[current->index] = true;
        for (auto p : current->next)
        {
            transitions[current->index].push_back(std::make_pair(p.first, p.second->index));
            if (!seen[p.second->index])
            {
                queue.push_back(p.second);
            }
        }
    }

    delete seen;

    return transitions;
}