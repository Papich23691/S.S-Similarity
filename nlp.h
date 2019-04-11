#ifndef NLP   
#define NLP

#include <iostream>
#include <string>
#include <list>
#include <Python.h>

using namespace std;

list<list<string> > tokenize(string sentence);
double compare(string word1, string word2);

#endif