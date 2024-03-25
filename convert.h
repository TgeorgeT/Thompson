#ifndef CONVERT_H
#define CONVERT_H

#include "lambda_nfa.h"

std::string convert_to_prefix_form(std::string regex);
lambda_nfa *convert_postf_to_lambda_nfa(std::string regex);

#endif