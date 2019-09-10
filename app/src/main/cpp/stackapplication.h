#ifndef STACK_APPLICATION_H
#define STACK_APPLICATION_H

#include "linkedstack.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

struct Symbol
{
    char s;//
    int key;//
    int extraKey;//第二个key
    Symbol(char s, int key, int extraKey = -1)
    {
        this->s = s;
        this->key = key;
        this->extraKey = extraKey;
    }
    Symbol()
    {
        s = ' ';//初始化为空格
        key = -1;
        extraKey = -1;
    }
};

struct Pair//
{
    char left;
    char right;

    Pair(char l, char r)
    {
        left = l;
        right = r;
    }
    Pair()
    {
        left = '(';
        right = ')';
    }
};



void  match(Pair& p, const char* str);
string* infixToPostfix(const char* infix);
string* splitToString(const char* str,char splitChars[],int n);//str：要进行分割的源字符串 splitSymbol：分割标记字符
double countPostfix(string* postfix);
int isOperator(char operators[],int n, char ch);

#endif
