//
// Created by Yotam Levit on 22/09/2023.
//
#pragma once
#ifndef REGEX_ENGINE_PARSE_H
#define REGEX_ENGINE_PARSE_H

char* insertExplicitConcatOperator(char* exp);
char* infixToPostfix(char * infix);

#endif //REGEX_ENGINE_PARSE_H